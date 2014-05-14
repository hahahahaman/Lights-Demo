#include <cassert>
#include <cstdlib>
#include <vector>
#include <ctime>

#include <GL/glew.h>

#include <SFML/Graphics.hpp>

#include <Rocket/Core.h>
#include <Rocket/Controls.h>
#include <Rocket/Debugger.h>
#include <Rocket/Core/Input.h>
#include <Rocket/Debugger/Debugger.h>

#include "libRocket/ElementGame.h"
//#include "libRocket/EventHandlerGenerateMaze.h"
#include "libRocket/EventManager.h"
#include "libRocket/EventInstancer.h"

#include "libRocket/ShellSFML.h"

#include "libRocket/SystemInterfaceSFML.h"
#include "libRocket/RenderInterfaceSFML.h"
#include "libRocket/ShellFileInterface.h"

#include "libRocket/EventHandlerLightPointEditor.h"
#include "libRocket/EventHandlerEmissiveLightEditor.h"
#include "libRocket/EventHandlerToolbar.h"
#include "libRocket/Event.h"

using namespace std;

//some global stuff
Rocket::Core::Context* Context = NULL;
bool Run = true;

int main()
{
    //random seed
    srand(time(NULL));

    //sfml window stuff
    sf::RenderWindow render_window(sf::VideoMode(1600, 900), "Lights");
    render_window.setPosition(sf::Vector2i(100, 100));
    sf::View camera = render_window.getDefaultView();

    sf::Image icon;

    assert(icon.loadFromFile("data/icon.png"));

    render_window.setIcon(32, 32, icon.getPixelsPtr());

    sf::Event event;

    Shell::OpenWindow(&render_window);

    //rocket sfml interfaces
    RocketSFMLRenderer Renderer;
    RocketSFMLSystemInterface SystemInterface;
    ShellFileInterface FileInterface("./data/");

    //glew
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        //...
    }
    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

    //more intialization
    if(!render_window.isOpen())
        return 1;

    Renderer.SetWindow(&render_window);

    Rocket::Core::SetFileInterface(&FileInterface);
    Rocket::Core::SetRenderInterface(&Renderer);
    Rocket::Core::SetSystemInterface(&SystemInterface);

    if(!Rocket::Core::Initialise())
        return 1;

    Rocket::Controls::Initialise();

    //fonts
    Rocket::Core::FontDatabase::LoadFontFace("fonts/Delicious-Bold.otf");
    Rocket::Core::FontDatabase::LoadFontFace("fonts/Delicious-BoldItalic.otf");
    Rocket::Core::FontDatabase::LoadFontFace("fonts/Delicious-Italic.otf");
    Rocket::Core::FontDatabase::LoadFontFace("fonts/Delicious-Roman.otf");

    //context
    Context = Rocket::Core::CreateContext("default",
                                          Rocket::Core::Vector2i(render_window.getSize().x, render_window.getSize().y));

    //debugger
    Rocket::Debugger::Initialise(Context);

    // Register custom element and decorator instancers.
    Rocket::Core::ElementInstancer* element_instancer = new Rocket::Core::ElementInstancerGeneric< ElementGame >();
    Rocket::Core::Factory::RegisterElementInstancer("game", element_instancer);
    element_instancer->RemoveReference();

    /*
        Rocket::Core::DecoratorInstancer* decorator_instancer = new DecoratorInstancerStarfield();
        Rocket::Core::Factory::RegisterDecoratorInstancer("starfield", decorator_instancer);
        decorator_instancer->RemoveReference();
    */

    // Initialise the event instancer and handlers.
    EventInstancer* event_instancer = new EventInstancer();
    Rocket::Core::Factory::RegisterEventListenerInstancer(event_instancer);
    event_instancer->RemoveReference();

    EventManager::RegisterEventHandler("light_point_editor", new EventHandlerLightPointEditor());
    EventManager::RegisterEventHandler("emissive_light_editor", new EventHandlerEmissiveLightEditor());
    EventManager::RegisterEventHandler("toolbar", new EventHandlerToolbar());

    //EventManager::RegisterEventHandler("generate_maze", new EventHandlerGenerateMaze());

    //all the windows
    std::vector<Rocket::Core::ElementDocument*> WindowList;
    WindowList.push_back(EventManager::LoadWindow("game"));
    WindowList.push_back(EventManager::LoadWindow("light_point_editor"));
    WindowList.push_back(EventManager::LoadWindow("emissive_light_editor"));
    WindowList.push_back(EventManager::LoadWindow("toolbar"));


    for(auto i : WindowList)
    {
        if(i == nullptr)
        {
            Rocket::Core::Log::Message(Rocket::Core::Log::LT_ERROR, "NULL Window!");
            Run = false;
            break;
        }
    }

    // Start the game.
    if (Run)
    {
        //KeydownListener::RegisterKeydownObject(Context->GetDocument("light_point_editor"));
        Event keydownevent("");
        Context->GetDocument("light_point_editor")->AddEventListener("keydown", &keydownevent);
        Context->GetDocument("emissive_light_editor")->AddEventListener("keydown", &keydownevent);
        while(render_window.isOpen())
        {
            render_window.clear();

            while(render_window.pollEvent(event))
            {
                switch (event.type)
                {
                case sf::Event::Resized:
                    Context->SetDimensions(Rocket::Core::Vector2i(event.size.width, event.size.height));
                    Renderer.Resize(Rocket::Core::Vector2i(event.size.width, event.size.height));
                    break;

                case sf::Event::MouseMoved:
                    Context->ProcessMouseMove(event.mouseMove.x, event.mouseMove.y,
                                              SystemInterface.GetKeyModifiers(&render_window));
                    break;
                case sf::Event::MouseButtonPressed:
                    Context->ProcessMouseButtonDown(event.mouseButton.button,
                                                    SystemInterface.GetKeyModifiers(&render_window));
                    break;
                case sf::Event::MouseButtonReleased:
                    Context->ProcessMouseButtonUp(event.mouseButton.button,
                                                  SystemInterface.GetKeyModifiers(&render_window));
                    break;
                case sf::Event::MouseWheelMoved:
                    Context->ProcessMouseWheel(event.mouseWheel.delta,
                                               SystemInterface.GetKeyModifiers(&render_window));
                    break;
                case sf::Event::TextEntered:
                    if (event.text.unicode > 32)
                        Context->ProcessTextInput(event.text.unicode);
                    break;
                case sf::Event::KeyPressed:
                    Context->ProcessKeyDown(SystemInterface.TranslateKey(event.key.code),
                                            SystemInterface.GetKeyModifiers(&render_window));
                    break;
                case sf::Event::KeyReleased:
                    if(event.key.code == sf::Keyboard::F8)
                    {
                        Rocket::Debugger::SetVisible(!Rocket::Debugger::IsVisible());
                    };

                    //Hide UI
                    if(event.key.code == sf::Keyboard::F4)
                    {
                        GameDetails::HideUI = !GameDetails::HideUI;
                    };

                    Context->ProcessKeyUp(SystemInterface.TranslateKey(event.key.code),
                                          SystemInterface.GetKeyModifiers(&render_window));
                    break;
                case sf::Event::Closed:
                    Shell::RequestExit();
                    break;
                }
                /*
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                    camera.move(0, -10);
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                    camera.move(0, 10);
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                    camera.move(-10, 0);
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                    camera.move(10, 0);
                    */
            }
            //hide UI

            if(GameDetails::HideUI)
            {
                for(auto i: WindowList)
                {
                    if(i->GetId() != "game")
                        i->Hide();
                }
            }
            else
            {
                for(auto i: WindowList)
                {
                    if(!i->IsVisible())
                        i->Show();
                }
            }


            Context->Update();

            render_window.pushGLStates();
            Context->Render();
            render_window.popGLStates();

            render_window.display();

            render_window.setView(camera);
        }
    }

// Release the event handlers.
    EventManager::Shutdown();

// Shutdown Rocket.
    Context->RemoveReference();
    Rocket::Core::Shutdown();

    return 0;
}
