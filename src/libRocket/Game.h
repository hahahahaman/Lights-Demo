#ifndef GAME_H
#define GAME_H

#include <Rocket/Core/Types.h>
#include <Rocket/Core/Texture.h>

#include <SFML/Graphics.hpp>

#include "ShellSFML.h"
#include "GameDetails.h"
//#include "LightPointEditor.h"

#include <LTBL/Light/LightSystem.h>

#include <cassert>
#include <cstdlib>
#include <memory>

#include "../TextureManager.hpp"


class Game
{
public:
	Game();
	~Game();

	/// Initialise a new game
	void Initialise();

	/// Update the game
	void Update();

	/// Render the game
	void Render();

	/// Get the dimensions of the game window.
	const Rocket::Core::Vector2f GetWindowDimensions();
protected:
    sf::RenderWindow* pRender_Window;

private:
    ltbl::ConvexHull* hull;

	std::unique_ptr<ltbl::LightSystem> pLight_System;

	void CreateLight();
	void CreateEmissiveLight();

	sf::Sprite sp_background;

	void DisplayLightPointEditorData();
	void DisplayEmissiveLightEditorData();

	void UpdateTool();

	void ResetTool();
	void ClearSelection();

    //queries region and selects wherever is underneath mouse
	void QueryRegion();

    friend class GameDetails;
    friend class ElementGame;
};

#endif
