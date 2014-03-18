#ifndef sprite_h__
#define sprite_h__

#include "texture.h"
#include "renderable.h"
#include "vertex.h"
#include "shader.h"

class Sprite : public Renderable
{
public:
	Sprite(TexturePtr texture, bool autosize = true);
	Sprite(const char *path, bool autosize = true);
	~Sprite();

	void			update(float dt);
	void			render(ShaderPtr shader);

	void			setSize(float width, float height);

	void			setTexture(TexturePtr texture) 	{ mTexture = texture; }

	glm::mat4 &		getMatrix() 					{ return mMatrix; }

	glm::vec4 &		getColor()						{ return mColor; }
	void			setColor(glm::vec4 color)		{ mColor = color; }

	bool			isTextureLoaded()				{ return mTexture->loaded(); }

	TexturePtr		getTexture()					{ return mTexture; }

private:
	void			initVertexData();

	TexturePtr		mTexture;
	glm::mat4		mMatrix;

	bool			mAutoSize;

	Vertex			mVertexData[4];
	glm::vec4		mColor;
};

typedef std::shared_ptr<Sprite>		SpritePtr;
#define EMPTY_SPRITE				SpritePtr()

#endif // sprite_h__
