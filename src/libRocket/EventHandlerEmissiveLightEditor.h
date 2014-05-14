#ifndef _EVENTHANDLER_EMISSIVE_LIGHT_EDITOR_H
#define _EVENTHANDLER_EMISSIVE_LIGHT_EDITOR_H

#include "EventHandler.h"
#include "GameDetails.h"

class EventHandlerEmissiveLightEditor: public EventHandler
{
public:
    EventHandlerEmissiveLightEditor();

	virtual ~EventHandlerEmissiveLightEditor();

	virtual void ProcessEvent(Rocket::Core::Event& event, const Rocket::Core::String& value);
	static void SetData(Rocket::Core::Event& event);

};


#endif // _EVENTHANDLER_EMISSIVE_LIGHT_EDITOR_H
