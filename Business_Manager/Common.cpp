#include "Common.h"

#define IDM_WINDOWCHILD 8000

extern HINSTANCE g_hInst;
extern HWND g_hFrameWnd;	//���� ������ ������ �ڵ�
extern HWND g_hMDIClient;	//Ŭ���̾�Ʈ ������ �ڵ�
HWND hBuseoList;			//�μ�����Ʈ�� �ڵ�
HWND hReligionList;			//��������Ʈ�� �ڵ�
HWND hPositionList;			//��������Ʈ�� �ڵ�
extern int totB;			//�μ�����
extern int totP;			//��������
extern int totR;			//��������
extern BASE* buseo;			//�μ�
extern BASE* position;		//����
extern BASE* religion;		//����

enum { IDC_INSERT = 1, IDC_MODIFY, IDC_DEL, ID_NAME, ID_CODE, ID_BLIST, ID_RLIST, ID_PLIST };

LRESULT CALLBACK MDIWndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	CLIENTCREATESTRUCT ccs;
	MDICREATESTRUCT mcs;

	switch (iMessage) {
	case WM_CREATE:
		InitCommonControls();
		//MDI Client ������ ����
		ccs.hWindowMenu = GetSubMenu(GetMenu(hWnd), 1);
		ccs.idFirstChild = IDM_WINDOWCHILD;
		g_hMDIClient = CreateWindow(TEXT("MDIClient"), NULL, WS_CHILD | WS_VSCROLL | WS_HSCROLL | WS_CLIPCHILDREN, 0, 0, 0, 0, hWnd, (HMENU)NULL, g_hInst, (LPSTR)&ccs);
		ShowWindow(g_hMDIClient, SW_SHOW);
		//�ʱ⿡ �μ�,����,���� 1�� ������� �Ҵ�
		buseo = (BASE*)malloc(sizeof(BASE));
		position = (BASE*)malloc(sizeof(BASE));
		religion = (BASE*)malloc(sizeof(BASE));
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
			//�� MDI ������ ����
		case IDM_BUSEO:		//������������(�޴���)->�μ�
			mcs.szClass = TEXT("InitBuseoMDI");
			mcs.szTitle = TEXT("�μ�");
			mcs.hOwner = g_hInst;
			mcs.x = mcs.y = CW_USEDEFAULT;
			mcs.cx = mcs.cy = CW_USEDEFAULT;
			mcs.style = MDIS_ALLCHILDSTYLES;
			SendMessage(g_hMDIClient, WM_MDICREATE, 0, (LPARAM)(LPMDICREATESTRUCT)&mcs);
			break;
		case IDM_POSITION:	//������������(�޴���)->����
			mcs.szClass = TEXT("InitPosMDI");
			mcs.szTitle = TEXT("����");
			mcs.hOwner = g_hInst;
			mcs.x = mcs.y = CW_USEDEFAULT;
			mcs.cx = mcs.cy = CW_USEDEFAULT;
			mcs.style = MDIS_ALLCHILDSTYLES;
			SendMessage(g_hMDIClient, WM_MDICREATE, 0, (LPARAM)(LPMDICREATESTRUCT)&mcs);
			break;
		case IDM_RELIGION:	//������������(�޴���)->����
			mcs.szClass = TEXT("InitRelMDI");
			mcs.szTitle = TEXT("����");
			mcs.hOwner = g_hInst;
			mcs.x = mcs.y = CW_USEDEFAULT;
			mcs.cx = mcs.cy = CW_USEDEFAULT;
			mcs.style = MDIS_ALLCHILDSTYLES;
			SendMessage(g_hMDIClient, WM_MDICREATE, 0, (LPARAM)(LPMDICREATESTRUCT)&mcs);
			break;
		case ID_EMP:
			mcs.szClass = TEXT("InitEMPMDI");
			mcs.szTitle = TEXT("���");
			mcs.hOwner = g_hInst;
			mcs.x = mcs.y = CW_USEDEFAULT;
			mcs.cx = mcs.cy = CW_USEDEFAULT;
			mcs.style = MDIS_ALLCHILDSTYLES;
			SendMessage(g_hMDIClient, WM_MDICREATE, 0, (LPARAM)(LPMDICREATESTRUCT)&mcs);
			break;
		}
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		//�Ҵ�� �μ�,����,���� free
		free(buseo);
		free(position);
		free(religion);
		return 0;
	}
	return(DefFrameProc(hWnd, g_hMDIClient, iMessage, wParam, lParam));
}

