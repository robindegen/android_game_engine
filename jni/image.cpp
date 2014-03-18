#include "aeon.h"
#include "image.h"

Image::Image()
:
Resource(Resource::ResourceType_Image),
mWidth(0),
mHeight(0),
mPixelFormat(PixelFormat_RGBA)
{

}

Image::~Image()
{

}

void Image::setData(BufferPtr buffer, std::uint32_t width, std::uint32_t height, PixelFormat pixelformat /*= PixelFormat_RGBA*/)
{
	if(buffer == NULL || buffer->get() == NULL)
	{
		Console::Print(Console::Warning, "Image::setData buffer empty.");
		return;
	}
	
	mBuffer = buffer;
	mWidth = width;
	mHeight = height;
	mPixelFormat = pixelformat;

	setLoaded();
}
