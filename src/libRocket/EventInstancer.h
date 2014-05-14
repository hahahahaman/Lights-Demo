#ifndef EVENTINSTANCER_H
#define EVENTINSTANCER_H

#include <Rocket/Core/EventListenerInstancer.h>


class EventInstancer : public Rocket::Core::EventListenerInstancer
{
public:
	EventInstancer();
	virtual ~EventInstancer();

	/// Instances a new event handler.
	virtual Rocket::Core::EventListener* InstanceEventListener(const Rocket::Core::String& value, Rocket::Core::Element* element);

	/// Destroys the instancer.
	virtual void Release();
};

#endif
