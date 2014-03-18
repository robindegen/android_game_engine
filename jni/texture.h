#ifndef texture_h__
#define texture_h__

#include "image.h"
#include "resource.h"

class TextureLoader;
class Texture : public Resource
{
public:
	Texture(ImagePtr image);
	~Texture();

	void			bind();

	void			unload();

	float			getWidth()				{ return mWidth; }
	float			getHeight()				{ return mHeight; }

	void			finalize();

	//This will be NULL after finalizing.
	ImagePtr		getInteralImage()		{ return mImage; }

	GLuint			getGLTexture()			{ return mTexture; }

private:
	GLuint			mTexture;
	float			mWidth;
	float			mHeight;

	ImagePtr		mImage;
};

typedef std::shared_ptr<Texture>		TexturePtr;

#endif // texture_h__
