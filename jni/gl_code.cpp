#include "aeon.h"
#include "engine.h"
#include "resourcemanager.h"
#include "sprite.h"
#include <cstdlib>

extern "C"
{
    JNIEXPORT void JNICALL Java_com_android_aeon_AeonLib_init(JNIEnv * env, jobject obj, jobject assetmanager, jint width, jint height);
    JNIEXPORT void JNICALL Java_com_android_aeon_AeonLib_step(JNIEnv * env, jobject obj);
};

Engine engine;
TexturePtr texture;

struct SpritePos
{
	float x;
	float y;
	float xdir;
	float ydir;
	SpritePtr sprite;
};

std::vector<SpritePos> sprites;

class EventListenerWrapper : public EventListener
{
public:
	EventListenerWrapper() {}
	~EventListenerWrapper() {}

	void onInitialize()
	{
		Console::Print(Console::Info, "Initialize. Loading mario!");

		texture = ResourceManager::getSingleton().loadTexture("textures/mario.png");

		for(int i = 0; i < 300; ++i)
		{
			SpritePos sp;

			sp.sprite = SpritePtr(new Sprite(texture, true));
			sp.x = (float) ((rand()%1000)+1);
			sp.y = (float) ((rand()%800)+1);
			sp.xdir = (float) ((rand()%10)+1);
			sp.ydir = (float) ((rand()%10)+1);

			sprites.push_back(sp);
		}
	}

	void onDraw() 
	{
		glm::mat4 view_mat(1.0f);
		engine.getActiveShader()->setModelMatrix(view_mat);

		for(SpritePos sprite : sprites)
		{
			sprite.sprite->render(engine.getActiveShader());
		}
	}

	void onUpdate(float dt)
	{
		for(SpritePos &sprite : sprites)
		{
			sprite.x += sprite.xdir;
			
			if(sprite.x > 1280.0f)
				sprite.xdir = -sprite.xdir;

			if(sprite.x < 0)
				sprite.xdir = -sprite.xdir;
			
			sprite.y += sprite.ydir;

			if(sprite.y > 720.0f)
				sprite.ydir = -sprite.ydir;

			if(sprite.y < 0)
				sprite.ydir = -sprite.ydir;

			sprite.sprite->getMatrix() = glm::translate(glm::mat4(1.0f), glm::vec3(sprite.x, sprite.y, 0.0f));
			sprite.sprite->update(dt);
		}
	}
};

EventListenerWrapper eventlistener;

JNIEXPORT void JNICALL Java_com_android_aeon_AeonLib_init(JNIEnv * env, jobject obj, jobject assetmanager, jint width, jint height)
{
	//Hold a reference to the asset manager here.
	//env->NewGlobalRef(assetmanager);

	Console::Print(Console::Info, "AAssetManager_fromJava");
	AAssetManager* mgr = AAssetManager_fromJava(env, assetmanager);
	Console::Print(Console::Info, "set_asset_manager");
	ResourceManager::getSingleton().set_asset_manager(mgr);	

	Console::Print(Console::Info, "Setting event listener...");
	engine.setEventListener(&eventlistener);

	Console::Print(Console::Info, "Calling init");
    engine.initialize((float) width, (float) height);

	Console::Print(Console::Info, "init done.");
}

JNIEXPORT void JNICALL Java_com_android_aeon_AeonLib_step(JNIEnv * env, jobject obj)
{
    engine.render();
}
