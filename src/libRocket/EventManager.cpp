#include "EventManager.h"
#include <Rocket/Core/Context.h>
#include <Rocket/Core/ElementDocument.h>
#include <Rocket/Core/ElementUtilities.h>
#include "ShellSFML.h"
#include "EventHandler.h"
#include "GameDetails.h"
#include <map>

// The game's element Context (declared in main.cpp).
extern Rocket::Core::Context* Context;

// The event handler for the current screen. This may be NULL if the current screen has no specific functionality.
static EventHandler* event_handler = NULL;

// The event handlers registered with the manager.
typedef std::map< Rocket::Core::String, EventHandler* > EventHandlerMap;
EventHandlerMap event_handlers;

EventManager::EventManager()
{
}

EventManager::~EventManager()
{
}

// Releases all event handlers registered with the manager.
void EventManager::Shutdown()
{
    for (EventHandlerMap::iterator i = event_handlers.begin(); i != event_handlers.end(); ++i)
        delete (*i).second;

    event_handlers.clear();
    event_handler = NULL;
}

// Registers a new event handler with the manager.
void EventManager::RegisterEventHandler(const Rocket::Core::String& handler_name, EventHandler* handler)
{
    // Release any handler bound under the same name.
    EventHandlerMap::iterator iterator = event_handlers.find(handler_name);
    if (iterator != event_handlers.end())
        delete (*iterator).second;

    event_handlers[handler_name] = handler;
}

// Processes an event coming through from Rocket.
void EventManager::ProcessEvent(Rocket::Core::Event& event, const Rocket::Core::String& value)
{
    Rocket::Core::StringList commands;
    Rocket::Core::StringUtilities::ExpandString(commands, value, ';');

    if(commands.size() == 0)
    {
        //send only the event to event handlers
        for(EventHandlerMap::iterator it = event_handlers.begin(); it != event_handlers.end(); it++)
            if(it->second != NULL)
                it->second->ProcessEvent(event, "");
    }
    else
    {
        for (size_t i = 0; i < commands.size(); ++i)
        {
            // Check for a generic 'load' or 'exit' command.
            Rocket::Core::StringList values;
            Rocket::Core::StringUtilities::ExpandString(values, commands[i], ' ');

            //if (values.empty())
            //	return;

            if (values[0] == "goto" &&
                    values.size() > 1)
            {
                // Load the window, and if successful close the old window.
                if (LoadWindow(values[1]))
                    event.GetTargetElement()->GetOwnerDocument()->Close();
            }
            else if (values[0] == "load" &&
                     values.size() > 1)
            {
                // Load the window.
                LoadWindow(values[1]);
            }
            else if (values[0] == "close")
            {
                Rocket::Core::ElementDocument* target_document = NULL;

                if (values.size() > 1)
                    target_document = Context->GetDocument(values[1].CString());
                else
                    target_document = event.GetTargetElement()->GetOwnerDocument();

                if (target_document != NULL)
                    target_document->Close();
            }
            else if (values[0] == "exit")
            {
                Shell::RequestExit();
            }
            /*
            		else if (values[0] == "pause")
            		{
            			GameDetails::SetPaused(true);
            		}
            		else if (values[0] == "unpause")
            		{
            			GameDetails::SetPaused(false);
            		}
            */
            else
            {
                //send the event to all windows
                for(EventHandlerMap::iterator it = event_handlers.begin(); it != event_handlers.end(); it++)
                    if(it->second != NULL)
                        it->second->ProcessEvent(event, commands[i]);

                /*
                if (event_handler != NULL)
                {
                	event_handler->ProcessEvent(event, commands[i]);
                }
                */
            }
        }
    }
}

// Loads a window and binds the event handler for it.
Rocket::Core::ElementDocument* EventManager::LoadWindow(const Rocket::Core::String& window_name)
{
    // Set the event handler for the new screen, if one has been registered.
    EventHandler* old_event_handler = event_handler;
    EventHandlerMap::iterator iterator = event_handlers.find(window_name);
    if (iterator != event_handlers.end())
    {
        event_handler = iterator->second;
        //Rocket::Core::Log::Message(Rocket::Core::Log::LT_INFO, "%s", window_name.CString());
    }
    else
        event_handler = NULL;

    // Attempt to load the referenced RML document.
    Rocket::Core::String document_path = Rocket::Core::String("data/") + window_name + Rocket::Core::String(".rml");
    Rocket::Core::ElementDocument* document = Context->LoadDocument(document_path.CString());
    if (document == nullptr)
    {
        event_handler = old_event_handler;
        return nullptr;
    }

    document->SetId(window_name);

    // Set the element's title on the title; IDd 'title' in the RML.
    Rocket::Core::Element* title = document->GetElementById("title");
    if (title != NULL)
        title->SetInnerRML(document->GetTitle());

    document->Focus();
    document->Show();

    // Remove the caller's reference.
    document->RemoveReference();

    return document;
}
