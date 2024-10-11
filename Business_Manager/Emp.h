#pragma once
#ifndef EMP_H
#define EMP_H

#include <windows.h>

//���νŻ�����
typedef struct personalInfo {
	TCHAR pName[2][21];		//�̸�,�����̸�
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
	TCHAR empPosCode[3];	//�����å
	TCHAR empStartYear[5];	//�Ի�⵵
	TCHAR empBuseo[3];		//�ٹ��μ�
	BOOL empRetire;			//�ٹ�����(TRUE:�ٹ�, FALSE:����)
	PERSONALINFO pInfo;		//�����������
} EMP;

#endif