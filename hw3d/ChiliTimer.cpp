// ChiliTimer.cpp
// Simple implementation of the ChiliTimer helper. This wraps a steady_clock
// time point to offer convenient functions for frame timing.

#include "ChiliTimer.h"

using namespace std::chrono;

ChiliTimer::ChiliTimer() noexcept
{
	// Initialize the timer to now.
	last = steady_clock::now();
}

// Mark returns the time since the previous mark and resets the internal
// timestamp to now. Useful for computing per-frame delta times.
float ChiliTimer::Mark() noexcept
{
	const auto old = last;
	last = steady_clock::now();
	const duration<float> frameTime = last - old;
	return frameTime.count();
}

// Peek returns the time in seconds since the last mark without resetting the
// stored timestamp. Use this when you need to read elapsed time but don't
// want to restart the timer.
float ChiliTimer::Peek() const noexcept
{
	return duration<float>( steady_clock::now() - last ).count();
}
