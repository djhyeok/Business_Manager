#pragma once
#ifndef COMMON_H
#define COMMON_H

#include <windows.h>
#include <commctrl.h>
#include "Emp.h"
#include "resource.h"

#define IDM_WINDOWCHILD 8000

//��� ��������
typedef struct base {
	TCHAR code[3];	//�����ڵ�
	TCHAR name[21];	//�̸�
} BASE;


LRESULT CALLBACK MDIWndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK InitBuseoMDIProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK InitReligionMDIProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK InitPositionMDIProc(HWND, UINT, WPARAM, LPARAM);




#endif