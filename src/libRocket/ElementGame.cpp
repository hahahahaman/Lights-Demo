#include "ElementGame.h"
#include <Rocket/Core/ElementDocument.h>
#include <Rocket/Core/Input.h>
#include "EventManager.h"
#include "Game.h"

sf::Vector2f coord(0.0f, 0.0f);
static sf::Vector2f CenterDiff(0.0f, 0.0f);
static bool Drag = false;

ElementGame::ElementGame(const Rocket::Core::String& tag) : Rocket::Core::Element(tag)
{
    game = new Game();
    SetProperty("drag", "drag");
}

ElementGame::~ElementGame()
{
    delete game;
}

// Intercepts and handles key events.
void ElementGame::ProcessEvent(Rocket::Core::Event& event)
{
    Rocket::Core::Element::ProcessEvent(event);

    if (event == "keydown" ||
            event == "keyup")
    {
        bool key_down = event == "keydown";
        Rocket::Core::Input::KeyIdentifier key_identifier = (Rocket::Core::Input::KeyIdentifier) event.GetParameter< int >("key_identifier", 0);

        if (key_identifier == Rocket::Core::Input::KI_ESCAPE &&
                !key_down)
        {
            Shell::RequestExit();
        }

        //key pressed
        if (key_down)
        {
            if (key_identifier == Rocket::Core::Input::KI_LEFT)
            {
                //testLight->setCenter(sf::Vector2f(testLight->getCenter().x -10, testLight->getCenter().y));
                //testLight->incCenter(sf::Vector2f(-10.f, 0.0f));
            }

            if (key_identifier == Rocket::Core::Input::KI_RIGHT)
            {
                //testLight->setCenter(sf::Vector2f(testLight->getCenter().x +10, testLight->getCenter().y));
                //testLight->incCenter(sf::Vector2f(10.f, 0.0f));
            }

            if (key_identifier == Rocket::Core::Input::KI_UP)
            {
                //GameDetails::pSelectedLight->incRadius(10.f);
            }

            if(key_identifier == Rocket::Core::Input::KI_DOWN)
            {
                //GameDetails::pSelectedLight->incRadius(-10.f);
            }
        }
        //key released
        else if (!key_down)
        {
            if (key_identifier == Rocket::Core::Input::KI_LEFT)
            {
            }

            if (key_identifier == Rocket::Core::Input::KI_RIGHT)
            {
            }

            if(key_identifier == Rocket::Core::Input::KI_F1)
            {
                GameDetails::Debug = !GameDetails::Debug;
            }

            if(key_identifier == Rocket::Core::Input::KI_F2)
            {
                game->pLight_System->m_obliqueShadows = !game->pLight_System->m_obliqueShadows;
            }
            if(key_identifier == Rocket::Core::Input::KI_DELETE)
            {
                if(GameDetails::GetTool() == GameDetails::TOOL_MOUSE)
                {
                    if(GameDetails::pSelected != nullptr)
                    {
                        if(GameDetails::SelectedTool == GameDetails::TOOL_LIGHT)
                        {
                            game->pLight_System->removeLight(static_cast<ltbl::Light_Point*>(GameDetails::pSelected));
                            game->ClearSelection();
                            GameDetails::SelectedTool = GameDetails::TOOL_MOUSE;
                        }
                        else if(GameDetails::SelectedTool == GameDetails::TOOL_EMISSIVE)
                        {
                            game->pLight_System->removeEmissiveLight(static_cast<ltbl::EmissiveLight*>(GameDetails::pSelected));
                            game->ClearSelection();
                            GameDetails::SelectedTool = GameDetails::TOOL_MOUSE;
                        }
                    }
                }
            }
        }
    }

    if (event == "load")
    {
        game->Initialise();

        Rocket::Core::Log::Message(Rocket::Core::Log::LT_INFO,"INITIALIZING");
    }

    if(event == "mousemove")
    {
        /*
        float x = event.GetParameter<float>("mouse_x", 0.f);
        float y = event.GetParameter<float>("mouse_y", 0.f);
        coord.x = x;
        coord.y = y;
        //printf("%f, %f\n", coord.x, coord.y);
        */
    }

    if(event == "click")
    {
        if(GameDetails::GetTool() == GameDetails::TOOL_MOUSE)
        {
            //selects an object (if there is one) when clicked
            game->QueryRegion();
        }
    }

    if(event == "dragstart")
    {
        if(GameDetails::GetTool() == GameDetails::TOOL_MOUSE)
        {
            game->QueryRegion();
            if(GameDetails::pSelected != nullptr)
            {
                if(GameDetails::SelectedTool == GameDetails::TOOL_LIGHT)
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(*game->pRender_Window);

                    // convert it to world coordinates
                    sf::Vector2f worldPos = game->pRender_Window->mapPixelToCoords(mousePos);

                    //distance from center used throughout the drag
                    CenterDiff = static_cast<ltbl::Light_Point*>(GameDetails::pSelected)->getCenter() - worldPos;
                    Drag = true;
                }
                else if(GameDetails::SelectedTool == GameDetails::TOOL_EMISSIVE)
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(*game->pRender_Window);

                    // convert it to world coordinates
                    sf::Vector2f worldPos = game->pRender_Window->mapPixelToCoords(mousePos);

                    CenterDiff = static_cast<ltbl::EmissiveLight*>(GameDetails::pSelected)->getCenter() - worldPos;
                    Drag = true;
                }
            }
        }
    }

    if(event == "dragend")
    {
        if(GameDetails::GetTool() == GameDetails::TOOL_MOUSE)
        {
            if(Drag)
            {
                Drag = false;
                CenterDiff = sf::Vector2f(0.0f, 0.f);
            }
        }
    }

    //when first focused upon do not create a light, but double clicking is fine i guess`
    if(event == "dblclick")
    {
        int button = event.GetParameter<int>("button_index", 0);
        if(button == 0)
        {
            if(GameDetails::GetTool() == GameDetails::TOOL_LIGHT)
                game->CreateLight();
            else if(GameDetails::GetTool() == GameDetails::TOOL_EMISSIVE)
                game->CreateEmissiveLight();
        }
    }
}

// Updates the game.
void ElementGame::OnUpdate()
{
    game->Update();
    if(Drag)
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(*game->pRender_Window);

        // convert it to world coordinates
        sf::Vector2f worldPos = game->pRender_Window->mapPixelToCoords(mousePos);

        if(GameDetails::pSelected != nullptr)
        {
            if(GameDetails::SelectedTool == GameDetails::TOOL_LIGHT)
            {
                static_cast<ltbl::Light_Point*>(GameDetails::pSelected)->setCenter(worldPos + CenterDiff);
            }
            else if(GameDetails::SelectedTool == GameDetails::TOOL_EMISSIVE)
            {
                static_cast<ltbl::EmissiveLight*>(GameDetails::pSelected)->setCenter(worldPos + CenterDiff);
            }
        }
    }
}

// Renders the game.
void ElementGame::OnRender()
{
    game->Render();
}

void ElementGame::OnChildAdd(Rocket::Core::Element* element)
{
    Rocket::Core::Element::OnChildAdd(element);

    if (element == this)
        GetOwnerDocument()->AddEventListener("load", this);
}
