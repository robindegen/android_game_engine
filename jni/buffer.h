#ifndef buffer_h__
#define buffer_h__

class Buffer
{
public:
	Buffer()
	:
	mBuffer(NULL),
	mSize(0)
	{}
	
	Buffer(size_t size)
	:
	mBuffer(NULL),
	mSize(0)
	{
		alloc(size);
	}

	~Buffer()
	{
		free();
	}

	void alloc(size_t size)
	{
		mBuffer = (unsigned char *) malloc(size);
		mSize = size;

		//DEBUGPRINT("Buffer: Allocated %u bytes at %x.", size, mBuffer);
	}

	void free()
	{
		if(mBuffer)
			::free(mBuffer);

		//DEBUGPRINT("Buffer: Freed %u bytes at %x.", mSize, mBuffer);

		mBuffer = NULL;
		mSize = 0;
	}

	unsigned char *		get()		{ return mBuffer; }
	size_t				size()		{ return mSize; }

private:
	unsigned char *		mBuffer;
	size_t				mSize;
};

typedef std::shared_ptr<Buffer> BufferPtr;

#endif // buffer_h__
