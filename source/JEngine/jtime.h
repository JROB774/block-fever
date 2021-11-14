#ifndef INCLUDE_J_TIME
#define INCLUDE_J_TIME

#include "jerror.h"

/// <J_TIMER> /////////////////////////////////////////////////////////////////

class J_Timer
{
	public:

        /// DESCRIPTION@
		// The constructor.
		// First: Create a blank timer with default values.
		// Second: Copy the data from one timer into another.
		// Third: Move the data from one timer into another.
		//
		/// ARGUMENTS:
		// Second: The timer to copy from.
		// Third: The timer to move from.
		//
		J_Timer(void);
		J_Timer(const J_Timer&) = default;
        J_Timer(J_Timer&&) = default;

        /// DESCRIPTION:
		// The assignment operator.
		// First: Copy the data from one timer into another.
		// Second: Move the data from one timer into another.
		//
		/// ARGUMENTS:
		// First: The timer to copy from.
		// Seocnd: The timer to move from.
		//
		/// RETURN VALUES:
		// First: The copied data.
		// Second: The moved data.
		//
		J_Timer& operator=(const J_Timer&) = default;
		J_Timer& operator=(J_Timer&&) = default;

        /// DESCRIPTION:
        // Start the timer.
        //
		void start(void);

        /// DESCRIPTION:
        // Pause or unpause the timer based on whether it is already paused
        // or not.
        // If the timer has not been started this does nothing.
        //
        /// RETURN VALUES:
        // true = The timer is paused now.
        // false = The timer is unpaused now.
        //
		bool pause(void);

        /// DESCRIPTION:
        // Stop the timer and reset its time stored.
        //
		void stop(void);

        /// DESCRIPTION:
		// Get the number of ticks the timer has been running for.
		//
		/// RETURN VALUES:
		// Return the number of ticks the timer's been running.
		//
		Uint32 getTicks(void) const;

        /// DESCRIPTION:
        // Comparison operators.
        // Does the specified comparison between two timer objects.
        //
        /// ARGUMENTS:
        // The two objects to do the comparison on.
        //
        /// RETURN VALUES:
        // Whether the condition is true or false.
        //
        friend bool operator==(const J_Timer&, const J_Timer&);
        friend bool operator!=(const J_Timer&, const J_Timer&);
        friend bool operator<(const J_Timer&, const J_Timer&);
        friend bool operator>(const J_Timer&, const J_Timer&);
        friend bool operator<=(const J_Timer&, const J_Timer&);
        friend bool operator>=(const J_Timer&, const J_Timer&);

        /// DESCRIPTION:
		// The destructor.
		//
		~J_Timer(void) = default;

	private:

		// The state values of the timer.
		bool started, paused;
		// The tick storage for the timer.
		Uint32 startTicks, pauseTicks;
};

/// </J_TIMER> ////////////////////////////////////////////////////////////////

//
//
//

/// <J_COUNTER> ///////////////////////////////////////////////////////////////

/*
class J_Counter
{
	public:

        /// DESCRIPTION:
	    // The constructor.
	    // First: Create a blank counter with default values.
	    // Second: Copy the data from one counter into another.
	    // Third: Move the data from one coutner into another.
	    // Fourth: Create a counter with the values passed.
	    //
	    /// ARGUMENTS:
	    // Second: The counter to copy from.
	    // Third: The counter to move from.
	    // Fourth: The counter's time and tick values.
	    //
        J_Counter(void) = default;
        J_Counter(const J_Counter&) = default;
        J_Counter(J_Counter&&) = default;
        J_Counter(const int, const int);

        /// DESCRIPTION:
        // The assignment operator.
        // First: Copy the data from one counter into another.
        // Second: Move the data from one counter into another.
        //
        /// ARGUMENTS:
        // First: The counter to copy from.
        // Second: The counter to move from.
        //
        /// RETURN VALUES:
        // First: The copied data.
        // Second: The moved data.
        J_Counter& operator=(const J_Counter&) = default;
        J_Counter& operator=(J_Counter&&) = default;

        /// DESCRIPTION:
        // Set the counter's time and tick values.
        // If the value passed for the new tick value is TICK_UNCHANGED then
        // the tick value is not changed.
        // A tick value can't be less than one.
        //
        /// ARGUMENTS:
        // The time for the counter.
        // The tick amount to decrement each time.
        //
        void set(const int, const int);

        /// DESCRIPTION:
        // Add more time on to the counter's current time.
        //
        /// ARGUMENTS:
        // The amount of time to add. Must be positive.
        //
        /// RETURN VALUES:
        // Return the new time.
        //
        int add(const int);

        /// DESCRIPTION:
        // Tick down the time by whatever the tick amount is set to.
        // The time value will never go below zero.
        //
        void tick(void);

        /// DESCRPTION:
        // Get the current time left in the counter.
        //
        /// RETURN VALUES:
        // Return the counter's current time.
        //
        int getTime(void) const;

        /// DESCRIPTION:
        // Get the amount decemented per tick.
        //
        /// RETURN VALUES:
        // Return the counter's tick amount.
        //
        int getTickAmount(void) const;

        /// DESCRIPTION:
        // Get whether the counter is done counting or not.
        //
        /// RETURN VALUES:
        // true = The counter is done.
        // false = The counter is still counting.
        //
        bool isDone(void) const;

        /// DESCRIPTION:
        // Comparison operators.
        // Does the specified comparison between two counter objects.
        //
        /// ARGUMENTS:
        // The two objects to do the comparison on.
        //
        /// RETURN VALUES:
        // Whether the condition is true or false.
        //
        friend bool operator==(const J_Counter&, const J_Counter&);
        friend bool operator!=(const J_Counter&, const J_Counter&);
        friend bool operator<(const J_Counter&, const J_Counter&);
        friend bool operator>(const J_Counter&, const J_Counter&);
        friend bool operator<=(const J_Counter&, const J_Counter&);
        friend bool operator>=(const J_Counter&, const J_Counter&);

        /// DESCRIPTION:
        // The destructor.
        //
        ~J_Counter(void) = default;

	private:

	    // The value to pass to set() to keep the tick amount the same.
	    static const int TICK_UNCHANGED;
		// The current time in the counter.
        int time;
        // The amount of time to pass per tick.
        int tickAmount;
};
*/

/// </J_COUNTER> //////////////////////////////////////////////////////////////

#endif // INCLUDE_J_TIME
