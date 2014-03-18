#ifndef imageloader_png_h__
#define imageloader_png_h__

class ImageLoaderPng : public ImageLoader
{
public:
	ImageLoaderPng();
	~ImageLoaderPng();

	bool		load(ImagePtr image, const char *path);
	bool		load(ImagePtr image, BufferPtr buffer);
};

#endif // imageloader_png_h__
