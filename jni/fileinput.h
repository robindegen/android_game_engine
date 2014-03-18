#ifndef fileinput_h__
#define fileinput_h__

//TODO: For now only binary files. Support text and binary in a neat interface.
class FileInput
{
public:
	enum SeekDirection
	{
		SeekDirection_Begin,
		SeekDirection_Current,
		SeekDirection_End
	};

	FileInput();
	~FileInput();

	bool				open(std::string path);
	bool				open(const char *path);
	void				close();

	size_t				read(unsigned char *buffer);
	size_t				read(unsigned char *buffer, size_t size);
	size_t				read(std::string &string);

	int					seek(size_t count, SeekDirection direction);

	size_t				size()				{ return mFileSize; }

private:
	size_t				mFileSize;

	AAsset *			m_asset;
};


#endif // fileinput_h__
