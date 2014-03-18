#include "aeon.h"
#include "fileinput.h"
#include "shader.h"

Shader::Shader()
:
Resource(Resource::ResourceType_Shader),
mProgram(0),
mModelMatrixHandle(-1),
mViewMatrixHandle(-1),
mTexture0Handle(-1)
{

}

Shader::~Shader()
{
	unload();
}

void Shader::use()
{
	DEBUGPRINT("Using shader %u", mProgram);
	glUseProgram(mProgram);
}

void Shader::unload()
{
	//Cleanup the GL texture if any is loaded
	if(mProgram != 0)
	{
		DEBUGPRINT("Unloading OpenGL shader program %u", mProgram);
		//glDeleteTextures(1, &mTexture);
	}

	mProgram = 0;
}

void Shader::load(const char *path)
{
	std::string pathStr = path;

	FileInput vertexShaderFile;
	FileInput fragmentShaderFile;

	if(
		!vertexShaderFile.open(pathStr + ".vert") ||
		!fragmentShaderFile.open(pathStr + ".frag")
	)
	{
		Console::Print(Console::Error, "Could not load vertex shader %s.", path);
		return;
	}

	DEBUGPRINT("Reading shader sources",0);

	//Read the shader sources from file
	vertexShaderFile.read(mVertexShaderSrc);
	fragmentShaderFile.read(mFragmentShaderSrc);

	//DEBUGPRINT("Vertex shader %s", mVertexShaderSrc.c_str());

	//Compile the shaders
	DEBUGPRINT("Compiling Vertex Shader %s.vert", path);
	GLuint vertexshader = loadShader(mVertexShaderSrc, GL_VERTEX_SHADER);

	if(vertexshader == 0)
	{
		Console::Print(Console::Error, "Could not compile vertex shader.");
		return;
	}

	DEBUGPRINT("Compiling Fragment Shader %s.frag", path);
	GLuint fragmentshader = loadShader(mFragmentShaderSrc, GL_FRAGMENT_SHADER);

	if(vertexshader == 0)
	{
		Console::Print(Console::Error, "Could not compile fragment shader.");
		return;
	}

	//Link the shaders together into a program.
	DEBUGPRINT("Linking program %s", path);
	mProgram = linkProgram(vertexshader, fragmentshader);

	if (mProgram == 0)
	{
		Console::Print(Console::Error, "Error linking program.");
		glDeleteShader(vertexshader);
		glDeleteShader(fragmentshader);
		return;
	}

	DEBUGPRINT("Program linked: %i", mProgram);

	//Decrease the reference count on our shader objects so they get
	//deleted when the program is deleted.
	glDeleteShader(vertexshader);
	glDeleteShader(fragmentshader);

	//Set up the uniform locations for the matrices in this shader
	mProjectionMatrixHandle = glGetUniformLocation(mProgram, SHADER_PROJECTION_MATRIX_NAME);
	mModelMatrixHandle = glGetUniformLocation(mProgram, SHADER_MODEL_MATRIX_NAME);
	mViewMatrixHandle = glGetUniformLocation(mProgram, SHADER_VIEW_MATRIX_NAME);

	mTexture0Handle = glGetUniformLocation(mProgram, SHADER_TEXTURE0_NAME);
	mColor = glGetUniformLocation(mProgram, SHADER_COLOR_NAME);

	DEBUGPRINT("Found %s at: %i", SHADER_PROJECTION_MATRIX_NAME, mProjectionMatrixHandle);
	DEBUGPRINT("Found %s at: %i", SHADER_MODEL_MATRIX_NAME, mModelMatrixHandle);
	DEBUGPRINT("Found %s at: %i", SHADER_VIEW_MATRIX_NAME, mViewMatrixHandle);
	DEBUGPRINT("Found Texture0 at: %i", mTexture0Handle);
	DEBUGPRINT("Found Color at: %i", mColor);

	//Bind our shader
	use();
	//Set the default color
	glm::vec4 defaultcolor = glm::vec4(COLOR_DEFAULT);
	setColor(defaultcolor);

	//TODO: We should probably check if any of these are -1. If so, the shader is unusable.

	//Mark this shader as loaded so binding this shader works.
	setLoaded();
}

void Shader::setProjectionMatrix(glm::mat4 &matrix)
{
	if(mProjectionMatrixHandle == -1)
		return;

	glUniformMatrix4fv(mProjectionMatrixHandle, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::setModelMatrix(glm::mat4 &matrix)
{
	if(mModelMatrixHandle == -1)
		return;

	glUniformMatrix4fv(mModelMatrixHandle, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::setViewMatrix(glm::mat4 &matrix)
{
	if(mViewMatrixHandle == -1)
		return;

	glUniformMatrix4fv(mViewMatrixHandle, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::setColor(glm::vec4 &color)
{
	if(mColor == -1)
		return;

	glUniform4f(mColor, color.r, color.g, color.b, color.a);
}

GLuint Shader::loadShader(std::string &src, GLenum type)
{
	// Create the shader object
	GLuint shader = glCreateShader(type);

	if (shader == 0)
	{
		Console::Print(Console::Error, "Could not create shader.");
		return 0;
	}

	const char *shaderSrc = src.c_str();

	// Load the shader source
	glShaderSource(shader, 1, &shaderSrc, NULL);

	// Compile the shader
	glCompileShader(shader);

	// Check the compile status
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

	//Did the compile fail?
	if (!status)
	{
		//Do we have a log message? (compile errors etc.?)
		GLint infoLen = 0;
		glGetShaderiv (shader, GL_INFO_LOG_LENGTH, &infoLen);

		if (infoLen > 1)
		{
			char *infoLog = (char *) malloc(infoLen * sizeof(char));
			glGetShaderInfoLog (shader, infoLen, NULL, infoLog);
			Console::Print(Console::Error, "Error compiling shader:\n%s", infoLog);
			free(infoLog);
		}

		//Free the shader resource, since we can't use it anymore.
		glDeleteShader(shader);
		return 0;
	}

	return shader;
}

GLuint Shader::linkProgram(GLuint vertexshader, GLuint fragmentshader)
{
	mProgram = glCreateProgram();

	if (mProgram == 0)
	{
		Console::Print(Console::Error, "Could not create program.");
		return 0;
	}

	//Attach both fragment and vertex shaders to our program.
	glAttachShader(mProgram, vertexshader);
	glAttachShader(mProgram, fragmentshader);

	//Bind attrib locations (the bind points for vertex buffers to the shader)
	glBindAttribLocation(mProgram, SHADER_ATTRIB_VERTEX_ID, SHADER_ATTRIB_VERTEX_NAME);
	glBindAttribLocation(mProgram, SHADER_ATTRIB_TEXCOORD_ID, SHADER_ATTRIB_TEXCOORD_NAME);

	// Link the program
	glLinkProgram(mProgram);

	// Check the link status
	GLint status;
	glGetProgramiv(mProgram, GL_LINK_STATUS, &status);

	//Did linking fail?
	if (!status)
	{
		//Do we have a log message? (linker errors etc.?)
		GLint infoLen = 0;
		glGetProgramiv(mProgram, GL_INFO_LOG_LENGTH, &infoLen);

		if (infoLen > 1)
		{
			char *infoLog = (char *) malloc(infoLen * sizeof(char));
			glGetProgramInfoLog(mProgram, infoLen, NULL, infoLog);
			Console::Print(Console::Error, "Error linking shader:\n%s", infoLog);
			free(infoLog);
		}

		glDeleteProgram(mProgram);
		return 0;
	}

	return mProgram;
}
