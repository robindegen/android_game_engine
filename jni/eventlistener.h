#ifndef EVENTLISTENER_H_
#define EVENTLISTENER_H_

class EventListener
{
public:
	EventListener() {}
	virtual ~EventListener() {}

	virtual void onInitialize() = 0;

	virtual void onDraw() = 0;
	virtual void onUpdate(float dt) = 0;
};

#endif /* EVENTLISTENER_H_ */
