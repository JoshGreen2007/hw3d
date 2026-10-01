/******************************************************************************************
*	Chili Direct3D Engine																  *
*	Copyright 2018 PlanetChili <http://www.planetchili.net>								  *
*																						  *
*	This file is part of Chili Direct3D Engine.											  *
*																						  *
*	Chili Direct3D Engine is free software: you can redistribute it and/or modify		  *
*	it under the terms of the GNU General Public License as published by				  *
*	the Free Software Foundation, either version 3 of the License, or					  *
*	(at your option) any later version.													  *
*																						  *
*	The Chili Direct3D Engine is distributed in the hope that it will be useful,		  *
*	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
*	GNU General Public License for more details.										  *
*																						  *
*	You should have received a copy of the GNU General Public License					  *
*	along with The Chili Direct3D Engine.  If not, see <http://www.gnu.org/licenses/>.    *
******************************************************************************************/
// Keyboard.cpp
// Implementation of the Keyboard helper class. This file defines how key and
// character events are stored and returned to the rest of the program.
//
#include "Keyboard.h"

// Returns whether the given virtual-key code is currently pressed.
bool Keyboard::KeyIsPressed( unsigned char keycode ) const noexcept
{
	return keystates[keycode];
}

// Return next key event (press/release) from the internal queue.
Keyboard::Event Keyboard::ReadKey() noexcept
{
	if( keybuffer.size() > 0u )
	{
		Keyboard::Event e = keybuffer.front();
		keybuffer.pop();
		return e;
	}
	else
	{
		return Keyboard::Event(); // invalid event
	}
}

bool Keyboard::KeyIsEmpty() const noexcept
{
	return keybuffer.empty();
}

// Return next character (text input) event from the queue.
char Keyboard::ReadChar() noexcept
{
	if( charbuffer.size() > 0u )
	{
		unsigned char charcode = charbuffer.front();
		charbuffer.pop();
		return charcode;
	}
	else
	{
		return 0; // no char available
	}
}

bool Keyboard::CharIsEmpty() const noexcept
{
	return charbuffer.empty();
}

// Clear pending key events
void Keyboard::FlushKey() noexcept
{
	keybuffer = std::queue<Event>();
}

// Clear pending character events
void Keyboard::FlushChar() noexcept
{
	charbuffer = std::queue<char>();
}

// Flush both key and char queues
void Keyboard::Flush() noexcept
{
	FlushKey();
	FlushChar();
}

// Auto-repeat toggling for keys. When autorepeat is enabled the OS will
// generate repeated WM_KEYDOWN messages while a key is held; disable it to
// only receive a single press and release pair.
void Keyboard::EnableAutorepeat() noexcept
{
	autorepeatEnabled = true;
}

void Keyboard::DisableAutorepeat() noexcept
{
	autorepeatEnabled = false;
}

bool Keyboard::AutorepeatIsEnabled() const noexcept
{
	return autorepeatEnabled;
}

// These methods are called by the Window class when the corresponding
// Win32 messages arrive. They update internal state and push events onto
// the queues for the application to consume.
void Keyboard::OnKeyPressed( unsigned char keycode ) noexcept
{
	keystates[keycode] = true;
	keybuffer.push( Keyboard::Event( Keyboard::Event::Type::Press,keycode ) );
	TrimBuffer( keybuffer );
}

void Keyboard::OnKeyReleased( unsigned char keycode ) noexcept
{
	keystates[keycode] = false;
	keybuffer.push( Keyboard::Event( Keyboard::Event::Type::Release,keycode ) );
	TrimBuffer( keybuffer );
}

void Keyboard::OnChar( char character ) noexcept
{
	charbuffer.push( character );
	TrimBuffer( charbuffer );
}

void Keyboard::ClearState() noexcept
{
	keystates.reset();
}

// Helper to keep queue sizes bounded so we don't use unbounded memory if the
// application doesn't read events fast enough.
template<typename T>
void Keyboard::TrimBuffer( std::queue<T>& buffer ) noexcept
{
	while( buffer.size() > bufferSize )
	{
		buffer.pop();
	}
}

