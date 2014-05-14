#ifndef EVENTHANDLER_TOOLBAR_H_
#define EVENTHANDLER_TOOLBAR_H_

#include "EventHandler.h"

class EventHandlerToolbar: public EventHandler
{
public:
    EventHandlerToolbar();
    ~EventHandlerToolbar();

    virtual void ProcessEvent(Rocket::Core::Event& event, const Rocket::Core::String& value);
protected:
private:


};


#endif // EVENTHANDLER_TOOLBAR_H_
