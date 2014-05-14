#ifndef _EVENT_HANDLER_LIGHT_POINT_EDITOR_H_
#define _EVENT_HANDLER_LIGHT_POINT_EDITOR_H_

#include "EventHandler.h"
#include "GameDetails.h"

class EventHandlerLightPointEditor: public EventHandler
{
public:
    EventHandlerLightPointEditor();

	virtual ~EventHandlerLightPointEditor();

	virtual void ProcessEvent(Rocket::Core::Event& event, const Rocket::Core::String& value);
	static void SetData(Rocket::Core::Event& event);

};

/* was using this until found out about Event.h
class KeydownListener: public Rocket::Core::EventListener
{
public:
    static void RegisterKeydownObject(Rocket::Core::Element* element);
protected:
    virtual void ProcessEvent(Rocket::Core::Event& event);
};
*/

#endif // _EVENT_HANDLER_LIGHT_POINT_EDITOR_H_

