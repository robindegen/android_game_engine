#ifndef ENGINE_H_
#define ENGINE_H_

#include "eventlistener.h"
#include "shader.h"
#include "sprite.h"

class FontManager;
class ResourceManager;
class Engine : public Singleton<Engine>
{
public:
	Engine();
	~Engine();

	bool 						initialize(float width, float height);
	void						setEventListener(EventListener *eventlistener)
									{	mEventListener = eventlistener; }

	void						render();

	void						stop()	{ mRunning = false; }

	void 						setDefaultShader();
	void 						setActiveShader(ShaderPtr shader);

	ShaderPtr					getActiveShader() { return mActiveShader; }

private:
	// Callbacks
	EventListener *				mEventListener;

	bool						mRunning;

	glm::mat4					mProjectionMatrix;

	ShaderPtr					mDefaultShader;
	ShaderPtr					mActiveShader;

	ResourceManager *			mResourceManager;
	FontManager *				mFontManager;
};

#endif /* ENGINE_H_ */
