#include "windows.h"
#include "gl/gl.h"
#include "gl/glu.h"
#include "gl/glaux.h"

HDC g_HDC;//全局设备环境

//OpenGL框架测试代码
void Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslated(-1, -1, 0);

//	gluLookAt(0.0f, 0.0f, 0.0f, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

	glColor3f(1.0, 0.0f, 0.0);
	glBegin(GL_TRIANGLES);
		glColor3f(1.0, 0.0f, 0.0);
		glVertex3f(0.0, 0.0, 0.0);

		glColor3f(0.0, 1.0f, 0.0);
		glVertex3f(1.0, 0.0, 0.0);

		glColor3f(0.0, 0.0f, 1.0);
		glVertex3f(1.0, 1.1, 0.0);
	glEnd();


}


//为设备设置像素格式的函数
void SetupPixelFormat(HDC hDC)
{
	int nPixelFormat;//像素的格式变量

	static PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW|
		PFD_SUPPORT_OPENGL|
		PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		32,
		0,0,0,0,0,0,
		0,
		0,
		0,
		0,0,0,0,
		16,
		0,
		0,
		PFD_MAIN_PLANE,
		0,
		0,0,0
	};

	//选择最匹配的像素格式，返回索引值
	nPixelFormat = ChoosePixelFormat(hDC, &pfd);

	//设置设备环境的像素格式
	SetPixelFormat(hDC, nPixelFormat, &pfd);
}

//窗口处理函数
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HGLRC hRC;
	static HDC hDC;
	int width, height;

	switch (message)
	{

	case WM_CREATE:
		hDC = GetDC(hwnd);
		g_HDC = hDC;
		SetupPixelFormat(hDC);

		//创建绘制环境并设置为当前绘图环境
		hRC = wglCreateContext(hDC);
		wglMakeCurrent(hDC, hRC);

		break;

	case WM_CLOSE://关闭窗口
		wglMakeCurrent(hDC, NULL);
		wglDeleteContext(hRC);
		PostQuitMessage(0);

		break;
	case WM_SIZE:
		height = HIWORD(lParam);
		width = LOWORD(lParam);
		if (height == 0)
			height = 1;
		//重置视区尺寸
		glViewport(0, 0, width, height);//设定投影矩阵
		glMatrixMode(GL_PROJECTION);//复位投影矩阵

		//计算窗口尺寸比例
		glMatrixMode(GL_MODELVIEW);//设定模型视图矩阵
		glLoadIdentity();//复位模型视图矩阵

		break;

	default:
		break;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}


int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{

	WNDCLASSEX windowClass = {0};//窗口类
	HWND hwnd;//窗口句柄
	MSG msg;//窗口消息
	bool done;//应用程序关闭的标记

	//设置窗口数据结构
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc = WndProc;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = hInstance;
	windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);//默认图标
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);//默认鼠标指针
	windowClass.lpszClassName = L"OpenGL";
	windowClass.hIconSm = LoadIcon(NULL, IDI_WINLOGO);//小图标

	//注册窗口
	if (!RegisterClassEx(&windowClass))
	{
		return 0;
	}

	//创建窗口
	hwnd = CreateWindowEx(NULL, L"OpenGL", L"OpenGL窗口", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 600, 800,
		NULL, NULL, hInstance, NULL);

	//检查窗口是否创建失败
	if (!hwnd)
	{
		return 0;
	}
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	done = false;

	while (!done)
	{
		PeekMessage(&msg, hwnd, NULL, NULL, PM_REMOVE);

		if (msg.message == WM_QUIT)
		{
			done = true;
		}
		else
		{
			Render();
			SwapBuffers(g_HDC);
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}


	return msg.wParam;

}