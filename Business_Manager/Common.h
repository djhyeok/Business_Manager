#pragma once
#ifndef COMMON_H
#define COMMON_H

#include <windows.h>
#include <commctrl.h>
#include "resource.h"



//��� ��������
typedef struct base {
	TCHAR code[3];	//�����ڵ�
	TCHAR name[21];	//�̸�
} BASE;


LRESULT CALLBACK MDIWndProc(HWND, UINT, WPARAM, LPARAM);			//���� ������ ���ν���
LRESULT CALLBACK InitBuseoMDIProc(HWND, UINT, WPARAM, LPARAM);		//�μ� MDI ������ ���ν���
LRESULT CALLBACK InitReligionMDIProc(HWND, UINT, WPARAM, LPARAM);	//���� MDI ������ ���ν���
LRESULT CALLBACK InitPositionMDIProc(HWND, UINT, WPARAM, LPARAM);	//���� MDI ������ ���ν���




#endif