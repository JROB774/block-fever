#ifndef INCLUDE_J_WINDOW
#define INCLUDE_J_WINDOW

#include <sstream>
#include <iostream>
#include "jrender.h"

/// <J_WINDOW> ////////////////////////////////////////////////////////////////

class J_Window
{
    public:

        /// DESCRIPTION:
        // The constructor.
        //
        J_Window(void) = delete;
        J_Window(const J_Window&) = delete;
        J_Window(J_Window&&) = delete;

        /// DESCRIPTION:
        // The assignment operator.
        //
        J_Window& operator=(const J_Window&) = delete;
        J_Window& operator=(J_Window&&) = delete;

        /// DESCRIPTION:
        // Initialise the window.
        // Create the window itself using data from the window data file.
        //
        static void initialise(void);

        /// DESCRIPTION:
        // Handle all window related events.
        //
        /// ARGUMENTS:
        // The event handler.
        //
        static void handle(const SDL_Event&, const bool);

        /// DESCRIPTION:
        // Set the window's icon.
        //
        /// ARGUMENTS:
        // The window icon file.
        //
        static void setIcon(const std::string);

        /// DESCRIPTION:
        // Set the screen scale to the specified value.
        //
        /// ARGUMENTS:
        // The new screen scale.
        //
        static void setScreenScale(const int);

        /// DESCRIPTION:
        // Either increase or decrease the screen's render scale.
        //
        // static void increaseScreenScale(void);
        // static void decreaseScreenScale(void);

        /// DESCRIPTION:
        // Toggle whether fullscreen is on or off.
        //
        static void toggleFullscreen(void);

        /// DESCRIPTION:
        // Update the renderer's viewport
        //
        static void updateViewport(void);

        /// DESCRIPTION:
        // Get the window's dimensions.
        //
        /// RETURN VALUES:
        // The window's width or height.
        //
        static int getWidth(void);
        static int getHeight(void);

        /// DESCRIPTION:
        // Get the screen's dimensions.
        //
        /// RETURN VALUES:
        // The screen's width or height.
        //
        static int getScreenWidth(void);
        static int getScreenHeight(void);

        /// DESCRIPTION:
        // Get the desktop's dimensions.
        //
        /// RETURN VALUES:
        // The desktop's width or height.
        //
        static int getDesktopWidth(void);
        static int getDesktopHeight(void);

        /// DESCRIPTION:
        // Get the screen's render scale.
        //
        /// RETURN VALUES:
        // The screen's render scale.
        //
        static int getScreenScale(void);

        /// DESCRIPTION:
        // Get the fullscreen flag.
        //
        /// RETURN VALUES:
        // True if fullscreen is on.
        // False if fullscreen is off.
        //
        static bool getFullscreen(void);

        /// DESCRIPTION:
        // Get the SDL window.
        //
        /// RETURN VALUES:
        // Return the SDL window.
        //
        static SDL_Window* getWindow(void);

        /// DESCRIPTION:
        // Terminate the window.
        //
        static void terminate(void);

        /// DESCRIPTION:
        // The destructor.
        //
        ~J_Window(void) = delete;

    private:

        // The file containing all the window data.
        static const std::string WINDOW_FILE;
        // The window title.
        static std::string title;
        // The window's dimensions.
        static int width, height;
        // The screen's dimensions.
        static int screenWidth, screenHeight;
        // The desktop's dimensions.
        static int desktopWidth, desktopHeight;
        // The screen scale.
        static int screenScale;
        // The fullscreen flag.
        static bool fullscreen;
        // The raw SDL window itself.
        static SDL_Window* window;
};

/// </J_WINDOW> ///////////////////////////////////////////////////////////////

#endif // INCLUDE_J_WINDOW
