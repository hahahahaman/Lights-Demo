

#ifndef ROCKETINVADERSEVENTHANDLERGenerateMaze_H
#define ROCKETINVADERSEVENTHANDLERGenerateMaze_H

#include "EventHandler.h"

/**
	@author Peter Curry
 */

class EventHandlerGenerateMaze : public EventHandler
{
public:
	EventHandlerGenerateMaze();

	virtual ~EventHandlerGenerateMaze();

	virtual void ProcessEvent(Rocket::Core::Event& event, const Rocket::Core::String& value);
private:
};

#endif
