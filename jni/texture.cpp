#include "aeon.h"
#include "image.h"
#include "texture.h"
#include "resourcemanager.h"

Texture::Texture(ImagePtr image)
:
Resource(Resource::ResourceType_Texture),
mTexture(0),
mWidth(0),
mHeight(0),
mImage(image)
{

}

Texture::~Texture()
{
	unload();
}

void Texture::bind()
{
	//glBindTexture(GL_TEXTURE_2D, mTexture);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mTexture);

	//TODO: query the texture from the active shader
	glUniform1i(0, 0);
}

void Texture::unload()
{
	//Cleanup the GL texture if any is loaded
	if(mTexture != 0)
		glDeleteTextures(0, &mTexture);

	mTexture = 0;
}

void Texture::finalize()
{
	if(mImage == NULL || mImage->getData() == NULL || !mImage->loaded())
	{
		Console::Print(Console::Error, "Failed to load texture: Image wasn't loaded.");
		return;
	}

	//Cleanup the GL texture if any was loaded
	unload();

	//Generate and bind a new texture
	glGenTextures(1, &mTexture);
	glBindTexture(GL_TEXTURE_2D, mTexture);
	//bind();

	//DEBUGPRINT("Finalizing OpenGL texture %u", mTexture);

	GLenum glpixelformat = 0;
	switch(mImage->getPixelFormat())
	{
		case Image::PixelFormat_RGB:
		{
			glpixelformat = GL_RGB;
			//DEBUGPRINT("Image pixelformat is: RGB", 0);
		}break;
		case Image::PixelFormat_RGBA:
		{
			glpixelformat = GL_RGBA;
			//DEBUGPRINT("Image pixelformat is: RGBA", 0);
		}break;
		default:
		{
			Console::Print(Console::Error, "Failed to load texture: Unknown pixel format given.");
			return;
		}
	}

	mWidth = (float) mImage->getWidth();
	mHeight = (float) mImage->getHeight();

	DEBUGPRINT("Texture size is %f %f", mWidth, mHeight);

	glPixelStorei (GL_UNPACK_ALIGNMENT, 1);

	//gluBuild2DMipmaps(GL_TEXTURE_2D, 4, textureLoader.getWidth(), textureLoader.getHeight(), glpixelformat, GL_UNSIGNED_BYTE, buffer.get());
	glTexImage2D(GL_TEXTURE_2D, 0, glpixelformat, mImage->getWidth(), mImage->getHeight(), 0, glpixelformat, GL_UNSIGNED_BYTE, mImage->getData()->get());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	//Remove our reference to this image so it can be unloaded when no longer in use.
	mImage = EMPTY_IMAGE;

	//Mark this texture as loaded so the sprite can render.
	setLoaded();
}
