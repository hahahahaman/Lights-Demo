#ifndef ROCKETSHELL_H
#define ROCKETSHELL_H

#include <string>
#include <vector>

#include <Rocket/Core/Types.h>
#include <Rocket/Core/SystemInterface.h>
#include <SFML/Graphics.hpp>

/*
#ifdef ROCKET_PLATFORM_WIN32
#define PATH_SEPARATOR	";"
#else
#define PATH_SEPARATOR	":"
#endif
*/

/**
	Shell functions for creating windows, attaching OpenGL and handling input in a platform independent way.
	@author Lloyd Weehuizen
 */

class Shell
{
public:
	/// Initialise the shell.
	/// @param[in] path The path (relative to the current working directory) of the application's working directory.
	static bool Initialise(const Rocket::Core::String& path);
	/// Shutdown the shell.
	static void Shutdown();

	/// Loads the default fonts from the given path.
	static void LoadFonts(const std::string &directory);

	/// Open a platform specific window, optionally initialising an OpenGL Context on it.
	/// @param[in] title Title of the window.
	/// @param[in] attach_opengl Attach and opengl Context to the window.
	static bool OpenWindow(const std::string &title, int Width, int Height);
	static bool OpenWindow(sf::RenderWindow *window);
	/// Close the active window.
	static void CloseWindow();

	static sf::RenderWindow* GetWindowHandle();

	/// Run the event loop, calling the idle function every frame.
	typedef void (*ShellIdleFunction)();
	static void EventLoop(ShellIdleFunction idle_function);
	static void RequestExit();

	/// Display an error message.
	static void DisplayError(const char* fmt, ...);
	/// Log a message to the debugger.
	static void Log(const char* fmt, ...);

	/// Get the number of seconds that have passed since shell startup.
	static float GetElapsedTime();

private:

    static sf::RenderWindow* render_window;

	static sf::Clock Clock;

	static sf::Time Time;
};

#endif
