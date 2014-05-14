#ifndef EVENT_H
#define EVENT_H

#include <Rocket/Core/EventListener.h>


class Event : public Rocket::Core::EventListener
{
public:
	Event(const Rocket::Core::String& value);
	virtual ~Event();

	/// Sends the event value through to the event processing system.
	virtual void ProcessEvent(Rocket::Core::Event& event);

	/// Destroys the event.
	virtual void OnDetach(Rocket::Core::Element* element);

private:
	Rocket::Core::String value;
};

#endif
