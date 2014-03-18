#ifndef image_h__
#define image_h__

#include "resource.h"

class Image : public Resource
{
public:
	enum PixelFormat
	{
		PixelFormat_RGB,
		PixelFormat_RGBA,
	};

	Image();
	~Image();

	void					setData(BufferPtr buffer, std::uint32_t width, std::uint32_t height, PixelFormat pixelformat = PixelFormat_RGBA);

	BufferPtr				getData()			{ return mBuffer; }
	std::uint32_t			getWidth()			{ return mWidth; }
	std::uint32_t			getHeight()			{ return mHeight; }
	PixelFormat				getPixelFormat()	{ return mPixelFormat; }

private:
	BufferPtr				mBuffer;
	
	std::uint32_t			mWidth;
	std::uint32_t			mHeight;
	PixelFormat				mPixelFormat;
};

typedef std::shared_ptr<Image>	ImagePtr;
#define EMPTY_IMAGE		 ImagePtr();

#endif // image_h__
