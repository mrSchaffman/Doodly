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

//#pragma comment(linker,"\"/manifestdependency:type='win32' \
//name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
//processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#ifndef UNICODE
#define UNICODE
#endif // UNICODE

#include<Windows.h>
#include"MainWindow.h"
#include"uxtheme.h"			// SetWindowTheme


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPInstance, PWSTR pCmdLine, int nCmdShow)
{
	MainWindow win;

	if (!win.Create(L"Doodle App", WS_OVERLAPPEDWINDOW, WS_EX_APPWINDOW, 400, 400, 500, 500))
	{
		return 0;
	}
	//HWND hwndButton = CreateWindowEx(
	//	0,
	//	L"BUTTON",  // Predefined class; Unicode assumed
	//	L"OK",      // Button text
	//	WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,  // Styles
	//	10,         // x position
	//	100,         // y position
	//	50,        // Button width
	//	50,        // Button height
	//	win.Window(),     // Parent window
	//	NULL,       // No menu.
	//	(HINSTANCE)GetWindowLongPtr(win.Window(), GWLP_HINSTANCE),
	//	NULL      // Pointer not needed.
	//);
	//
	////HRESULT hr  = SetWindowTheme(hwndButton, L" ", L" ");		

	//HWND hwndButton2 = CreateWindowEx(
	//	0,
	//	L"BUTTON",  // Predefined class; Unicode assumed
	//	L"GROUP BOX",      // Button text
	//	WS_TABSTOP | WS_VISIBLE | WS_CHILD | /*BS_DEFPUSHBUTTON*/ BS_GROUPBOX,  // Styles
	//	60,         // x position
	//	10,         // y position
	//	200,        // Button width
	//	150,        // Button height
	//	win.Window(),     // Parent window
	//	NULL,       // No menu.
	//	(HINSTANCE)GetWindowLongPtr(win.Window(), GWLP_HINSTANCE),
	//	NULL      // Pointer not needed.
	//);
	//HWND hwndButton3 = CreateWindowEx(
	//	0,
	//	L"BUTTON",  // Predefined class; Unicode assumed
	//	L"OK TEST",      // Button text
	//	WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_COMMANDLINK,  // Styles
	//	10,         // x position
	//	300,         // y position
	//	150,        // Button width
	//	50,        // Button height
	//	win.Window(),     // Parent window
	//	NULL,       // No menu.
	//	(HINSTANCE)GetWindowLongPtr(win.Window(), GWLP_HINSTANCE),
	//	NULL      // Pointer not needed.
	//);


	//// create a scrollbar
	//RECT rect;

	//// Get the dimensions of the parent window's client area;
	//if (!GetClientRect(win.Window(), &rect))
	//	return NULL;

	//int sbHeight = 20;
	//// Create the scroll bar.
	//HWND scr = CreateWindowEx(
	//	0,                      // no extended styles 
	//	L"SCROLLBAR",           // scroll bar control class 
	//	(PTSTR)NULL,           // no window text 
	//	WS_CHILD | WS_VISIBLE   // window styles  
	//	| SBS_HORZ,         // horizontal scroll bar style 
	//	rect.left,              // horizontal position 
	//	rect.bottom - sbHeight, // vertical position 
	//	rect.right,             // width of the scroll bar 
	//	sbHeight,               // height of the scroll bar
	//	win.Window(),             // handle to main window 
	//	(HMENU)NULL,           // no menu 
	//	(HINSTANCE)GetWindowLongPtr(win.Window(), GWLP_HINSTANCE),
	//	(PVOID)NULL            // pointer not needed 
	//);

	//HWND hwndCommandLink = CreateWindowEx(
	//	0,
	//	L"BUTTON",  // Predefined class; Unicode assumed
	//	L"",        // Text will be defined later
	//	WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_COMMANDLINK,  // Styles
	//	200,        // x position 
	//	10,         // y position 
	//	200,        // Button width
	//	100,        // Button height
	//	win.Window(),             // handle to main window 
	//	NULL,       // No menu
	//	(HINSTANCE)GetWindowLongPtr(win.Window(), GWLP_HINSTANCE),
	//	NULL);      // Pointer not needed
	//SendMessage(hwndCommandLink, WM_SETTEXT, 0, (LPARAM)L"Command link");
	//SendMessage(hwndCommandLink, BCM_SETNOTE, 0, (LPARAM)L"with note");


	ShowWindow(win.Window(), nCmdShow);

	// enter the message loop: The application needs a loop to retrieve the messages and dispatch them to the correct windows.
	MSG message = {};
	while (GetMessage(&message, NULL, 0, 0) > 0)
	{
		// exemple of message: #define WM_LBUTTONDOWN    0x0201

		TranslateMessage(&message);
		DispatchMessage(&message);
	}


	return 0;
}
