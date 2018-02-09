#pragma once
#include "windows.h"


HWND CreateWnd(char* className, char* WndTitle, int w, int h,void* wndProc);

void ShowWnd(HWND hwnd);

LRESULT  CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);