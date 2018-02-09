#include "winmain.h"
#include "3DFunction.h"


HINSTANCE g_hInst;
HDC hdc;
HGLRC hrc;

void SetupPixelFormat(HDC hdc)
{
	int pixelFormat;//存放像素格式的索引值

	PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW |
		PFD_SUPPORT_OPENGL |
		PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		32,
		0,0,0,0,0,0,
		0,
		0,
		0,
		0,0,0,0,
		32,
		0,
		0,
		PFD_MAIN_PLANE,
		0,0,0,0 };
	pixelFormat = ChoosePixelFormat(hdc, &pfd);//返回一个最接近pfd且适合hdc设备的像素格式的索引
	SetPixelFormat(hdc, pixelFormat, &pfd);//设置像素格式




}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	g_hInst = hInstance;
	HWND hwnd = CreateWnd("OpenGL", "OpenGL窗口", 400, 400, WindowProc);
	ShowWnd(hwnd);


	return 0;

}



void ShowWnd(HWND hwnd)
{
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

};
HWND CreateWnd(char* className,char* title, int w, int h, void* wndProc)
{
	WNDCLASS	wc = { 0 };
	wc.lpfnWndProc = (WNDPROC)wndProc;
	wc.lpszClassName = className;
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wc);

	HWND hWnd = CreateWindow(className, title, WS_OVERLAPPEDWINDOW, 200, 200, w, h, NULL, NULL, g_hInst, NULL);

	return hWnd;
};
LRESULT  CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	switch (uMsg)
	{
	case WM_CREATE:
	{
		hdc = GetDC(hWnd);//获取窗口的设置句柄
		SetupPixelFormat(hdc);//设置窗口像素格式

		hrc = wglCreateContext(hdc);//创建渲染环境
		wglMakeCurrent(hdc, hrc);//设定当前设备的环境以及当前的渲染环境

		SetupMatrices(640, 480);

		InitOpenGL();

		SetTimer(hWnd, 1, 1, NULL);

	}break;

	case  WM_TIMER:
	{
		Render();
		SwapBuffers(hdc);

	}break;
		 
		 


	}


	return DefWindowProc(hWnd, uMsg, wParam, lParam);

};

