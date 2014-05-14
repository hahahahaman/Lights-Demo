#ifndef ELEMENTGAME_H
#define ELEMENTGAME_H

#include <Rocket/Core/Element.h>
#include <Rocket/Core/EventListener.h>

#include "SystemInterfaceSFML.h"

#include "Game.h"

#include "EventHandlerLightPointEditor.h"

class ElementGame : public Rocket::Core::Element, public Rocket::Core::EventListener
{
public:
	ElementGame(const Rocket::Core::String& tag);
	virtual ~ElementGame();

	/// Intercepts and handles key events.
	void ProcessEvent(Rocket::Core::Event& event);

	/// Receive notifications when child elements are added
	/// This will only get called when we're added to the tree,
	/// which allows us to bind to onload
	void OnChildAdd(Rocket::Core::Element* element);

protected:
	/// Updates the game.
	virtual void OnUpdate();
	/// Renders the game.
	virtual void OnRender();

private:
	Game* game;
	//ltbl::Light_Point* testLight;
};

#endif
