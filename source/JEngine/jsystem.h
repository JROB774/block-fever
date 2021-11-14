#ifndef INCLUDE_J_SYSTEM
#define INCLUDE_J_SYSTEM

#include "jtime.h"
#include "jrender.h"
#include "jwindow.h"
#include "jcollision.h"
#include "jaudio.h"

/// <J_SYSTEM> ////////////////////////////////////////////////////////////////

/// DESCRIPTION:
// The different states the system can be in.
//
enum J_SystemState
{
    J_SYSTEM_STATE_INACTIVE,
    J_SYSTEM_STATE_RESETTING,
    J_SYSTEM_STATE_ACTIVE
};

class J_System
{
    public:

        /// DESCRIPTION:
        // The constructor.
        //
        J_System(void) = delete;
        J_System(const J_System&) = delete;
        J_System(J_System&&) = delete;

        /// DESCRIPTION:
        // The assignment operators.
        //
        J_System& operator=(const J_System&) = delete;
        J_System& operator=(J_System&&) = delete;

        /// DESCRIPTION:
        // Initialise the main system and all its sub-systems.
        //
        static void initialise(void);

        /// DESCRIPTION:
        // Check to see if there are pending events. if so it stores the current
        // event in the event handler to be handled.
        //
        /// RETURN VALUES:
        // 1 if there is a pending event.
        // 0 if there are no events available.
        //
        static int pollEvent(void);

        /// DESCRIPTION:
        // Handle system related events.
        //
        static void handle(void);

        /// DESCRIPTION:
        // The start and end of every step in the system's life.
        //
        static void stepBegin(void);
        static void stepEnd(void);

        /// DESCRIPTION:
        // Set the system's state to reset.
        //
        static void reset(void);

        /// DESCRIPTION:
        // Set the system's state to exit.
        //
        static void exit(void);

        /// DESCRIPTION:
        // Get the event handler so events can be handled elsewhere.
        //
        /// RETRUN VALUES:
        // The event handler.
        //
        static SDL_Event getEvent(void);

        /// DESCRIPTION:
        // Get the FPS timer for the main loop.
        //
        /// RETURN VALUES:
        // A pointer to the FPS timer.
        //
        static J_Timer* getFpsTimer(void);

        /// DESCRIPTION:
        // Get the cap timer for the main loop.
        //
        /// RETURN VALUES:
        // A pointer to the cap timer.
        //
        static J_Timer* getCapTimer(void);

        /// DESCRIPTION:
        // Get the current FPS cap.
        //
        /// RETURN VALUES:
        // The FPS cap.
        //
        static int getFps(void);

        /// DESCRIPTION:
        // Get whether the system is in debug mode or not.
        //
        /// RETURN VALUES:
        // The debug flag.
        //
        static bool isDebug(void);

        /// DESCRIPTION:
        // Get the current system state.
        //
        /// RETURN VALUES:
        // The system state.
        //
        static J_SystemState getState(void);

        /// DESCRIPTION:
        // Terminate the system.
        //
        static void terminate(void);

        /// DESCRIPTION:
        // The destructor.
        //
        ~J_System(void) = delete;

    private:

        // The system data file.
        static const std::string SYSTEM_FILE;
        // The config data file.
        static const std::string CONFIG_FILE;
        // The event handler.
        static SDL_Event event;
        // The timers used for FPS elated calculations.
        static J_Timer fpsTimer, capTimer;
        // The FPS cap for the system and the number of ticks per frame.
        static int fps, tpf;
        // The count for how many frames have passed.
        static int frameCount;
        // The average FPS for the system.
        static double averageFps;
        // The flag that states whether the system is in debug mode ro not.
        static bool debug;
        // The current state of the system.
        static J_SystemState state;
};

/// </J_SYSTEM> ///////////////////////////////////////////////////////////////

#endif // INCLUDE_J_SYSTEM