LRESULT CALLBACK InitBuseoMDIProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	LVCOLUMN COL;
	LVITEM LI, tempLI;
	LVFINDINFO fi;
	HDC hdc;
	PAINTSTRUCT ps;
	int i, ind;
	static BOOL isDup = FALSE;
	TCHAR tCode[3], tName[21];		//�ӽ� ���ڿ�

	switch (iMessage) {
	case WM_CREATE:
		//����Ʈ�� ����
		hBuseoList = CreateWindow(WC_LISTVIEW, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_SHOWSELALWAYS, 50, 10, 200, 300, hWnd, (HMENU)ID_BLIST, g_hInst, NULL);

		//����Ʈ�� ����߰�
		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 100;
		COL.pszText = (LPWSTR)TEXT("�μ��ڵ�");
		COL.iSubItem = 0;
		ListView_InsertColumn(hBuseoList, 0, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 100;
		COL.pszText = (LPWSTR)TEXT("�μ���");
		COL.iSubItem = 1;
		ListView_InsertColumn(hBuseoList, 1, &COL);
		//����Ʈ�信 �μ� ä���
		for (i = 0; i < totB; i++) {
			LI.mask = LVIF_TEXT;
			LI.iItem = i;
			LI.iSubItem = 0;
			LI.pszText = buseo[i].code;
			ListView_InsertItem(hBuseoList, &LI);
			ListView_SetItemText(hBuseoList, i, 1, (LPWSTR)buseo[i].name);
		}
		//�μ��ڵ� edit����
		CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 370, 150, 70, 25, hWnd, (HMENU)ID_CODE, g_hInst, NULL);
		//�μ��� edit����
		CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 520, 150, 70, 25, hWnd, (HMENU)ID_NAME, g_hInst, NULL);
		//���Թ�ư����
		CreateWindow(TEXT("button"), TEXT("����"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 300, 250, 70, 25, hWnd, (HMENU)IDC_INSERT, g_hInst, NULL);
		//������ư����
		CreateWindow(TEXT("button"), TEXT("����"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 400, 250, 70, 25, hWnd, (HMENU)IDC_MODIFY, g_hInst, NULL);
		//������ư����
		CreateWindow(TEXT("button"), TEXT("����"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 500, 250, 70, 25, hWnd, (HMENU)IDC_DEL, g_hInst, NULL);
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_INSERT:	//���Թ�ư
			lstrcpy(tCode, TEXT(""));
			lstrcpy(tName, TEXT(""));

			//�μ��ڵ�� �μ��̸� edit��Ʈ���� ���� tCode,tName�� �ӽ� ����
			GetDlgItemText(hWnd, ID_CODE, tCode, 3);
			GetDlgItemText(hWnd, ID_NAME, tName, 21);

			//�ߺ������� üũ
			for (i = 0; i < totB; i++) {
				if (lstrcmp(buseo[i].code, tCode) == 0 || lstrcmp(buseo[i].name, tName) == 0) {
					isDup = TRUE;
					break;
				}
			}

			//�ߺ����� �ʾҴٸ� �μ� �߰��ؼ� ����Ʈ�信 �ٽ� ����
			if (isDup == FALSE) {
				buseo = (BASE*)realloc(buseo, (totB + 1) * sizeof(BASE));	//�μ� ������ ���Ҵ�
				GetDlgItemText(hWnd, ID_CODE, buseo[totB].code, 3);			//�μ��ڵ� edit�� ���� �μ������� ������.code �� ����
				GetDlgItemText(hWnd, ID_NAME, buseo[totB].name, 21);		//�μ��ڵ� edit�� ���� �μ������� ������.name �� ����
				ListView_DeleteAllItems(hBuseoList);		//����Ʈ�� ���

				totB++;		//�μ�����++

				//����Ʈ�信 �ٽ� �ִ°� ä���
				for (i = 0; i < totB; i++) {
					LI.mask = LVIF_TEXT;
					LI.iItem = i;
					LI.iSubItem = 0;
					LI.pszText = buseo[i].code;
					ListView_InsertItem(hBuseoList, &LI);
					ListView_SetItemText(hBuseoList, i, 1, (LPWSTR)buseo[i].name);
				}
			}
			else {
				isDup = !isDup;
				MessageBox(hWnd, TEXT("�� �ߺ�"), NULL, MB_OK);
			}

			break;
		case IDC_MODIFY:	//������ư

			ind = ListView_GetNextItem(hBuseoList, -1, LVNI_ALL | LVNI_SELECTED);
			if (ind == -1) {
				MessageBox(hWnd, TEXT("������ �׸��� ���� �����Ͻʽÿ�"), TEXT("�˸�"), MB_OK);
			}
			else {
				//�μ��ڵ�� �μ��̸� edit��Ʈ���� ���� tCode,tName�� �ӽ� ����
				GetDlgItemText(hWnd, ID_CODE, tCode, 3);
				GetDlgItemText(hWnd, ID_NAME, tName, 21);

				//�ߺ������� üũ
				for (i = 0; i < totB; i++) {
					if (i != ind && (lstrcmp(buseo[i].code, tCode) == 0 || lstrcmp(buseo[i].name, tName) == 0)) {
						isDup = TRUE;
						break;
					}
				}
				//�ߺ����̶�� �����Ұ�
				if (isDup == TRUE) {
					MessageBox(hWnd, TEXT("�ش� ���� �����մϴ�. �ٸ� ���� �Է��ϼ���."), TEXT("�� �ߺ�"), MB_OK);
					isDup = FALSE;
				}
				else {
					//ind��° buseo�� ������ �ٲ�
					GetDlgItemText(hWnd, ID_CODE, buseo[ind].code, 3);
					GetDlgItemText(hWnd, ID_NAME, buseo[ind].name, 21);

					//����Ʈ�� ���� �ٽ�ä��
					ListView_DeleteAllItems(hBuseoList);		//����Ʈ�� ���

					for (i = 0; i < totB; i++) {
						LI.mask = LVIF_TEXT;
						LI.iItem = i;
						LI.iSubItem = 0;
						LI.pszText = buseo[i].code;
						ListView_InsertItem(hBuseoList, &LI);
						ListView_SetItemText(hBuseoList, i, 1, (LPWSTR)buseo[i].name);
					}
				}
			}
			break;
		case IDC_DEL:
			ind = ListView_GetNextItem(hBuseoList, -1, LVNI_ALL | LVNI_SELECTED);
			if (ind == -1) {
				MessageBox(hWnd, TEXT("������ �׸��� ���� �����Ͻʽÿ�"), TEXT("�˸�"), MB_OK);
			}
			else {
				ListView_DeleteItem(hBuseoList, ind);		//����Ʈ�� ������ ����

				for (i = ind; i < totB - 1; i++) {
					buseo[i] = buseo[i + 1];
				}
				lstrcpy(buseo[totB - 1].code, TEXT(""));
				lstrcpy(buseo[totB - 1].name, TEXT(""));
				totB--;
				buseo = (BASE*)realloc(buseo, totB * sizeof(BASE));
			}
			break;
		}
		return 0;
	case WM_NOTIFY:
		LPNMHDR hdr;
		LPNMLISTVIEW nlv;
		hdr = (LPNMHDR)lParam;
		nlv = (LPNMLISTVIEW)lParam;

		//�μ�����Ʈ�信�� ���õ� �׸� edit�� �Ѹ���
		switch (hdr->code) {
		case LVN_ITEMCHANGED:
			if (nlv->uChanged == LVIF_STATE && nlv->uNewState == (LVIS_SELECTED | LVIS_FOCUSED)) {
				SetDlgItemText(hWnd, ID_CODE, buseo[nlv->iItem].code);
				SetDlgItemText(hWnd, ID_NAME, buseo[nlv->iItem].name);
			}
			return TRUE;
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 300, 155, TEXT("�μ��ڵ�"), 4);
		TextOut(hdc, 450, 155, TEXT("�μ��̸�"), 4);
		EndPaint(hWnd, &ps);
		return 0;
	}
	return (DefMDIChildProc(hWnd, iMessage, wParam, lParam));
}

