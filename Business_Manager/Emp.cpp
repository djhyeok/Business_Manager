#include "Emp.h"
#include "Common.h"

extern HINSTANCE g_hInst;
extern int totB;			//�μ�����
extern int totP;			//��������
extern int totR;			//��������
extern int totWEmp;			//�����
extern int totREmp;			//���������
extern BASE* buseo;			//�μ�
extern BASE* position;		//����
extern BASE* religion;		//����
extern EMP* workEmp;		//���
extern EMP* retireEmp;		//�������

HWND hEMPList, hEmpNo, hEmpBuseo, hEmpPoscode, hEmpIndate, hEmpName, hEmpMale, hEmpFemale, hEmpBirth, hEmpAddress,
hEmpEmail, hEmpPhone, hEmpHeight, hEmpWeight, hEmpLefteye, hEmpRighteye, hEmpSingle, hEmpMarriage, hEmpRelligion;	//��Ʈ�� �ڵ�
enum {
	ID_EMPLIST = 1, ID_EMPNO, ID_BUSEO, ID_POSCODE, ID_INDATE, ID_NAME, ID_MALE, ID_FEMALE, ID_BIRTH, ID_ADDRESS, ID_EMAIL,
	ID_PHONE, ID_HEIGHT, ID_WEIGHT, ID_LEFTEYE, ID_RIGHTEYE, ID_SINGLE, ID_MARRIAGE, ID_RELLIGION, ID_RETIRE, IDC_INSERT, IDC_MODIFY, IDC_DELETE
};

