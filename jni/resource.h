#ifndef resource_h__
#define resource_h__

class Resource
{
public:
	enum ResourceType
	{
		ResourceType_Image,
		ResourceType_Texture,
		ResourceType_Shader,
		ResourceType_Font
	};

	Resource(ResourceType type)
	:
	mLoaded(false),
	mType(type)
	{}

	virtual ~Resource() {}

	bool			loaded()		{ return mLoaded; }
	ResourceType	getType()		{ return mType; }

	//This is called once after this resource was queued as completely loaded on the render thread.
	virtual void	finalize() {}

private:
	volatile bool	mLoaded; //The loaded parameter is being used cross-thread.
	ResourceType	mType;

protected:
	void			setLoaded()		{ mLoaded = true; }
};

typedef std::shared_ptr<Resource>		ResourcePtr;
//Used in the resource manager. The resource manager itself should not be owner of a resource.
typedef std::weak_ptr<Resource>		ResourceWeakPtr;
#define EMPTY_RESOURCE	ResourcePtr()

#endif // resource_h__
