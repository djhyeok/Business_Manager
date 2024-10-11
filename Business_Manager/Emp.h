#pragma once
#ifndef EMP_H
#define EMP_H

#include <windows.h>

//개인신상정보
typedef struct personalInfo {
	TCHAR pName[2][21];		//이름,영문이름
	TCHAR pIdNum[15];		//주민등록번호
	TCHAR pAddress[51];		//주소
	TCHAR pEmail[41];		//email
	TCHAR pPhone[2][14];	//연락처1,2
	TCHAR pPhysical[5][5];	//신장, 체중, 혈액형, 좌시력, 우시력
	BOOL pFamily;			//기혼여부(FALSE:미혼, TRUE:기혼)
	TCHAR pReligion[3];		//종교
} PERSONALINFO;

//사원기초정보
typedef struct empInfo {
	TCHAR empNo[12];		//사원번호 ex) 2024년 입사 경리부 여성 0001  -> 2024GR20001
	TCHAR empPosCode[3];	//사원직책
	TCHAR empStartYear[5];	//입사년도
	TCHAR empBuseo[3];		//근무부서
	BOOL empRetire;			//근무여부(TRUE:근무, FALSE:퇴직)
	PERSONALINFO pInfo;		//사원개인정보
} EMP;

#endif