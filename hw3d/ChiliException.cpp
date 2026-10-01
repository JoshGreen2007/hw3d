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
// ChiliException.cpp
// Implementation of the simple ChiliException helper. This file implements
// the methods declared in ChiliException.h. The class exists to provide
// nicer error messages during development and to carry file/line information
// where the exception was thrown.

#include "ChiliException.h"
#include <sstream>


ChiliException::ChiliException( int line,const char* file ) noexcept
	:
	line( line ),
	file( file )
{}

// `what()` builds a single std::string with useful information and returns
// a pointer to the internal buffer. This is the string that will be shown
// if the exception is printed or caught and logged.
const char* ChiliException::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl
		<< GetOriginString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

// A short type name for this class. Override this in derived exception
// classes to provide more specific type information.
const char* ChiliException::GetType() const noexcept
{
	return "Chili Exception";
}

int ChiliException::GetLine() const noexcept
{
	return line;
}

const std::string& ChiliException::GetFile() const noexcept
{
	return file;
}

// Build a compact origin string that includes the file and line number. This
// helps to quickly identify where an exception was created.
std::string ChiliException::GetOriginString() const noexcept
{
	std::ostringstream oss;
	oss << "[File] " << file << std::endl
		<< "[Line] " << line;
	return oss.str();
}
