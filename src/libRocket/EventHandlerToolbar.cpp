#include "EventHandlerToolbar.h"
#include "GameDetails.h"

EventHandlerToolbar::EventHandlerToolbar()
{

}

EventHandlerToolbar::~EventHandlerToolbar()
{

}

void EventHandlerToolbar::ProcessEvent(Rocket::Core::Event& event, const Rocket::Core::String& value)
{
    if(value == "switch_mouse")
    {
        GameDetails::SetTool(GameDetails::TOOL_MOUSE);
    }

    if(value == "switch_light")
    {
        GameDetails::SetTool(GameDetails::TOOL_LIGHT);
    }

    if(value == "switch_emissive")
    {
        GameDetails::SetTool(GameDetails::TOOL_EMISSIVE);
    }
}
