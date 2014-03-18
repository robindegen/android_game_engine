#include "aeon.h"
#include "engine.h"
#include "resourcemanager.h"
#include "shader.h"

initializeSingleton(Engine);

Engine::Engine()
:
mEventListener(NULL),
mRunning(true),
mResourceManager(NULL),
mFontManager(NULL)
{
	/************************************************************************/
	/* Create our singletons                                                */
	/************************************************************************/
	mResourceManager = new ResourceManager();

}

Engine::~Engine()
{

}

bool Engine::initialize(float width, float height)
{
	/************************************************************************/
	/* Init GLES                                                            */
	/************************************************************************/
	Console::Print(Console::Info, "Initializing GLES renderer...");

	//TODO:

	Console::Print(Console::Info, "Initialized GLES renderer...");

	/************************************************************************/
	/* OpenGL settings                                                      */
	/************************************************************************/
	Console::Print(Console::Info, "Configuring GLES...");

	//Set up transparency
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Console::Print(Console::Info, "Setting up viewport %f %f", width, height);
	glViewport(0, 0, width, height);

	//Load the default shader. This shader should be sufficient unless you want special effects
	mDefaultShader = ResourceManager::getSingleton().loadShader("shaders/default");
	setDefaultShader();

	mProjectionMatrix = glm::ortho(0.0f, FULLSCREEN_VIRTUAL_RESOLUTION_WIDTH, FULLSCREEN_VIRTUAL_RESOLUTION_HEIGHT, 0.0f);

	/************************************************************************/
	/* Application initialize                                               */
	/************************************************************************/	
	if(mEventListener != NULL)
		mEventListener->onInitialize();

	return true;
}

void Engine::render()
{
	//Send update event
	if(mEventListener != NULL)
		mEventListener->onUpdate(0.1f);

	//Clear background
	glClearColor(COLOR_BACKGROUND);
	glClear(GL_COLOR_BUFFER_BIT);

	//If we don't have an active shader, there's nothing we can render.
	if(mActiveShader == NULL)
	{
		DEBUGPRINT("ERROR! No active shader!", 0)
		return;
	}

	//Set up the model matrix
	mActiveShader->setProjectionMatrix(mProjectionMatrix);

	//Send draw event
	if(mEventListener != NULL)
		mEventListener->onDraw();
}

void Engine::setDefaultShader()
{
	setActiveShader(mDefaultShader);
}

void Engine::setActiveShader(ShaderPtr shader)
{
	if(shader == NULL)
		return;

	mActiveShader = shader;
	mActiveShader->use();
}
