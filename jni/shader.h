#ifndef shader_h__
#define shader_h__

#include "resource.h"

class Shader : public Resource
{
public:
	Shader();
	~Shader();

	void			use();
	void			unload();

	//Load a shader. Loading a shader is always synchronous since we instantly need it unlike textures.
	void			load(const char *path);

	void			setProjectionMatrix(glm::mat4 &matrix);
	void			setModelMatrix(glm::mat4 &matrix);
	void			setViewMatrix(glm::mat4 &matrix);

	void			setColor(glm::vec4 &color);

	//GLint			getModelMatrixHandle() 	{ return mModelMatrixHandle; }
	//GLint			getViewMatrixHandle()	{ return mViewMatrixHandle; }

private:
	GLuint			loadShader(std::string &src, GLenum type);
	GLuint			linkProgram(GLuint vertexshader, GLuint fragmentshader);

	GLuint			mProgram;
	GLint			mProjectionMatrixHandle;
	GLint			mModelMatrixHandle;
	GLint			mViewMatrixHandle;
	GLint			mTexture0Handle;
	GLint			mColor;

	std::string		mVertexShaderSrc;
	std::string		mFragmentShaderSrc;
};

typedef std::shared_ptr<Shader>		ShaderPtr;

#endif // shader_h__
