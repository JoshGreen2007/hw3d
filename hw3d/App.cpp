#include "App.h"

// App.cpp
// A tiny explanation for beginners:
// This file implements the `App` class declared in App.h. The `App` wraps the
// main application loop and uses the `Window` and `Graphics` classes to render
// frames. `DoFrame` is called every loop and should contain the update and
// render logic for a single frame.

App::App()
	:
	wnd( 800,600,"The Donkey Fart Box" )
{}

int App::Go()
{
	// The main loop: process OS messages and render when idle
	while( true )
	{
		// Process all pending window messages. If ProcessMessages returns a
		// value then the user requested the application to quit; return that
		// as the process exit code.
		if( const auto ecode = Window::ProcessMessages() )
		{
			return *ecode; // exit code
		}
		// No quit message received: perform a single frame's work
		DoFrame();
	}
}

void App::DoFrame()
{
	// Example of simple animation: use the high-resolution timer to compute
	// a varying parameter. Here it's used as a rotation angle passed to the
	// graphics system.
	const float b = sin( timer.Peek() ) / 2.0f + 0.5f;

	// Clear the screen to black (red,green,blue)
	wnd.Gfx().ClearBuffer( 0.0f,0.0f,0.0f );

	// Draw the test mesh / geometry. We pass an angle and a translation
	// computed from the mouse position to demonstrate transformations.
	wnd.Gfx().DrawTestTriangle
	(
		timer.Peek(), // rotation angle in radians
		wnd.mouse.GetPosX() / 400.0f - 1.0f, // normalized X in [-1,+1]
		-wnd.mouse.GetPosY() / 300.0f + 1.0f // normalized Y in [-1,+1], inverted
	);

	wnd.Gfx().DrawTestTriangle
	(
		-timer.Peek(),
		0.0f, 
		0.0f
	);
	// Present what we've drawn this frame to the screen
	wnd.Gfx().EndFrame();
}