LRESULT CALLBACK InitReligionMDIProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	LVCOLUMN COL;
	LVITEM LI, tempLI;
	LVFINDINFO fi;
	HDC hdc;
	PAINTSTRUCT ps;
	int i, ind;
	static BOOL isDup = FALSE;
	TCHAR tCode[3], tName[21];		//�ӽ� ���ڿ�

	switch (iMessage) {
	case WM_CREATE:
		//����Ʈ�� ����
		hReligionList = CreateWindow(WC_LISTVIEW, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_SHOWSELALWAYS, 50, 10, 200, 300, hWnd, (HMENU)ID_RLIST, g_hInst, NULL);

		//����Ʈ�� ����߰�
		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 100;
		COL.pszText = (LPWSTR)TEXT("�����ڵ�");
		COL.iSubItem = 0;
		ListView_InsertColumn(hReligionList, 0, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 100;
		COL.pszText = (LPWSTR)TEXT("������");
		COL.iSubItem = 1;
		ListView_InsertColumn(hReligionList, 1, &COL);
		//����Ʈ�信 ���� ä���
		for (i = 0; i < totR; i++) {
			LI.mask = LVIF_TEXT;
			LI.iItem = i;
			LI.iSubItem = 0;
			LI.pszText = religion[i].code;
			ListView_InsertItem(hReligionList, &LI);
			ListView_SetItemText(hReligionList, i, 1, (LPWSTR)religion[i].name);
		}
		//�����ڵ� edit����
		CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 370, 150, 70, 25, hWnd, (HMENU)ID_CODE, g_hInst, NULL);
		//������ edit����
		CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 520, 150, 70, 25, hWnd, (HMENU)ID_NAME, g_hInst, NULL);
		//���Թ�ư����
		CreateWindow(TEXT("button"), TEXT("����"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 300, 250, 70, 25, hWnd, (HMENU)IDC_INSERT, g_hInst, NULL);
		//������ư����
		CreateWindow(TEXT("button"), TEXT("����"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 400, 250, 70, 25, hWnd, (HMENU)IDC_MODIFY, g_hInst, NULL);
		//������ư����
		CreateWindow(TEXT("button"), TEXT("����"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 500, 250, 70, 25, hWnd, (HMENU)IDC_DEL, g_hInst, NULL);
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_INSERT:	//���Թ�ư
			lstrcpy(tCode, TEXT(""));
			lstrcpy(tName, TEXT(""));
			//�����ڵ�� �����̸� edit��Ʈ���� ���� tCode,tName�� �ӽ� ����
			GetDlgItemText(hWnd, ID_CODE, tCode, 3);
			GetDlgItemText(hWnd, ID_NAME, tName, 21);

			//�ߺ������� üũ
			for (i = 0; i < totR; i++) {
				if (lstrcmp(religion[i].code, tCode) == 0 || lstrcmp(religion[i].name, tName) == 0) {
					isDup = TRUE;
					break;
				}
			}
			//�ߺ����� �ʾҴٸ� ���� �߰��ؼ� ����Ʈ�信 �ٽ� ����
			if (isDup == FALSE) {
				religion = (BASE*)realloc(religion, (totR + 1) * sizeof(BASE));	//���� ������ ���Ҵ�
				GetDlgItemText(hWnd, ID_CODE, religion[totR].code, 3);			//�����ڵ� edit�� ���� �μ������� ������.code �� ����
				GetDlgItemText(hWnd, ID_NAME, religion[totR].name, 21);			//�����ڵ� edit�� ���� �μ������� ������.name �� ����
				ListView_DeleteAllItems(hReligionList);		//����Ʈ�� ���

				totR++;		//��������++

				//����Ʈ�信 �ٽ� �ִ°� ä���
				for (i = 0; i < totR; i++) {
					LI.mask = LVIF_TEXT;
					LI.iItem = i;
					LI.iSubItem = 0;
					LI.pszText = religion[i].code;
					ListView_InsertItem(hReligionList, &LI);
					ListView_SetItemText(hReligionList, i, 1, (LPWSTR)religion[i].name);
				}
			}
			else {
				isDup = !isDup;
				MessageBox(hWnd, TEXT("�� �ߺ�"), NULL, MB_OK);
			}

			break;
		case IDC_MODIFY:	//������ư

			ind = ListView_GetNextItem(hReligionList, -1, LVNI_ALL | LVNI_SELECTED);
			if (ind == -1) {
				MessageBox(hWnd, TEXT("������ �׸��� ���� �����Ͻʽÿ�"), TEXT("�˸�"), MB_OK);
			}
			else {
				lstrcpy(tCode, TEXT(""));
				lstrcpy(tName, TEXT(""));
				//�����ڵ�� �����̸� edit��Ʈ���� ���� tCode,tName�� �ӽ� ����
				GetDlgItemText(hWnd, ID_CODE, tCode, 3);
				GetDlgItemText(hWnd, ID_NAME, tName, 21);

				//�ߺ������� üũ
				for (i = 0; i < totR; i++) {
					if (i != ind && (lstrcmp(religion[i].code, tCode) == 0 || lstrcmp(religion[i].name, tName) == 0)) {
						isDup = TRUE;
						break;
					}
				}
				//�ߺ����̶�� ���� �Ұ�
				if (isDup == TRUE) {
					MessageBox(hWnd, TEXT("�ش� ���� �����մϴ�. �ٸ� ���� �Է��ϼ���."), TEXT("�� �ߺ�"), MB_OK);
					isDup = FALSE;
				}
				else {
					//ind��° religion�� ������ �ٲ�
					GetDlgItemText(hWnd, ID_CODE, religion[ind].code, 3);
					GetDlgItemText(hWnd, ID_NAME, religion[ind].name, 21);

					//����Ʈ�� ���� �ٽ�ä��
					ListView_DeleteAllItems(hReligionList);

					for (i = 0; i < totR; i++) {
						LI.mask = LVIF_TEXT;
						LI.iItem = i;
						LI.iSubItem = 0;
						LI.pszText = religion[i].code;
						ListView_InsertItem(hReligionList, &LI);
						ListView_SetItemText(hReligionList, i, 1, (LPWSTR)religion[i].name);
					}
				}
			}
			break;
		case IDC_DEL:
			ind = ListView_GetNextItem(hReligionList, -1, LVNI_ALL | LVNI_SELECTED);
			if (ind == -1) {
				MessageBox(hWnd, TEXT("������ �׸��� ���� �����Ͻʽÿ�"), TEXT("�˸�"), MB_OK);
			}
			else {
				ListView_DeleteItem(hReligionList, ind);		//����Ʈ�� ������ ����

				for (i = ind; i < totR - 1; i++) {
					religion[i] = religion[i + 1];
				}
				lstrcpy(religion[totR - 1].code, TEXT(""));
				lstrcpy(religion[totR - 1].name, TEXT(""));
				totR--;
				religion = (BASE*)realloc(religion, totR * sizeof(BASE));
			}
			break;
		}
		return 0;
	case WM_NOTIFY:
		LPNMHDR hdr;
		LPNMLISTVIEW nlv;
		hdr = (LPNMHDR)lParam;
		nlv = (LPNMLISTVIEW)lParam;

		//��������Ʈ�信�� ���õ� �׸� edit�� �Ѹ���
		switch (hdr->code) {
		case LVN_ITEMCHANGED:
			if (nlv->uChanged == LVIF_STATE && nlv->uNewState == (LVIS_SELECTED | LVIS_FOCUSED)) {
				SetDlgItemText(hWnd, ID_CODE, religion[nlv->iItem].code);
				SetDlgItemText(hWnd, ID_NAME, religion[nlv->iItem].name);
			}
			return TRUE;
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 300, 155, TEXT("�����ڵ�"), 4);
		TextOut(hdc, 450, 155, TEXT("�����̸�"), 4);
		EndPaint(hWnd, &ps);
		return 0;
	}
	return (DefMDIChildProc(hWnd, iMessage, wParam, lParam));
}

