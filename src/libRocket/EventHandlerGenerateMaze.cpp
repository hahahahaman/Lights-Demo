

#include "EventHandlerGenerateMaze.h"
#include <Rocket/Core/Context.h>
#include <Rocket/Core/ElementDocument.h>
#include <Rocket/Core/ElementUtilities.h>
#include <Rocket/Core/Event.h>
#include <Rocket/Controls.h>
#include "EventManager.h"
#include "GameDetails.h"

// The game's element Context (declared in main.cpp).
extern Rocket::Core::Context* Context;

EventHandlerGenerateMaze::EventHandlerGenerateMaze()
{
}

EventHandlerGenerateMaze::~EventHandlerGenerateMaze()
{
}


void EventHandlerGenerateMaze::ProcessEvent(Rocket::Core::Event& event, const Rocket::Core::String& value)
{
	if (value == "generate")
	{
	    /*
		// Set the difficulty.
		Rocket::Core::String difficulty = event.GetParameter< Rocket::Core::String >("difficulty", "easy");
		if (difficulty == "hard")
			GameDetails::SetDifficulty(GameDetails::HARD);
		else
			GameDetails::SetDifficulty(GameDetails::EASY);
        */

		// Set the defender colour.
		//Rocket::Core::StringList algorithm_list;
		//Rocket::Core::StringUtilities::ExpandString(colour_components, event.GetParameter< Rocket::Core::String >("algorithm", (int) 0));

        Rocket::Core::Element* input_width= event.GetTargetElement()->GetElementById("input_width");
        Rocket::Core::Element* input_height= event.GetTargetElement()->GetElementById("input_height");

        Rocket::Core::String width = input_height->GetAttribute<Rocket::Core::String>("value", "");
        Rocket::Core::String height = input_width->GetAttribute<Rocket::Core::String>("value", "");

        vertex v;
        v.x = atoi(height.CString());
        v.y = atoi(width.CString());
        GameDetails::setSize(v);

        Rocket::Core::ElementDocument* body= event.GetTargetElement()->GetOwnerDocument();

        Rocket::Controls::ElementFormControlSelect* select_algorithm= dynamic_cast<Rocket::Controls::ElementFormControlSelect*>(body->GetElementById("select_algorithm"));
        int algorithm =select_algorithm->GetSelection();
		GameDetails::setAlgorithm(algorithm);

		GameDetails::setGenerateNew(true);
	}
}
