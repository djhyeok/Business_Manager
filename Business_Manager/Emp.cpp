#include "Emp.h"
#include "Common.h"

/*
����Ʈ�� �Է��� ���� ����Ʈ�信 �Ѹ��� ����Ʈ ��Ʈ�� �ʱ�ȭ
����,����,���� �� ����Ʈ�� �� ���� �ٽ� �����ͼ���ŭ ����Ʈ�信 �Ѹ���
*/

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

HWND hEMPList, hEmpNo, hEmpBuseo, hEmpPoscode, hEmpIndate, hEmpName1, hEmpName2, hEmpName3, hEmpMale, hEmpFemale, hEmpBirth, hEmpAddress,
hEmpEmail, hEmpPhone1, hEmpPhone2, hEmpHeight, hEmpWeight, hEmpLefteye, hEmpRighteye, hEmpSingle, hEmpMarriage, hEmpRelligion;	//��Ʈ�� �ڵ�
enum {
	ID_EMPLIST = 1, ID_EMPNO, ID_BUSEO, ID_POSCODE, ID_INDATE, ID_NAME1, ID_NAME2, ID_NAME3, ID_MALE, ID_FEMALE, ID_BIRTH, ID_ADDRESS, ID_EMAIL,
	ID_PHONE1, ID_PHONE2, ID_HEIGHT, ID_WEIGHT, ID_LEFTEYE, ID_RIGHTEYE, ID_SINGLE, ID_MARRIAGE, ID_RELLIGION, ID_RETIRE, IDC_INSERT, IDC_MODIFY, IDC_DELETE
};

