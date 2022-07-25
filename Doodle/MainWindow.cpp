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

#include "MainWindow.h"
#include"DPIConverter.h"
#include<WindowsX.h>		// for GET_X_LPARAM and GET_Y_LPARAM
#include<dwmapi.h>		// for DwmExtendFrameIntoClientArea

LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	//	// Handle the window activation.
	//case WM_ACTIVATE:
	//	{
	//		// Extend the frame into the client area.
	//		MARGINS margins;

	//		margins.cxLeftWidth = 1;      // 8
	//		margins.cxRightWidth = 1;    // 8
	//		margins.cyBottomHeight = 1; // 20
	//		margins.cyTopHeight = 27;       // 27

	//		HRESULT hr = DwmExtendFrameIntoClientArea(m_hwnd, &margins);

	//		if (!SUCCEEDED(hr))
	//		{
	//			// Handle the error.
	//		}

	//	}		return 0;

	case WM_CREATE:
		if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory)))		// initialize the Factory
			return -1;	// The Creation of the Window failed.
		
		DPIConverter::Initilize(m_hwnd);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_LBUTTONDOWN:
		OnLButtonDown(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), (DWORD)(wParam));

	case WM_LBUTTONUP:
		OnLButtonUp();
		return 0;

	case WM_MOUSEMOVE:
		OnMouseMove(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), (DWORD)wParam);
		return 0;
	case WM_SIZE:
		Resize();
		return 0;

	case WM_PAINT:
		OnPaint();
		return 0;

	default:
		return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
	}
	return TRUE;
}




HRESULT MainWindow::CreateGraphicsResource()
{
	HRESULT hr = S_OK;
	if (!pRenderTarget )
	{
		RECT rc;
		GetClientRect(m_hwnd, &rc);

		D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

		hr = pFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(m_hwnd, size), &pRenderTarget);

		if (SUCCEEDED(hr))
		{
			const D2D1_COLOR_F color = D2D1::ColorF(0.0f, 1.0f, 0.0f, 1.0f);
			hr = pRenderTarget->CreateSolidColorBrush(color, &pBrush);

			if (FAILED(hr))
			{
				DiscardGraphicsResource();
			}
		}

	}
	return hr;
}

void MainWindow::DiscardGraphicsResource()
{
	SafeRelease(&pRenderTarget);
	SafeRelease(&pBrush);
}

void MainWindow::OnLButtonDown(int pixelX, int pixelY, DWORD flags)
{
	// begin Capturing the Mouse
	SetCapture(m_hwnd);		

	// Store the position of the Mouse
	ellipse.point = pMouse = DPIConverter::PixelsToDIPs(pixelX, pixelY);
	ellipse.radiusX = ellipse.radiusY = 1.0f;

	// force the Window to be repainted.
	InvalidateRect(m_hwnd, NULL, FALSE);

}

void MainWindow::OnLButtonUp()
{
	ReleaseCapture();
}

void MainWindow::OnMouseMove(int pixelX, int pixelY, DWORD flags)
{
	if (flags & MK_LBUTTON)
	{
		const D2D1_POINT_2F dips = DPIConverter::PixelsToDIPs(pixelX, pixelY);

		const float width = (dips.x - pMouse.x) / 2;
		const float height = (dips.y - pMouse.y) / 2;
		const float x1 = pMouse.x + width;
		const float y1 = pMouse.y + height;

		ellipse = D2D1::Ellipse(D2D1::Point2F(x1, y1), width, height);

		InvalidateRect(m_hwnd, NULL, FALSE);
	}
}

void MainWindow::OnPaint()
{
	HRESULT hr = CreateGraphicsResource();

	if (SUCCEEDED(hr))
	{
		PAINTSTRUCT ps;

		BeginPaint(m_hwnd, &ps);


		pRenderTarget->BeginDraw();
		pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));		// Draw Command 1

		pRenderTarget->FillEllipse(ellipse, pBrush);

		hr = pRenderTarget->EndDraw();		// check if the Draw was successful

		if (FAILED(hr) || hr == D2DERR_RECREATE_TARGET)
		{
			DiscardGraphicsResource();
		}

		EndPaint(m_hwnd, &ps);
	}
}

void MainWindow::Resize()
{

	if (pRenderTarget != NULL)
	{
		RECT rc;
		GetClientRect(m_hwnd, &rc);

		D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

		pRenderTarget->Resize(size);



		InvalidateRect(m_hwnd, NULL, FALSE);
	}
}
