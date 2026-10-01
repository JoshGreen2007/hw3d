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
#include <exception>
#include <string>

// ====================================================================================
// ChiliException
//
// This is a small helper exception class used throughout the tutorial code to
// carry file/line information and to provide readable error messages. It
// derives from std::exception so it can be used in try/catch blocks normally.
//
// For beginners:
// - `GetOriginString()` returns a short string like "(filename.cpp:123)"
//   describing where the exception was created.
// - `what()` returns a complete human-readable string that includes the
//   exception type and the origin string.
// ====================================================================================
class ChiliException : public std::exception
{
public:
	// Construct with the source code line and file where the exception was thrown
	ChiliException( int line,const char* file ) noexcept;

	// Standard exception message getter. Implementations return a readable
	// message that includes the type and the origin (file:line).
	const char* what() const noexcept override;

	// Returns a short type string such as "Chili Exception"
	virtual const char* GetType() const noexcept;

	// Accessors for the saved source location
	int GetLine() const noexcept;
	const std::string& GetFile() const noexcept;

	// Builds a small origin string combining file and line.
	std::string GetOriginString() const noexcept;

private:
	int line;              // source line where exception was created
	std::string file;      // source filename
protected:
	mutable std::string whatBuffer; // storage for the `what()` C-string
};
