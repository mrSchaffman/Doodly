#pragma once
/*
	Copyright (C) 2022  Barth.Feudong
	Author can be contacted here: <https://github.com/mrSchaffman/Cpp-Doodle-App>

	This file is part of the Doodle project. using the Win32 API and The COM

	Doodle is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Doodle is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <https://www.gnu.org/licenses/>.

*/

// Mouse coordinates are given in physical pixels, but Direct2D expects device-independent pixels (DIPs). 
// To handle high-DPI settings correctly, I must translate the pixel coordinates into DIPs.
#include<Windows.h>
#include<d2d1.h>
class DPIConverter
{
public:
	static void Initilize(HWND hwnd)
	{
		// Get the Curretn DPI of the System associated with the Window
		float dpi = GetDpiForWindow(hwnd);
		defaultScale = dpi / 96.0f;		// standard DPI can be 96.0, 120.0, 144.0
	}

	template <typename T>
	static D2D1_POINT_2F PixelsToDIPs(T x, T y)
	{
		return D2D1::Point2F(static_cast<float>(x) / defaultScale, static_cast<float>(y) / defaultScale);
	}
private:
	static float defaultScale;
};

// supposed to be in the .cpp
float DPIConverter::defaultScale = 1.0f;