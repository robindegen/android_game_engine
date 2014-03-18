#ifndef resourcemanager_h__
#define resourcemanager_h__

#include "texture.h"
#include "shader.h"
#include "imageloader.h"

//All image loaders. Every extension has it's own loader. This makes it easier
//to add support for other file formats.
typedef std::map<std::string, ImageLoaderPtr> ImageLoaders;

//All loaded resources, finalized or not. 
typedef std::map<std::string, ResourceWeakPtr> LoadedResources;

class ResourceManager : public Singleton<ResourceManager>
{
public:
	ResourceManager();
	~ResourceManager();

	TexturePtr							loadTexture(const char *path);
	ShaderPtr							loadShader(const char *path);

	void								set_asset_manager(AAssetManager *mgr) { m_asset_manager = mgr; }
	AAssetManager *						get_asset_manager() { return m_asset_manager; }

private:
	//TODO: better name?
	ResourcePtr							checkIfResourceLoaded(const char *path, Resource::ResourceType type);
	void								markResourceAsLoaded(const char *path, ResourcePtr resource);

	ImageLoaders						mImageLoaders;
	LoadedResources						mLoadedResources;

	AAssetManager *						m_asset_manager;
};

#endif // resourcemanager_h__
