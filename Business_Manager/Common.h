#pragma once
#ifndef COMMON_H
#define COMMON_H

#include <windows.h>
#include <commctrl.h>
#include "resource.h"



//기업 기초정보
typedef struct base {
	TCHAR code[3];	//구분코드
	TCHAR name[21];	//이름
} BASE;


LRESULT CALLBACK MDIWndProc(HWND, UINT, WPARAM, LPARAM);			//메인 윈도우 프로시져
LRESULT CALLBACK InitBuseoMDIProc(HWND, UINT, WPARAM, LPARAM);		//부서 MDI 윈도우 프로시져
LRESULT CALLBACK InitReligionMDIProc(HWND, UINT, WPARAM, LPARAM);	//종교 MDI 윈도우 프로시져
LRESULT CALLBACK InitPositionMDIProc(HWND, UINT, WPARAM, LPARAM);	//직위 MDI 윈도우 프로시져




#endif