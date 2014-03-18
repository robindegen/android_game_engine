#include "aeon.h"
#include "resourcemanager.h"
#include "sprite.h"

Sprite::Sprite(TexturePtr texture, bool autosize /* = true*/)
:
mTexture(texture),
mAutoSize(autosize),
mColor(COLOR_DEFAULT)
{
	//Set up the raw vertex data. (0.0 size)
	initVertexData();
}

Sprite::Sprite(const char *path, bool autosize /* = true*/)
:
mAutoSize(autosize),
mColor(COLOR_DEFAULT)
{
	mTexture = ResourceManager::getSingleton().loadTexture(path);

	//Set up the raw vertex data. (0.0 size)
	initVertexData();
}

Sprite::~Sprite()
{
}

void Sprite::update(float dt)
{

}

void Sprite::render(ShaderPtr shader)
{
	if(!mTexture->loaded())
		return;

	if(mAutoSize)
	{
		DEBUGPRINT("Auto sizing sprite to %1.0f %1.0f", mTexture->getWidth(), mTexture->getHeight());
		setSize(mTexture->getWidth(), mTexture->getHeight());
		mAutoSize = false;
	}

	//Bind the texture
	mTexture->bind();

	//Set up our matrix in the shader
	shader->setViewMatrix(mMatrix);
	shader->setColor(mColor);

	glVertexAttribPointer(SHADER_ATTRIB_VERTEX_ID, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *) mVertexData);
	glEnableVertexAttribArray(SHADER_ATTRIB_VERTEX_ID);

	//The texture offsets start at UV in the struct. However we need to cast vertex data to a char first so we add the offset in bytes
	//properly. This might seem weird.. but it's the only proper way that doesn't generate a gcc warning.
	glVertexAttribPointer(SHADER_ATTRIB_TEXCOORD_ID, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *) (((char *) mVertexData) + offsetof(Vertex, uv)));
	glEnableVertexAttribArray(SHADER_ATTRIB_TEXCOORD_ID);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void Sprite::setSize(float width, float height)
{
	mVertexData[1].position[1] = height;
	mVertexData[2].position[0] = width;
	mVertexData[3].position[0] = width;
	mVertexData[3].position[1] = height;
}

void Sprite::initVertexData()
{
	//Position data
	mVertexData[0].position[0] = 0.0f;
	mVertexData[0].position[1] = 0.0f;
	mVertexData[1].position[0] = 0.0f;
	mVertexData[1].position[1] = 0.0f;
	mVertexData[2].position[0] = 0.0f;
	mVertexData[2].position[1] = 0.0f;
	mVertexData[3].position[0] = 0.0f;
	mVertexData[3].position[1] = 0.0f;

	//UV data
	mVertexData[0].uv[0] = 0.0f;
	mVertexData[0].uv[1] = 0.0f;
	mVertexData[1].uv[0] = 0.0f;
	mVertexData[1].uv[1] = 1.0f;
	mVertexData[2].uv[0] = 1.0f;
	mVertexData[2].uv[1] = 0.0f;
	mVertexData[3].uv[0] = 1.0f;
	mVertexData[3].uv[1] = 1.0f;
}
