#pragma once
#include "Window.h"
#include "ChiliTimer.h"
// ====================================================================================
// App.h
//
// The `App` class is a very small entry-point wrapper that owns a window and a
// high-resolution timer. It contains the main loop for the application and
// calls `DoFrame` every iteration to update and render a single frame.
//
// For beginners:
// - `Go()` implements the main loop: it processes OS messages and calls
//   `DoFrame` when there are no messages to process.
// - `DoFrame()` should perform game/update logic and call into the `Window`
//   and `Graphics` classes to render the frame.
// ====================================================================================

class App
{
public:
	App();
	// master frame / message loop
	int Go();
private:
	void DoFrame();
private:
	Window wnd;
	ChiliTimer timer;
};