//������� ���ν���
LRESULT CALLBACK InitEMPMDIProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	LVCOLUMN COL;
	HDC hdc;
	PAINTSTRUCT ps;
	INITCOMMONCONTROLSEX icex;
	int i,ind;

	switch (iMessage) {
	case WM_CREATE:
		InitCommonControlsEx(&icex);

		//����Ʈ�� ����
		hEMPList = CreateWindow(WC_LISTVIEW, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_SHOWSELALWAYS, 350, 10, 1130, 700, hWnd, (HMENU)ID_EMPLIST, g_hInst, NULL);
		//����Ʈ�� ����߰�
		//(�����ȣ,�μ�,��å,�Ի���,�̸�,����,�������,�ּ�,���ڿ���,����ó,����,ü��,�÷�(��),�÷�(��),��ȥ����,����)
		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 150;
		COL.pszText = (LPWSTR)TEXT("�����ȣ");
		COL.iSubItem = 0;
		ListView_InsertColumn(hEMPList, 0, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 50;
		COL.pszText = (LPWSTR)TEXT("�μ�");
		COL.iSubItem = 1;
		ListView_InsertColumn(hEMPList, 1, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 60;
		COL.pszText = (LPWSTR)TEXT("��å");
		COL.iSubItem = 2;
		ListView_InsertColumn(hEMPList, 2, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 80;
		COL.pszText = (LPWSTR)TEXT("�Ի���");
		COL.iSubItem = 3;
		ListView_InsertColumn(hEMPList, 3, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 50;
		COL.pszText = (LPWSTR)TEXT("�̸�");
		COL.iSubItem = 4;
		ListView_InsertColumn(hEMPList, 4, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 50;
		COL.pszText = (LPWSTR)TEXT("����");
		COL.iSubItem = 5;
		ListView_InsertColumn(hEMPList, 5, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 80;
		COL.pszText = (LPWSTR)TEXT("�������");
		COL.iSubItem = 6;
		ListView_InsertColumn(hEMPList, 6, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 100;
		COL.pszText = (LPWSTR)TEXT("�ּ�");
		COL.iSubItem = 7;
		ListView_InsertColumn(hEMPList, 7, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 100;
		COL.pszText = (LPWSTR)TEXT("���ڿ���");
		COL.iSubItem = 8;
		ListView_InsertColumn(hEMPList, 8, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 100;
		COL.pszText = (LPWSTR)TEXT("����ó");
		COL.iSubItem = 9;
		ListView_InsertColumn(hEMPList, 9, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 40;
		COL.pszText = (LPWSTR)TEXT("����");
		COL.iSubItem = 10;
		ListView_InsertColumn(hEMPList, 10, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 40;
		COL.pszText = (LPWSTR)TEXT("ü��");
		COL.iSubItem = 11;
		ListView_InsertColumn(hEMPList, 11, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 60;
		COL.pszText = (LPWSTR)TEXT("�÷�(��)");
		COL.iSubItem = 12;
		ListView_InsertColumn(hEMPList, 12, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 60;
		COL.pszText = (LPWSTR)TEXT("�÷�(��)");
		COL.iSubItem = 13;
		ListView_InsertColumn(hEMPList, 13, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 60;
		COL.pszText = (LPWSTR)TEXT("��ȥ����");
		COL.iSubItem = 11;
		ListView_InsertColumn(hEMPList, 11, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 50;
		COL.pszText = (LPWSTR)TEXT("����");
		COL.iSubItem = 12;
		ListView_InsertColumn(hEMPList, 12, &COL);

		//����Ʈ�信 ��� ä���

		//�����ȣ ����Ʈ��Ʈ�� ����
		hEmpNo = CreateWindow(TEXT("static"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER , 150, 33, 150, 25, hWnd, (HMENU)ID_EMPNO, g_hInst, NULL);
		//�μ� �޺��ڽ� ����
		hEmpBuseo = CreateWindow(TEXT("combobox"), NULL, WS_CHILD | WS_VISIBLE | CBS_DROPDOWN, 150, 70, 153, 200, hWnd, (HMENU)ID_BUSEO, g_hInst, NULL);
		for (i = 0; i < totB; i++) {
			SendMessage(hEmpBuseo, CB_ADDSTRING, 0, (LPARAM)buseo[i].name);
		}
		//��å �޺��ڽ� ����
		hEmpPoscode = CreateWindow(TEXT("combobox"), NULL, WS_CHILD | WS_VISIBLE | CBS_DROPDOWN, 150, 110, 153, 200, hWnd, (HMENU)ID_POSCODE, g_hInst, NULL);
		for (i = 0; i < totP; i++) {
			SendMessage(hEmpPoscode, CB_ADDSTRING, 0, (LPARAM)position[i].name);
		}
		//�Ի��� ��¥��Ʈ�� ����
		hEmpIndate = CreateWindow(DATETIMEPICK_CLASS, NULL, WS_BORDER | WS_CHILD | WS_VISIBLE | DTS_SHORTDATEFORMAT, 150, 150, 153, 25, hWnd, (HMENU)ID_INDATE, g_hInst, NULL);
		//�̸� ����Ʈ��Ʈ�� ����
		hEmpName = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 150, 190, 150, 25, hWnd, (HMENU)ID_NAME, g_hInst, NULL);
		//���� ������ư ����
		hEmpMale = CreateWindow(TEXT("button"), TEXT("Male"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP, 150, 230, 70, 25, hWnd, (HMENU)ID_MALE, g_hInst, NULL);
		hEmpFemale = CreateWindow(TEXT("button"), TEXT("Female"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 225, 230, 70, 25, hWnd, (HMENU)ID_FEMALE, g_hInst, NULL);
		CheckRadioButton(hWnd, ID_MALE, ID_FEMALE, ID_MALE);
		//������� ��¥��Ʈ�� ����
		hEmpBirth = CreateWindow(DATETIMEPICK_CLASS, NULL, WS_BORDER | WS_CHILD | WS_VISIBLE | DTS_SHORTDATEFORMAT, 150, 270, 153, 25, hWnd, (HMENU)ID_BIRTH, g_hInst, NULL);
		//�ּ� ����Ʈ��Ʈ�� ����
		hEmpAddress = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 150, 310, 150, 25, hWnd, (HMENU)ID_ADDRESS, g_hInst, NULL);
		//�̸��� ����Ʈ��Ʈ�� ����
		hEmpEmail = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 150, 350, 150, 25, hWnd, (HMENU)ID_EMAIL, g_hInst, NULL);
		//����ó ����Ʈ��Ʈ�� ����
		hEmpPhone = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 150, 390, 150, 25, hWnd, (HMENU)ID_PHONE, g_hInst, NULL);
		//���� ����Ʈ��Ʈ�� ����
		hEmpHeight = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 150, 430, 150, 25, hWnd, (HMENU)ID_HEIGHT, g_hInst, NULL);
		//ü�� ����Ʈ��Ʈ�� ����
		hEmpWeight = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 150, 470, 150, 25, hWnd, (HMENU)ID_WEIGHT, g_hInst, NULL);
		//��ȥ���� ������ư ����
		hEmpSingle = CreateWindow(TEXT("button"), TEXT("Single"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP, 150, 510, 70, 30, hWnd, (HMENU)ID_SINGLE, g_hInst, NULL);
		hEmpMarriage = CreateWindow(TEXT("button"), TEXT("Marriage"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 220, 510, 80, 30, hWnd, (HMENU)ID_MARRIAGE, g_hInst, NULL);
		CheckRadioButton(hWnd, ID_SINGLE, ID_MARRIAGE, ID_SINGLE);
		//���� �޺��ڽ� ����
		hEmpRelligion = CreateWindow(TEXT("combobox"), NULL, WS_CHILD | WS_VISIBLE | CBS_DROPDOWN, 150, 550, 153, 200, hWnd, (HMENU)ID_RELLIGION, g_hInst, NULL);
		for (i = 0; i < totR; i++) {
			SendMessage(hEmpRelligion, CB_ADDSTRING, 0, (LPARAM)religion[i].name);
		}
		//�÷� ����Ʈ��Ʈ�� ����
		hEmpLefteye = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 150, 590, 150, 25, hWnd, (HMENU)ID_LEFTEYE, g_hInst, NULL);
		hEmpRighteye = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 150, 630, 150, 25, hWnd, (HMENU)ID_RIGHTEYE, g_hInst, NULL);
		//����ó�� ��ư����
		CreateWindow(TEXT("button"), TEXT("����ó��"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 100, 670, 130, 30, hWnd, (HMENU)ID_RETIRE, g_hInst, NULL);

		//���Թ�ư����
		CreateWindow(TEXT("button"), TEXT("����"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 50, 710, 70, 25, hWnd, (HMENU)IDC_INSERT, g_hInst, NULL);
		//������ư����
		CreateWindow(TEXT("button"), TEXT("����"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 130, 710, 70, 25, hWnd, (HMENU)IDC_MODIFY, g_hInst, NULL);
		//������ư����
		CreateWindow(TEXT("button"), TEXT("����"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 210, 710, 70, 25, hWnd, (HMENU)IDC_DELETE, g_hInst, NULL);

		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 50, 35, TEXT("�����ȣ"), lstrlen(TEXT("�����ȣ")));
		TextOut(hdc, 50, 75, TEXT("�μ�"), lstrlen(TEXT("�μ�")));
		TextOut(hdc, 50, 115, TEXT("��å"), lstrlen(TEXT("��å")));
		TextOut(hdc, 50, 155, TEXT("�Ի���"), lstrlen(TEXT("�Ի���")));
		TextOut(hdc, 50, 195, TEXT("�̸�"), lstrlen(TEXT("�̸�")));
		TextOut(hdc, 50, 235, TEXT("����"), lstrlen(TEXT("����")));
		TextOut(hdc, 50, 275, TEXT("�������"), lstrlen(TEXT("�������")));
		TextOut(hdc, 50, 315, TEXT("�ּ�"), lstrlen(TEXT("�ּ�")));
		TextOut(hdc, 50, 355, TEXT("���ڿ���"), lstrlen(TEXT("���ڿ���")));
		TextOut(hdc, 50, 395, TEXT("����ó"), lstrlen(TEXT("����ó")));
		TextOut(hdc, 50, 435, TEXT("����"), lstrlen(TEXT("����")));
		TextOut(hdc, 50, 475, TEXT("ü��"), lstrlen(TEXT("ü��")));
		TextOut(hdc, 50, 515, TEXT("��ȥ����"), lstrlen(TEXT("��ȥ����")));
		TextOut(hdc, 50, 555, TEXT("����"), lstrlen(TEXT("����")));
		TextOut(hdc, 50, 595, TEXT("�÷�(��)"), lstrlen(TEXT("�÷�(��)")));
		TextOut(hdc, 50, 635, TEXT("�÷�(��)"), lstrlen(TEXT("�÷�(��)")));
		EndPaint(hWnd, &ps);
		return 0;
	}
	return (DefMDIChildProc(hWnd, iMessage, wParam, lParam));
}
