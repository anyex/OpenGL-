#pragma once
#include "windows.h"


HWND CreateWnd(char* className, char* WndTitle, int w, int h,void* wndProc);//创建窗口

void ShowWnd(HWND hwnd);//显示窗口

LRESULT  CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);//窗口处理函数

void SetupPixelFormat(HDC hdc);//设置像素
