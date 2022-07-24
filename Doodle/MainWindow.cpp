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
LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory)))		// initialize the Factory
			return -1;	// The Creation of the Window failed.
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
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
	if (pRenderTarget == NULL)
	{
		RECT rc;
		GetClientRect(m_hwnd, &rc);

		D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

		hr = pFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(m_hwnd, size), &pRenderTarget);

		if (SUCCEEDED(hr))
		{
			const D2D1_COLOR_F color = D2D1::ColorF(1.0f, 1.0f, 0.0f, 0.2f);
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

void MainWindow::OnPaint()
{
	HRESULT hr = CreateGraphicsResource();

	if (SUCCEEDED(hr))
	{
		PAINTSTRUCT ps;

		BeginPaint(m_hwnd, &ps);

		pRenderTarget->BeginDraw();
		pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));		// Draw Command 1
		
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
