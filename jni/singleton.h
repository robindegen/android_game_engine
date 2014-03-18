#ifndef singleton_h__
#define singleton_h__

#define initializeSingleton(type)					template <> type * Singleton <type>::mSingleton = NULL
#define createFileSingleton(type)					initializeSingleton(type); type the##type

template <class type>
class Singleton
{
public:
	Singleton()
	{
		assert(mSingleton == NULL);
		mSingleton = static_cast<type *>(this);

		if(mSingleton == NULL)
		{
			//Error!
		}
	}

	virtual ~Singleton()
	{
		mSingleton = NULL;
	}

	static type *create()
	{
		return new type;
	}

	static void dispose()
	{
		if(mSingleton != NULL)
			delete (type *) mSingleton;
	}

	static type & getSingleton()
	{ 
		assert(mSingleton);

		if(mSingleton == NULL)
		{
			//throw std::exception();
		}

		return *mSingleton;
	}

	static type * getSingletonPtr()
	{
		return mSingleton;
	}

protected:
	static type * mSingleton;

};

#endif // singleton_h__
