#include "aeon.h"
#include "fileinput.h"
#include "image.h"
#include "imageloader.h"
#include "imageloader_png.h"
#include "lodepng.h"

ImageLoaderPng::ImageLoaderPng()
{

}

ImageLoaderPng::~ImageLoaderPng()
{

}

bool ImageLoaderPng::load(ImagePtr image, const char *path)
{
	//Open the new file
	FileInput file;

	if(!file.open(path))
		return false;

	size_t filesize = file.size();

	if(filesize == 0)
	{
		Console::Print(Console::Error, "Could not load PNG %s. File empty.", path);
		return false;
	}

	std::vector<unsigned char> encoded_image;
	encoded_image.resize(filesize);

	size_t read_result = file.read(&encoded_image[0]);
	file.close();

	DEBUGPRINT("Read result is %i", read_result);
	DEBUGPRINT("Size of encoded image is %i", encoded_image.size());

	std::vector<unsigned char> decoded_image;
	
	unsigned int width = 0;
	unsigned int height = 0;

	unsigned int error = lodepng::decode(decoded_image, width, height, encoded_image);
	
	DEBUGPRINT("Lodepng returned %u", error);
	DEBUGPRINT("Lodepng decoded size: %ux%u", width, height);

	BufferPtr bitmapBuffer(new Buffer(decoded_image.size()));
	memcpy(bitmapBuffer->get(), &decoded_image[0], decoded_image.size());
    
	//Load the data into the image object
	image->setData(bitmapBuffer, width, height, Image::PixelFormat_RGBA);

	return true;
}

bool ImageLoaderPng::load(ImagePtr image, BufferPtr buffer)
{
	//TODO: Implement loading PNG from memory.
	return false;
}