LRESULT CALLBACK InitPositionMDIProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	LVCOLUMN COL;
	LVITEM LI, tempLI;
	LVFINDINFO fi;
	HDC hdc;
	PAINTSTRUCT ps;
	int i, ind;
	static BOOL isDup = FALSE;
	TCHAR tCode[3], tName[21];		//�ӽ� ���ڿ�

	switch (iMessage) {
	case WM_CREATE:
		//����Ʈ�� ����
		hPositionList = CreateWindow(WC_LISTVIEW, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_SHOWSELALWAYS, 50, 10, 200, 300, hWnd, (HMENU)ID_PLIST, g_hInst, NULL);

		//����Ʈ�� ����߰�
		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 100;
		COL.pszText = (LPWSTR)TEXT("�����ڵ�");
		COL.iSubItem = 0;
		ListView_InsertColumn(hPositionList, 0, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 100;
		COL.pszText = (LPWSTR)TEXT("������");
		COL.iSubItem = 1;
		ListView_InsertColumn(hPositionList, 1, &COL);
		//����Ʈ�信 ���� ä���
		for (i = 0; i < totP; i++) {
			LI.mask = LVIF_TEXT;
			LI.iItem = i;
			LI.iSubItem = 0;
			LI.pszText = position[i].code;
			ListView_InsertItem(hPositionList, &LI);
			ListView_SetItemText(hPositionList, i, 1, (LPWSTR)position[i].name);
		}
		//�����ڵ� edit����
		CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 370, 150, 70, 25, hWnd, (HMENU)ID_CODE, g_hInst, NULL);
		//������ edit����
		CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 520, 150, 70, 25, hWnd, (HMENU)ID_NAME, g_hInst, NULL);
		//���Թ�ư����
		CreateWindow(TEXT("button"), TEXT("����"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 300, 250, 70, 25, hWnd, (HMENU)IDC_INSERT, g_hInst, NULL);
		//������ư����
		CreateWindow(TEXT("button"), TEXT("����"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 400, 250, 70, 25, hWnd, (HMENU)IDC_MODIFY, g_hInst, NULL);
		//������ư����
		CreateWindow(TEXT("button"), TEXT("����"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 500, 250, 70, 25, hWnd, (HMENU)IDC_DEL, g_hInst, NULL);
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_INSERT:	//���Թ�ư
			lstrcpy(tCode, TEXT(""));
			lstrcpy(tName, TEXT(""));
			//�����ڵ�� �����̸� edit��Ʈ���� ���� tCode,tName�� �ӽ� ����
			GetDlgItemText(hWnd, ID_CODE, tCode, 3);
			GetDlgItemText(hWnd, ID_NAME, tName, 21);

			//�ߺ������� üũ
			for (i = 0; i < totP; i++) {
				if (lstrcmp(position[i].code, tCode) == 0 || lstrcmp(position[i].name, tName) == 0) {
					isDup = TRUE;
					break;
				}
			}
			//�ߺ����� �ʾҴٸ� �μ� �߰��ؼ� ����Ʈ�信 �ٽ� ����
			if (isDup == FALSE) {
				position = (BASE*)realloc(position, (totP + 1) * sizeof(BASE));	//���� ������ ���Ҵ�
				GetDlgItemText(hWnd, ID_CODE, position[totP].code, 3);			//�����ڵ� edit�� ���� �μ������� ������.code �� ����
				GetDlgItemText(hWnd, ID_NAME, position[totP].name, 21);			//�����ڵ� edit�� ���� �μ������� ������.name �� ����
				ListView_DeleteAllItems(hPositionList);		//����Ʈ�� ���

				totP++;		//��������++

				//����Ʈ�信 �ٽ� �ִ°� ä���
				for (i = 0; i < totP; i++) {
					LI.mask = LVIF_TEXT;
					LI.iItem = i;
					LI.iSubItem = 0;
					LI.pszText = position[i].code;
					ListView_InsertItem(hPositionList, &LI);
					ListView_SetItemText(hPositionList, i, 1, (LPWSTR)position[i].name);
				}
			}
			else {
				isDup = !isDup;
				MessageBox(hWnd, TEXT("�� �ߺ�"), NULL, MB_OK);

			}

			break;
		case IDC_MODIFY:	//������ư

			ind = ListView_GetNextItem(hPositionList, -1, LVNI_ALL | LVNI_SELECTED);
			if (ind == -1) {
				MessageBox(hWnd, TEXT("������ �׸��� ���� �����Ͻʽÿ�"), TEXT("�˸�"), MB_OK);
			}
			else {
				lstrcpy(tCode, TEXT(""));
				lstrcpy(tName, TEXT(""));
				//�����ڵ�� �����̸� edit��Ʈ���� ���� tCode,tName�� �ӽ� ����
				GetDlgItemText(hWnd, ID_CODE, tCode, 3);
				GetDlgItemText(hWnd, ID_NAME, tName, 21);

				//�ߺ������� üũ
				for (i = 0; i < totP; i++) {
					if (i != ind && (lstrcmp(position[i].code, tCode) == 0 || lstrcmp(position[i].name, tName) == 0)) {
						isDup = TRUE;
						break;
					}
				}
				if (isDup == TRUE) {
					MessageBox(hWnd, TEXT("�ش� ���� �����մϴ�. �ٸ� ���� �Է��ϼ���."), TEXT("�� �ߺ�"), MB_OK);
					isDup = FALSE;
				}
				else {
					//ind��° position�� ������ �ٲ�
					GetDlgItemText(hWnd, ID_CODE, position[ind].code, 3);
					GetDlgItemText(hWnd, ID_NAME, position[ind].name, 21);

					//����Ʈ�� ���� �ٽ�ä��
					ListView_DeleteAllItems(hPositionList);		//����Ʈ�� ���

					for (i = 0; i < totP; i++) {
						LI.mask = LVIF_TEXT;
						LI.iItem = i;
						LI.iSubItem = 0;
						LI.pszText = position[i].code;
						ListView_InsertItem(hPositionList, &LI);
						ListView_SetItemText(hPositionList, i, 1, (LPWSTR)position[i].name);
					}
				}
			}
			break;
		case IDC_DEL:
			ind = ListView_GetNextItem(hPositionList, -1, LVNI_ALL | LVNI_SELECTED);
			if (ind == -1) {
				MessageBox(hWnd, TEXT("������ �׸��� ���� �����Ͻʽÿ�"), TEXT("�˸�"), MB_OK);
			}
			else {
				ListView_DeleteItem(hPositionList, ind);		//����Ʈ�� ������ ����

				for (i = ind; i < totP - 1; i++) {
					position[i] = position[i + 1];
				}
				lstrcpy(position[totP - 1].code, TEXT(""));
				lstrcpy(position[totP - 1].name, TEXT(""));
				totP--;
				position = (BASE*)realloc(position, totP * sizeof(BASE));
			}
			break;
		}
		return 0;
	case WM_NOTIFY:
		LPNMHDR hdr;
		LPNMLISTVIEW nlv;
		hdr = (LPNMHDR)lParam;
		nlv = (LPNMLISTVIEW)lParam;

		//��������Ʈ�信�� ���õ� �׸� edit�� �Ѹ���
		switch (hdr->code) {
		case LVN_ITEMCHANGED:
			if (nlv->uChanged == LVIF_STATE && nlv->uNewState == (LVIS_SELECTED | LVIS_FOCUSED)) {
				SetDlgItemText(hWnd, ID_CODE, position[nlv->iItem].code);
				SetDlgItemText(hWnd, ID_NAME, position[nlv->iItem].name);
			}
			return TRUE;
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 300, 155, TEXT("�����ڵ�"), 4);
		TextOut(hdc, 450, 155, TEXT("�����̸�"), 4);
		EndPaint(hWnd, &ps);
		return 0;
	}
	return (DefMDIChildProc(hWnd, iMessage, wParam, lParam));
}