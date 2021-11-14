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
