#include "aeon.h"
#include "fileinput.h"
#include "resourcemanager.h"

FileInput::FileInput()
:
mFileSize(0),
m_asset(NULL)
{

}

FileInput::~FileInput()
{
	close();
}

bool FileInput::open(std::string path)
{
	return open(path.c_str());
}

bool FileInput::open(const char *path)
{
	DEBUGPRINT("Opening file: %s", path);
	AAssetManager *assetmanager = ResourceManager::getSingleton().get_asset_manager();
	
	DEBUGPRINT("using AssetManager at %x", assetmanager);

	//Open the file
	m_asset = AAssetManager_open(assetmanager, path, AASSET_MODE_UNKNOWN);

	DEBUGPRINT("Asset: %x", m_asset);

	if(!m_asset)
	{
		Console::Print(Console::Error, "Could not open file: %s", path);
		return false;
	}

	//Determine file size
	mFileSize = seek(0, SeekDirection_End);

	DEBUGPRINT("File Size %i", mFileSize);

	if(mFileSize == -1)
	{
		Console::Print(Console::Error, "Could not determine file size for file: %s. Seek end failed.", path);
		return false;
	}

	if(seek(0, SeekDirection_Begin) == -1)
	{
		Console::Print(Console::Error, "Could not determine file size for file: %s. Seek begin failed.", path);
		return false;
	}

	return true;
}

void FileInput::close()
{
	DEBUGPRINT("Closing file", 0);

	if(m_asset)
		AAsset_close(m_asset);

	m_asset = NULL;
}

size_t FileInput::read(unsigned char *buffer)
{
	return read(buffer, mFileSize);
}

size_t FileInput::read(unsigned char *buffer, size_t size)
{
	if(!m_asset || !buffer)
	{
		Console::Print(Console::Error, "Could not read from file.");
		return 0;
	}

	DEBUGPRINT("Reading %i bytes from asset %x", size, m_asset);

	int returnval = AAsset_read(m_asset, buffer, size);

	DEBUGPRINT("AAsset_read returned %i", returnval);

	return returnval;
}

size_t FileInput::read(std::string &string)
{
	if(mFileSize == 0)
		return 0;

	BufferPtr data = std::make_shared<Buffer>(mFileSize + 1);

	//string.reserve(mFileSize);
	int returnval = read((unsigned char *) data->get(), mFileSize);

	if(returnval <= 0)
		return returnval;

	//Null terminate the string
	data->get()[mFileSize] = '\0';

	//Copy into the std string
	string = (char *) data->get();

	return returnval;
}

int FileInput::seek(size_t count, SeekDirection direction)
{
	if(!m_asset)
		return -1;

	switch(direction)
	{
		case SeekDirection_Begin:
		{
			return AAsset_seek(m_asset, count, SEEK_SET);
		}break;
		case SeekDirection_Current:
		{
			return AAsset_seek(m_asset, count, SEEK_CUR);
		}break;
		case SeekDirection_End:
		{
			return AAsset_seek(m_asset, count, SEEK_END);
		}break;
	};

	return -1;
}
