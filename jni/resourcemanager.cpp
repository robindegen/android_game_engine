#include "aeon.h"
#include "utils.h"
#include "resourcemanager.h"
#include "imageloader.h"
#include "imageloader_png.h"

initializeSingleton(ResourceManager);

ResourceManager::ResourceManager()
:
m_asset_manager(NULL)
{
	DEBUGPRINT("Creating ResourceManager...",0)

	//Register image loaders
	mImageLoaders["png"] = ImageLoaderPtr(new ImageLoaderPng());
}

ResourceManager::~ResourceManager()
{
	//Free all loaders
	mImageLoaders.clear();
}

TexturePtr ResourceManager::loadTexture(const char *path)
{
	Console::Print(Console::Info, "Loading texture %s", path);

	//Check if this resource was already loaded
	ResourcePtr resource = checkIfResourceLoaded(path, Resource::ResourceType_Texture);

	//We found the resource! Cast back to texture and return.
	if(resource != NULL)
		return std::static_pointer_cast<Texture>(resource);
	
	//Create an image object for the texture. This image will be loaded and filled in another thread
	ImagePtr image = ImagePtr(new Image());

	//Create the texture
	TexturePtr texture = TexturePtr(new Texture(image));

	std::string fileExtension = Utils::getExtensionFromFile(path);

	//Find the right loader for this file extension
	ImageLoaders::iterator itr = mImageLoaders.find(fileExtension);

	if(itr == mImageLoaders.end())
	{
		Console::Print(Console::Error, "Unsupported file extension: %s (%s)", fileExtension.c_str(), path);
		return TexturePtr();
	}

	if(itr->second == NULL)
	{
		Console::Print(Console::Error, "Unsupported file extension: %s (%s)", fileExtension.c_str(), path);
		return TexturePtr();
	}

	//Load the file into the image object
	if(!itr->second->load(texture->getInteralImage(), path))
	{
		Console::Print(Console::Error, "Could not load file %s", path);
		return TexturePtr();
	}

	Console::Print(Console::Info, "Finalizing texture %s", path);

	texture->finalize();

	//Mark this resource as loaded so we don't loaded it multiple times.
	markResourceAsLoaded(path, texture);

	return texture;
}

ShaderPtr ResourceManager::loadShader(const char *path)
{
	//Check if this resource was already loaded
	ResourcePtr resource = checkIfResourceLoaded(path, Resource::ResourceType_Shader);

	//We found the resource! Cast back to texture and return.
	if(resource != NULL)
		return std::static_pointer_cast<Shader>(resource);

	//It's not worth the time loading shaders on another thread. They're just small text files.
	ShaderPtr shader = ShaderPtr(new Shader());
	shader->load(path);

	//Mark this resource as loaded so we don't loaded it multiple times.
	markResourceAsLoaded(path, shader);

	shader->finalize();

	return shader;
}

ResourcePtr ResourceManager::checkIfResourceLoaded(const char *path, Resource::ResourceType type)
{
	//See if we've already loaded this file
	std::string pathString = path;
	LoadedResources::iterator resourceItr = mLoadedResources.find(pathString);

	//We found a resource! Return it.
	if(resourceItr != mLoadedResources.end())
	{
		//Check if there are still references to this resource.
		if(ResourcePtr resource = resourceItr->second.lock())
		{
			//Check the type
			if(resource->getType() == type)
				return resource;

			//This resource was of a different type. Warning...
			Console::Print(Console::Warning, "Resource type was not equal to previous load. Can't load resource.");
			return EMPTY_RESOURCE;
		}else{
			//There are apparently no references to this resource anymore, which means it was
			//automatically unloaded. Remove the weak pointer from the map

			//TODO: Add a GC pass to remove all these once in a while automatically
			mLoadedResources.erase(resourceItr);
		}
	}
	
	//The resource wasn't loaded yet.
	return EMPTY_RESOURCE;
}

void ResourceManager::markResourceAsLoaded(const char *path, ResourcePtr resource)
{
	//Add this resource to our map of loaded resources.
	std::string pathString = path;
	mLoadedResources[pathString] = ResourceWeakPtr(resource);
}
