

#include "ShellSFML.h"
#include <Rocket/Core/FontDatabase.h>
#include <Rocket/Core.h>
#include "ShellFileInterface.h"

#ifdef WINDOWS
    #include <direct.h>
    #define GetCurrentDir _getcwd
#else
    #include <unistd.h>
    #define GetCurrentDir getcwd
 #endif

sf::RenderWindow* Shell::render_window;

sf::Clock Shell::Clock;

sf::Time Shell::Time;

static bool activated = true;

static bool running = false;

static ShellFileInterface* file_interface = NULL;

bool Shell::Initialise(const Rocket::Core::String& path)
{
    file_interface = new ShellFileInterface(path);
    Rocket::Core::SetFileInterface(file_interface);
}

void Shell::Shutdown()
{
    delete file_interface;
    file_interface = NULL;
}

bool Shell::OpenWindow(const std::string &title, int Width, int Height)
{
    render_window = new sf::RenderWindow(sf::VideoMode(Width, Height), title);

    if(!render_window)
    {
        printf("Could not open window\n");
        return false;
    }

    return true;
}

bool Shell::OpenWindow(sf::RenderWindow *window)
{
    if(window != NULL)
        render_window = window;
    else
        return false;

    return true;
}

void Shell::CloseWindow()
{
    render_window->close();
}

sf::RenderWindow* Shell::GetWindowHandle()
{
    return render_window;
}

/// Loads the default fonts from the given path.
void Shell::LoadFonts(const std::string &directory)
{
	Rocket::Core::String font_names[4];
	font_names[0] = "Delicious-Roman.otf";
	font_names[1] = "Delicious-Italic.otf";
	font_names[2] = "Delicious-Bold.otf";
	font_names[3] = "Delicious-BoldItalic.otf";

	for (int i = 0; i < sizeof(font_names) / sizeof(Rocket::Core::String); i++)
	{
		Rocket::Core::FontDatabase::LoadFontFace(Rocket::Core::String(directory.c_str()) + font_names[i]);
	}
}

float Shell::GetElapsedTime()
{
    Time = Clock.getElapsedTime();

    return Time.asSeconds();
}

void Shell::EventLoop(ShellIdleFunction idle_function)
{
    running = true;

    while (running)
	{
		idle_function();
	}
}

void Shell::RequestExit()
{
    //running = false;
    render_window->close();
    //delete render_window;
    render_window = NULL;
}

void Shell::DisplayError(const char* fmt, ...)
{
}

void Shell::Log(const char* fmt, ...)
{
}
