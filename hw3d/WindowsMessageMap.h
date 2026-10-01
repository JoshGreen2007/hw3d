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
#pragma once
#include <unordered_map>
#include "ChiliWin.h"
#include <string>

// ====================================================================================
// WindowsMessageMap
//
// Small utility that provides human-readable names for common Win32 message
// codes. Useful when debugging message handling to print the message name
// rather than a numeric code.
// ====================================================================================
class WindowsMessageMap
{
public:
	WindowsMessageMap() noexcept;
	// Returns a human-readable string for a given message code and parameters.
	std::string operator()( DWORD msg,LPARAM lp,WPARAM wp ) const noexcept;
private:
	std::unordered_map<DWORD,std::string> map;
};
