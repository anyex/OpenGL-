#include "windows.h"
#include "gl/gl.h"
#include "gl/glu.h"
#include "gl/glaux.h"

HDC g_HDC;//ȫ���豸����

//OpenGL��ܲ��Դ���
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


//Ϊ�豸�������ظ�ʽ�ĺ���
void SetupPixelFormat(HDC hDC)
{
	int nPixelFormat;//���صĸ�ʽ����

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

	//ѡ����ƥ������ظ�ʽ����������ֵ
	nPixelFormat = ChoosePixelFormat(hDC, &pfd);

	//�����豸���������ظ�ʽ
	SetPixelFormat(hDC, nPixelFormat, &pfd);
}

//���ڴ�����
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

		//�������ƻ���������Ϊ��ǰ��ͼ����
		hRC = wglCreateContext(hDC);
		wglMakeCurrent(hDC, hRC);

		break;

	case WM_CLOSE://�رմ���
		wglMakeCurrent(hDC, NULL);
		wglDeleteContext(hRC);
		PostQuitMessage(0);

		break;
	case WM_SIZE:
		height = HIWORD(lParam);
		width = LOWORD(lParam);
		if (height == 0)
			height = 1;
		//���������ߴ�
		glViewport(0, 0, width, height);//�趨ͶӰ����
		glMatrixMode(GL_PROJECTION);//��λͶӰ����

		//���㴰�ڳߴ����
		glMatrixMode(GL_MODELVIEW);//�趨ģ����ͼ����
		glLoadIdentity();//��λģ����ͼ����

		break;

	default:
		break;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}


int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{

	WNDCLASSEX windowClass = {0};//������
	HWND hwnd;//���ھ��
	MSG msg;//������Ϣ
	bool done;//Ӧ�ó���رյı��

	//���ô������ݽṹ
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc = WndProc;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = hInstance;
	windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);//Ĭ��ͼ��
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);//Ĭ�����ָ��
	windowClass.lpszClassName = L"OpenGL";
	windowClass.hIconSm = LoadIcon(NULL, IDI_WINLOGO);//Сͼ��

	//ע�ᴰ��
	if (!RegisterClassEx(&windowClass))
	{
		return 0;
	}

	//��������
	hwnd = CreateWindowEx(NULL, L"OpenGL", L"OpenGL����", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 600, 800,
		NULL, NULL, hInstance, NULL);

	//��鴰���Ƿ񴴽�ʧ��
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