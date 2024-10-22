#pragma once
#ifndef COMMON_H
#define COMMON_H
#include <windows.h>

//��� ��������
typedef struct base {
	TCHAR code[3];	//�����ڵ�
	TCHAR name[21];	//�̸�
} BASE;

//���νŻ�����
typedef struct personalInfo {
	TCHAR pName[3][21];		//�̸�(�ѱ�,����,����)
	TCHAR pIdNum[15];		//�ֹε�Ϲ�ȣ
	TCHAR pAddress[51];		//�ּ�
	TCHAR pEmail[41];		//email
	TCHAR pPhone[2][14];	//����ó1,2
	TCHAR pPhysical[5][5];	//����, ü��, ������, �½÷�, ��÷�
	BOOL pFamily;			//��ȥ����(FALSE:��ȥ, TRUE:��ȥ)
	TCHAR pReligion[3];		//����
} PERSONALINFO;

//�����������
typedef struct empInfo {
	TCHAR empNo[12];		//�����ȣ ex) 2024�� �Ի� �渮�� ���� 0001  -> 2024GR20001
	TCHAR empStartYear[5];	//�Ի�⵵
	TCHAR empBuseo[3];		//�ٹ��μ�
	TCHAR empPosCode[3];	//�����å
	BOOL empRetire;			//�ٹ�����(TRUE:�ٹ�, FALSE:����)
	PERSONALINFO pInfo;		//�����������
} EMP;

#endif