#ifndef imageloader_h__
#define imageloader_h__

class ImageLoader
{
public:
	ImageLoader(){}
	virtual ~ImageLoader() {}

	virtual bool		load(ImagePtr image, const char *path) = 0;
	virtual bool		load(ImagePtr image, BufferPtr buffer) = 0;
};

typedef std::shared_ptr<ImageLoader>		ImageLoaderPtr;

#endif // imageloader_h__