//������� ���ν���
LRESULT CALLBACK InitEMPMDIProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	LVCOLUMN COL;
	HFONT hFont, OldFont;
	HDC hdc;
	PAINTSTRUCT ps;
	INITCOMMONCONTROLSEX icex;
	int i, ind;
	EMP tempEmp;
	SYSTEMTIME st;

	switch (iMessage) {
	case WM_CREATE:
		InitCommonControlsEx(&icex);

		//����Ʈ�� ����
		hEMPList = CreateWindow(WC_LISTVIEW, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_SHOWSELALWAYS, 350, 10, 1150, 700, hWnd, (HMENU)ID_EMPLIST, g_hInst, NULL);
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
		COL.cx = 70;
		COL.pszText = (LPWSTR)TEXT("�����̸�");
		COL.iSubItem = 5;
		ListView_InsertColumn(hEMPList, 5, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 70;
		COL.pszText = (LPWSTR)TEXT("�����̸�");
		COL.iSubItem = 6;
		ListView_InsertColumn(hEMPList, 6, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 50;
		COL.pszText = (LPWSTR)TEXT("����");
		COL.iSubItem = 7;
		ListView_InsertColumn(hEMPList, 7, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 80;
		COL.pszText = (LPWSTR)TEXT("�������");
		COL.iSubItem = 8;
		ListView_InsertColumn(hEMPList, 8, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 100;
		COL.pszText = (LPWSTR)TEXT("�ּ�");
		COL.iSubItem = 9;
		ListView_InsertColumn(hEMPList, 9, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 100;
		COL.pszText = (LPWSTR)TEXT("���ڿ���");
		COL.iSubItem = 10;
		ListView_InsertColumn(hEMPList, 10, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 100;
		COL.pszText = (LPWSTR)TEXT("����ó1");
		COL.iSubItem = 11;
		ListView_InsertColumn(hEMPList, 11, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 100;
		COL.pszText = (LPWSTR)TEXT("����ó2");
		COL.iSubItem = 12;
		ListView_InsertColumn(hEMPList, 12, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 40;
		COL.pszText = (LPWSTR)TEXT("����");
		COL.iSubItem = 13;
		ListView_InsertColumn(hEMPList, 13, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 40;
		COL.pszText = (LPWSTR)TEXT("ü��");
		COL.iSubItem = 14;
		ListView_InsertColumn(hEMPList, 14, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 60;
		COL.pszText = (LPWSTR)TEXT("��ȥ����");
		COL.iSubItem = 15;
		ListView_InsertColumn(hEMPList, 15, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 50;
		COL.pszText = (LPWSTR)TEXT("����");
		COL.iSubItem = 16;
		ListView_InsertColumn(hEMPList, 16, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 60;
		COL.pszText = (LPWSTR)TEXT("�÷�(��)");
		COL.iSubItem = 17;
		ListView_InsertColumn(hEMPList, 17, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 60;
		COL.pszText = (LPWSTR)TEXT("�÷�(��)");
		COL.iSubItem = 18;
		ListView_InsertColumn(hEMPList, 18, &COL);

		//����Ʈ�信 ��� ä���

		//�����ȣ ����Ʈ��Ʈ�� ����
		hEmpNo = CreateWindow(TEXT("static"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 150, 10, 150, 25, hWnd, (HMENU)ID_EMPNO, g_hInst, NULL);
		//�μ� �޺��ڽ� ����
		hEmpBuseo = CreateWindow(TEXT("combobox"), NULL, WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST, 150, 45, 153, 200, hWnd, (HMENU)ID_BUSEO, g_hInst, NULL);
		for (i = 0; i < totB; i++) {
			SendMessage(hEmpBuseo, CB_ADDSTRING, 0, (LPARAM)buseo[i].name);
		}
		//��å �޺��ڽ� ����
		hEmpPoscode = CreateWindow(TEXT("combobox"), NULL, WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST, 150, 80, 153, 200, hWnd, (HMENU)ID_POSCODE, g_hInst, NULL);
		for (i = 0; i < totP; i++) {
			SendMessage(hEmpPoscode, CB_ADDSTRING, 0, (LPARAM)position[i].name);
		}
		//�Ի��� ��¥��Ʈ�� ����
		hEmpIndate = CreateWindow(DATETIMEPICK_CLASS, NULL, WS_BORDER | WS_CHILD | WS_VISIBLE | DTS_SHORTDATEFORMAT, 150, 115, 153, 25, hWnd, (HMENU)ID_INDATE, g_hInst, NULL);
		//�̸� ����Ʈ��Ʈ�� ����
		hEmpName1 = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 150, 150, 150, 25, hWnd, (HMENU)ID_NAME1, g_hInst, NULL);
		hEmpName2 = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 150, 185, 150, 25, hWnd, (HMENU)ID_NAME2, g_hInst, NULL);
		hEmpName3 = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 150, 220, 150, 25, hWnd, (HMENU)ID_NAME3, g_hInst, NULL);
		//���� ������ư ����
		hEmpMale = CreateWindow(TEXT("button"), TEXT("Male"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP, 150, 255, 70, 25, hWnd, (HMENU)ID_MALE, g_hInst, NULL);
		hEmpFemale = CreateWindow(TEXT("button"), TEXT("Female"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 225, 255, 70, 25, hWnd, (HMENU)ID_FEMALE, g_hInst, NULL);
		CheckRadioButton(hWnd, ID_MALE, ID_FEMALE, ID_MALE);
		//������� ��¥��Ʈ�� ����
		hEmpBirth = CreateWindow(DATETIMEPICK_CLASS, NULL, WS_BORDER | WS_CHILD | WS_VISIBLE | DTS_SHORTDATEFORMAT, 150, 290, 153, 25, hWnd, (HMENU)ID_BIRTH, g_hInst, NULL);
		//�ּ� ����Ʈ��Ʈ�� ����
		hEmpAddress = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 150, 325, 150, 25, hWnd, (HMENU)ID_ADDRESS, g_hInst, NULL);
		//�̸��� ����Ʈ��Ʈ�� ����
		hEmpEmail = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 150, 360, 150, 25, hWnd, (HMENU)ID_EMAIL, g_hInst, NULL);
		//����ó ����Ʈ��Ʈ�� ����
		hEmpPhone1 = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 150, 395, 150, 25, hWnd, (HMENU)ID_PHONE1, g_hInst, NULL);
		hEmpPhone2 = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 150, 430, 150, 25, hWnd, (HMENU)ID_PHONE2, g_hInst, NULL);
		//���� ����Ʈ��Ʈ�� ����
		hEmpHeight = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 150, 465, 150, 25, hWnd, (HMENU)ID_HEIGHT, g_hInst, NULL);
		//ü�� ����Ʈ��Ʈ�� ����
		hEmpWeight = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 150, 500, 150, 25, hWnd, (HMENU)ID_WEIGHT, g_hInst, NULL);
		//��ȥ���� ������ư ����
		hEmpSingle = CreateWindow(TEXT("button"), TEXT("Single"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP, 150, 535, 70, 30, hWnd, (HMENU)ID_SINGLE, g_hInst, NULL);
		hEmpMarriage = CreateWindow(TEXT("button"), TEXT("Marriage"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 220, 535, 80, 30, hWnd, (HMENU)ID_MARRIAGE, g_hInst, NULL);
		CheckRadioButton(hWnd, ID_SINGLE, ID_MARRIAGE, ID_SINGLE);
		//���� �޺��ڽ� ����
		hEmpRelligion = CreateWindow(TEXT("combobox"), NULL, WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST, 150, 580, 153, 200, hWnd, (HMENU)ID_RELLIGION, g_hInst, NULL);
		for (i = 0; i < totR; i++) {
			SendMessage(hEmpRelligion, CB_ADDSTRING, 0, (LPARAM)religion[i].name);
		}
		//�÷� ����Ʈ��Ʈ�� ����
		hEmpLefteye = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 150, 615, 150, 25, hWnd, (HMENU)ID_LEFTEYE, g_hInst, NULL);
		hEmpRighteye = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 150, 650, 150, 25, hWnd, (HMENU)ID_RIGHTEYE, g_hInst, NULL);
		//����ó�� ��ư����
		CreateWindow(TEXT("button"), TEXT("����ó��"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 100, 685, 130, 30, hWnd, (HMENU)ID_RETIRE, g_hInst, NULL);

		//���Թ�ư����
		CreateWindow(TEXT("button"), TEXT("����"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 50, 720, 70, 25, hWnd, (HMENU)IDC_INSERT, g_hInst, NULL);
		//������ư����
		CreateWindow(TEXT("button"), TEXT("����"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 130, 720, 70, 25, hWnd, (HMENU)IDC_MODIFY, g_hInst, NULL);
		//������ư����
		CreateWindow(TEXT("button"), TEXT("����"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 210, 720, 70, 25, hWnd, (HMENU)IDC_DELETE, g_hInst, NULL);

		return 0;
	case WM_COMMAND:
	

		switch (LOWORD(wParam)) {
		case IDC_INSERT:	//���� ��ư
			GetWindowText(hEmpBuseo, tempEmp.empBuseo, lstrlen(tempEmp.empBuseo));				//�μ�
			GetWindowText(hEmpPoscode, tempEmp.empPosCode, lstrlen(tempEmp.empPosCode));		//��å
			if (SendMessage(hEmpIndate, DTM_GETSYSTEMTIME, 0, (LPARAM)&st) == GDT_VALID) {
				tempEmp.empStartYear = st;														//�Ի���
			}
			else {
				MessageBox(hWnd, TEXT("�Ի����� ���õ��� �ʾҽ��ϴ�"), TEXT("�Ի��� ���� ����"), MB_OK);
				break;
			}
			GetWindowText(hEmpName1, tempEmp.pInfo.pName[0], lstrlen(tempEmp.pInfo.pName[0]));	//�̸�
			GetWindowText(hEmpName2, tempEmp.pInfo.pName[1], lstrlen(tempEmp.pInfo.pName[1]));	//�����̸�
			GetWindowText(hEmpName3, tempEmp.pInfo.pName[2], lstrlen(tempEmp.pInfo.pName[2]));	//�����̸�
			if (SendMessage(hWnd, BST_CHECKED, ID_MALE, lParam)) {
				tempEmp.pInfo.pSex = TRUE;														//����
			}
			else {
				tempEmp.pInfo.pSex = FALSE;														//����
			}
			if (SendMessage(hEmpBirth, DTM_GETSYSTEMTIME, 0, (LPARAM)&st) == GDT_VALID) {
				tempEmp.pInfo.pBirth = st;														//����
			}
			else {
				MessageBox(hWnd, TEXT("������ ���õ��� �ʾҽ��ϴ�"), TEXT("���� ���� ����"), MB_OK);
				break;
			}
			GetWindowText(hEmpAddress, tempEmp.pInfo.pAddress, lstrlen(tempEmp.pInfo.pAddress));	//�ּ�
			GetWindowText(hEmpEmail, tempEmp.pInfo.pEmail, lstrlen(tempEmp.pInfo.pEmail));		//���ڿ���
			GetWindowText(hEmpPhone1, tempEmp.pInfo.pPhone[0], lstrlen(tempEmp.pInfo.pPhone[0]));//����ó1
			GetWindowText(hEmpPhone2, tempEmp.pInfo.pPhone[1], lstrlen(tempEmp.pInfo.pPhone[1]));//����ó2
			GetWindowText(hEmpHeight, tempEmp.pInfo.pPhysical[0], lstrlen(tempEmp.pInfo.pPhysical[0]));//����
			GetWindowText(hEmpWeight, tempEmp.pInfo.pPhysical[1], lstrlen(tempEmp.pInfo.pPhysical[1]));//ü��
			if (SendMessage(hWnd, BST_CHECKED, ID_MARRIAGE, lParam)) {
				tempEmp.pInfo.pSex = TRUE;														//��ȥ
			}
			else {
				tempEmp.pInfo.pSex = FALSE;														//��ȥ
			}
			GetWindowText(hEmpRelligion, tempEmp.pInfo.pReligion, lstrlen(tempEmp.pInfo.pReligion));//����
			GetWindowText(hEmpLefteye, tempEmp.pInfo.pPhysical[2], lstrlen(tempEmp.pInfo.pPhysical[2]));//�÷�(��)
			GetWindowText(hEmpRighteye, tempEmp.pInfo.pPhysical[3], lstrlen(tempEmp.pInfo.pPhysical[3]));//�÷�(��)

			if (lstrlen(tempEmp.empBuseo) && lstrlen(tempEmp.empPosCode) && lstrlen(tempEmp.pInfo.pName[0])
				&& lstrlen(tempEmp.pInfo.pName[1]) && lstrlen(tempEmp.pInfo.pName[2]) && lstrlen(tempEmp.pInfo.pAddress)
				&& lstrlen(tempEmp.pInfo.pEmail) && lstrlen(tempEmp.pInfo.pPhone[0]) && lstrlen(tempEmp.pInfo.pPhone[1])
				&& lstrlen(tempEmp.pInfo.pPhysical[0]) && lstrlen(tempEmp.pInfo.pPhysical[1]) && lstrlen(tempEmp.pInfo.pReligion)
				&& lstrlen(tempEmp.pInfo.pPhysical[2]) && lstrlen(tempEmp.pInfo.pPhysical[3])) {
				MessageBox(hWnd, TEXT("���̰� 0�� ���� �߰��� �� �����ϴ�."), TEXT("�Է°� ����"), MB_OK);
			}
			break;
		case IDC_MODIFY:	//���� ��ư

			break;
		case IDC_DELETE:	//���� ��ư

			break;
		case ID_RETIRE:		//����ó�� ��ư

			break;
		}
		return 0;
	case WM_NOTIFY:
		LPNMHDR hdr;
		LPNMLISTVIEW nlv;
		hdr = (LPNMHDR)lParam;
		nlv = (LPNMLISTVIEW)lParam;
		TCHAR str[255],tstr[255];

		//�μ�����Ʈ�信�� ���õ� �׸� ��Ʈ�ѵ�� �Ѹ���
		switch (hdr->code) {
		case LVN_ITEMCHANGED:
			if (nlv->uChanged == LVIF_STATE && nlv->uNewState == (LVIS_SELECTED | LVIS_FOCUSED)) {

				SetWindowText(hEmpNo, workEmp[nlv->iItem].empNo);
				SetWindowText(hEmpBuseo, workEmp[nlv->iItem].empBuseo);
				SetWindowText(hEmpPoscode, workEmp[nlv->iItem].empPosCode);
				st = workEmp[nlv->iItem].empStartYear;
				SendMessage(hEmpIndate, DTM_SETSYSTEMTIME, GDT_VALID, (LPARAM)&st);
				SetWindowText(hEmpName1, workEmp[nlv->iItem].pInfo.pName[0]);
				SetWindowText(hEmpName2, workEmp[nlv->iItem].pInfo.pName[1]);
				SetWindowText(hEmpName3, workEmp[nlv->iItem].pInfo.pName[2]);

				if (workEmp[nlv->iItem].pInfo.pSex == TRUE) {
					SendMessage(hWnd, BST_CHECKED, ID_MALE, lParam);
				}
				else {
					SendMessage(hWnd, BST_CHECKED, ID_FEMALE, lParam);
				}


			}
			return TRUE;
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		hFont = CreateFont(18, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("���� ���"));
		OldFont = (HFONT)SelectObject(hdc, hFont);
		SetBkMode(hdc, TRANSPARENT);
		TextOut(hdc, 65, 13, TEXT("�����ȣ"), lstrlen(TEXT("�����ȣ")));
		TextOut(hdc, 65, 48, TEXT("�μ�"), lstrlen(TEXT("�μ�")));
		TextOut(hdc, 65, 83, TEXT("��å"), lstrlen(TEXT("��å")));
		TextOut(hdc, 65, 118, TEXT("�Ի���"), lstrlen(TEXT("�Ի���")));
		TextOut(hdc, 65, 153, TEXT("�̸�"), lstrlen(TEXT("�̸�")));
		TextOut(hdc, 65, 188, TEXT("�����̸�"), lstrlen(TEXT("�����̸�")));
		TextOut(hdc, 65, 223, TEXT("�ѹ��̸�"), lstrlen(TEXT("�ѹ��̸�")));
		TextOut(hdc, 65, 258, TEXT("����"), lstrlen(TEXT("����")));
		TextOut(hdc, 65, 293, TEXT("�������"), lstrlen(TEXT("�������")));
		TextOut(hdc, 65, 328, TEXT("�ּ�"), lstrlen(TEXT("�ּ�")));
		TextOut(hdc, 65, 363, TEXT("���ڿ���"), lstrlen(TEXT("���ڿ���")));
		TextOut(hdc, 65, 398, TEXT("����ó1"), lstrlen(TEXT("����ó1")));
		TextOut(hdc, 65, 433, TEXT("����ó2"), lstrlen(TEXT("����ó2")));
		TextOut(hdc, 65, 470, TEXT("����"), lstrlen(TEXT("����")));
		TextOut(hdc, 65, 505, TEXT("ü��"), lstrlen(TEXT("ü��")));
		TextOut(hdc, 65, 545, TEXT("��ȥ����"), lstrlen(TEXT("��ȥ����")));
		TextOut(hdc, 65, 585, TEXT("����"), lstrlen(TEXT("����")));
		TextOut(hdc, 65, 620, TEXT("�÷�(��)"), lstrlen(TEXT("�÷�(��)")));
		TextOut(hdc, 65, 655, TEXT("�÷�(��)"), lstrlen(TEXT("�÷�(��)")));
		DeleteObject(hFont);
		EndPaint(hWnd, &ps);
		return 0;
	}
	return (DefMDIChildProc(hWnd, iMessage, wParam, lParam));
}
