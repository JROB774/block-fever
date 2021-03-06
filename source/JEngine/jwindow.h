#ifndef INCLUDE_J_WINDOW
#define INCLUDE_J_WINDOW

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
        // Update the window each frame.
        //
        static void step(void);

        /// DESCRIPTION:
        // Shows the window if it is currently hidden.
        //
        static void show(void);

        /// DESCRIPTION:
        // Hides the window if it is currently visible.
        //
        static void hide(void);

        /// DESCRIPTION:
        // Set whether the fullscreen is on or off.
        //
        /// ARGUMENTS:
        // The fullscreen state.
        //
        static void setFullscreen(const bool);

        /// DESCRIPTION:
        // Toggle whether fullscreen is on or off.
        //
        static void toggleFullscreen(void);

        /// DESCRIPTION:
        // Set the new width and height of the window.
        //
        /// ARGUMENTS:
        // New width of height.
        //
        static void setWidth(int);
        static void setHeight(int);

        /// DESCRIPTION:
        // Updates the scale of the screen.
        //
        /// ARGUMENTS:
        // Whether to update the render scale and viewport or not.
        //
        static void updateScale(const bool);

        /// DESCRIPTION:
        // Update the renderer's viewport
        //
        /// ARGUMENTS:
        // The scale to adjust the viewport for.
        //
        static void updateViewport(const int);

        /// DESCRIPTION:
        // Get the screen's dimensions after being scaled within the window.
        //
        /// RETURN VALUES:
        // The screen's scaled width or height.
        //
        static int getScreenWidthScaled(void);
        static int getScreenHeightScaled(void);

        /// DESCRIPTION:
        // Get the screen's dimensions.
        //
        /// RETURN VALUES:
        // The screen's width or height.
        //
        static int getScreenWidth(void);
        static int getScreenHeight(void);

        /// DESCRIPTION:
        // Get the window's dimensions (when in fullscreen it returns the size as if it were windowed).
        //
        /// RETURN VALUES:
        // The window's width or height.
        //
        static int getWidth(void);
        static int getHeight(void);

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
        // The window's start dimensions.
        static int startWidth, startHeight;
        // The window's dimensions.
        static int cachedWidth, cachedHeight;
        // The screen's scaled dimensions.
        static int screenWidthScaled, screenHeightScaled;
        // The screen's dimensions.
        static int screenWidth, screenHeight;
        // The fullscreen flag.
        static bool fullscreen;
        // The raw SDL window itself.
        static SDL_Window* window;
};

/// </J_WINDOW> ///////////////////////////////////////////////////////////////

#endif // INCLUDE_J_WINDOW
