#include "jtime.h"

/// <J_TIMER> /////////////////////////////////////////////////////////////////

J_Timer::J_Timer (void) : started(false), paused(false), startTicks(0), pauseTicks(0) {}



void J_Timer::start (void) {

    // Starts the timer.
    started = true, paused = false;
    startTicks = SDL_GetTicks(), pauseTicks = 0;
}

bool J_Timer::pause (void) {

    // If the timer is unpaused then pause it and vice versa.
	if (started && !paused) {

		paused = true;
		pauseTicks = SDL_GetTicks() - startTicks;
		startTicks = 0;
	}
	else if (started && paused) {

		paused = false;
		startTicks = SDL_GetTicks() - pauseTicks;
		pauseTicks = 0;
	}

    // Return whether the timer is paused or not.
	return paused;
}

void J_Timer::stop (void) {

    // Stop and reset the timer.
    started = false, paused = false;
    startTicks = 0, pauseTicks = 0;
}



Uint32 J_Timer::getTicks (void) const {

    // Return how long the timer has been running for, in ticks.
	Uint32 ticks = 0;
	if (started) { ticks = (paused) ? pauseTicks : (SDL_GetTicks() - startTicks); }

	return ticks;
}



bool operator== (const J_Timer& arg_lhs, const J_Timer& arg_rhs) { return (arg_lhs.getTicks() == arg_rhs.getTicks()) ? true : false; }

bool operator!= (const J_Timer& arg_lhs, const J_Timer& arg_rhs) { return !operator==(arg_lhs, arg_rhs); }

bool operator< (const J_Timer& arg_lhs, const J_Timer& arg_rhs) { return (arg_lhs.getTicks() < arg_rhs.getTicks()) ? true : false; }

bool operator> (const J_Timer& arg_lhs, const J_Timer& arg_rhs) { return operator<(arg_rhs, arg_lhs); }

bool operator<= (const J_Timer& arg_lhs, const J_Timer& arg_rhs) { return !operator>(arg_lhs, arg_rhs); }

bool operator>= (const J_Timer& arg_lhs, const J_Timer& arg_rhs) { return !operator<(arg_lhs, arg_rhs); }

/// </J_TIMER> ////////////////////////////////////////////////////////////////

//
//
//
//

/// <J_COUNTER> ///////////////////////////////////////////////////////////////

/*
const int J_Counter::TICK_UNCHANGED = 0;



J_Counter::J_Counter (const int arg_time, const int arg_tick) {

    // Set the counter's time to run for and how much it decrements per tick.
    time = (arg_time < 0) ? 0 : arg_time;
    tickAmount = (arg_tick <= TICK_UNCHANGED) ? tickAmount : arg_tick;
    if (tickAmount <= 0) { tickAmount = 1; }
}



void J_Counter::set (const int arg_time, const int arg_tick) {

    // Set the counter's time to run for and how much it decrements per tick.
    time = (arg_time < 0) ? 0 : arg_time;
    tickAmount = (arg_tick <= TICK_UNCHANGED) ? tickAmount : arg_tick;
    if (tickAmount <= 0) { tickAmount = 1; }
}

int J_Counter::add (const int arg_time) {

    // Add more time to the counter's current time.
    time += (arg_time < 0) ? 0 : arg_time;

    // Return the new time.
    return time;
}

void J_Counter::tick (void) {

    // Ticks down the time on the timer.
    time -= (time > 0) ? tickAmount : 0;
    time = (time < 0) ? 0 : time;
}



int J_Counter::getTime (void) const { return time; }

int J_Counter::getTickAmount (void) const { return tickAmount; }

bool J_Counter::isDone (void) const { return (time <= 0) ? true : false; }



bool operator== (const J_Counter& arg_lhs, const J_Counter& arg_rhs) { return (arg_lhs.time == arg_rhs.time) ? true : false; }

bool operator!= (const J_Counter& arg_lhs, const J_Counter& arg_rhs) { return !operator==(arg_lhs, arg_rhs); }

bool operator< (const J_Counter& arg_lhs, const J_Counter& arg_rhs) { return (arg_lhs.time == arg_rhs.time) ? true : false; }

bool operator> (const J_Counter& arg_lhs, const J_Counter& arg_rhs) { return operator<(arg_rhs, arg_lhs); }

bool operator<= (const J_Counter& arg_lhs, const J_Counter& arg_rhs) { return !operator>(arg_lhs, arg_rhs); }

bool operator>= (const J_Counter& arg_lhs, const J_Counter& arg_rhs) { return !operator<(arg_lhs, arg_rhs); }
*/

/// </J_COUNTER> //////////////////////////////////////////////////////////////
