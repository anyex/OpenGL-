#include "winmain.h"

HINSTANCE g_hInst;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	g_hInst = hInstance;
	HWND hwnd = CreateWnd("OpenGL", "OpenGL´°¿Ú", 400, 400, WindowProc);
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