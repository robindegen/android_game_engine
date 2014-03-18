#ifndef renderable_h__
#define renderable_h__

class Renderable
{
public:
	Renderable() {}
	virtual ~Renderable() {}

	virtual void update(float dt) = 0;
	virtual void render(ShaderPtr shader) = 0;
};

#endif // renderable_h__
