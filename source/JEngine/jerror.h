#ifndef INCLUDE_J_ERROR
#define INCLUDE_J_ERROR

/// <J_ERROR> /////////////////////////////////////////////////////////////////

class J_Error
{
    public:

        /// DESCRIPTION:
        // The constructor.
        //
        J_Error(void) = delete;
        J_Error(const J_Error&) = delete;
        J_Error(J_Error&&) = delete;

        /// DESCRIPTION:
        // The assignment operator.
        //
        J_Error& operator=(const J_Error&) = delete;
        J_Error& operator=(J_Error&&) = delete;

        /// DESCRIPTION:
        // Initialise the error system.
        // If the system is already initialised calling this does nothing.
        // Terminate the program, with a failure state, if there was a problem
        // initialising the system and display a windows error message box to
        // inform the user.
        //
        static void initialise(void);

        /// DESCRIPTION:
        // Print an error message to the error log file and displays a windows
        // error message box to inform the user.
        // Terminate the program, with a failure state; if there was a problem
        // writing the error message to the file, or if the error system has not
        // been initialised.
        //
        /// ARGUMENTS:
        // The error key value which states which error to call.
        //
        static void log(const std::string);

        /// DESCRIPTION:
        // Terminate the error system.
        //
        static void terminate(void);

        /// DESCRIPTION:
        // The destructor.
        //
        ~J_Error(void) = delete;

    private:

        // The file containing all the error data.
        static const std::string ERROR_FILE;
        // The log of error information.
        static const std::string ERROR_LOG;
        // The total number of errors.
        static int total;
        // The different errors stored by their key.
        static std::unordered_map <std::string, std::string> error;

        /// DESCRIPTION:
        // The different types of error.
        //
        enum J_ErrorType
        {
            J_ERROR_TYPE_STD,
            J_ERROR_TYPE_SDL,
            J_ERROR_TYPE_IMG,
            J_ERROR_TYPE_MIX
        };

        /// DESCRIPTION:
        // Open a windows error message box and terminate the program
        //
        static inline void initialiseError(void);
        static inline void logError(void);
};

/// </J_ERROR> ////////////////////////////////////////////////////////////////

#endif // INCLUDE_J_ERROR
