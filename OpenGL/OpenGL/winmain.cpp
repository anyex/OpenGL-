#include "winmain.h"
#include "gl/GL.h"
#include "gl/glu.h"
#include "gl/GLAUX.H"

HINSTANCE g_hInst;

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
	return DefWindowProc(hWnd, uMsg, wParam, lParam);

};