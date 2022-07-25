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
#include<Windows.h>


template <class TYPE>
class BaseWindow
{
public:
	// The Ctor of the Base Class.
	BaseWindow() : m_hwnd(NULL) { }

	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		TYPE *pThis = NULL;			// to be use as the State of the create Window.

		if (uMsg == WM_NCCREATE)	// This message is send before the WM_CREATE, so it is the best place to set the hwnd of the window to be created
		{
			CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;		// get the struct containing the info about the Window to be created.
			pThis = (TYPE*)pCreate->lpCreateParams;				// retreive the void* pointer specifyied when creating the Window with CreateWindowEx.

			SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pThis);	//Sets the user data associated with the window hwnd.

			pThis->m_hwnd = hwnd;

			return TRUE;	// If the application returns FALSE, the CreateWindow or CreateWindowEx function will return a NULL handle.
		}
		else
		{
			pThis = (TYPE*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		}
		if (pThis)
		{
			return pThis->HandleMessage(uMsg, wParam, lParam);
		}
		else
		{
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
	}



	BOOL Create(
		DWORD dwExStyle,
		PCWSTR lpWindowName,
		DWORD dwStyle,				// DWORD: Allocates and optionally initializes a double word (4 bytes) of storage for each initializer
		int x = CW_USEDEFAULT,
		int y = CW_USEDEFAULT,
		int nWidth = CW_USEDEFAULT,
		int nHeight = CW_USEDEFAULT,
		HWND hWndParent = 0,
		HMENU hMenu = 0
	)
	{
		WNDCLASS wc = { 0 };

		wc.lpfnWndProc = TYPE::WindowProc;
		wc.hInstance = GetModuleHandle(NULL);
		wc.lpszClassName = ClassName();
		wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);

		RegisterClass(&wc);

		m_hwnd = CreateWindowEx(
			dwExStyle,
			ClassName(),
			lpWindowName,
			dwStyle,
			x,
			y,
			nWidth,
			nHeight,
			hWndParent,
			hMenu,
			GetModuleHandle(NULL),			// HINSTANCE: A handle to the instance of the module to be associated with the window.
			this							// taking itself as state pointer.
		);

		return (m_hwnd ? TRUE : FALSE);
	}

	HWND Window() const { return m_hwnd; }

protected:

	virtual PCWSTR  ClassName() const = 0;
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;

	HWND m_hwnd;
};