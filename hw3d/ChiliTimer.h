#pragma once
#include <chrono>

class ChiliTimer
{
public:
    // ====================================================================================
	// ChiliTimer
	//
	// Tiny helper class that wraps a high-resolution steady clock. It is used to
	// measure elapsed time between frames and to produce smooth animations.
	//
	// Methods:
	// - `Mark()` resets the internal timer and returns the time (in seconds)
	//    since the last mark.
	// - `Peek()` returns the time (in seconds) since the last mark without
	//    resetting the timer.
	// ====================================================================================
	ChiliTimer() noexcept;
	float Mark() noexcept;
	float Peek() const noexcept;
private:
	std::chrono::steady_clock::time_point last;
};