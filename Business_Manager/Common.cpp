#include "Common.h"

extern HINSTANCE g_hInst;
extern HWND g_hFrameWnd;	//메인 프레임 윈도우 핸들
extern HWND g_hMDIClient;	//클라이언트 윈도우 핸들
HWND hBuseoList;	//부서리스트뷰 핸들
HWND hPositionList;	//직위리스트뷰 핸들
HWND hReligionList;	//종교리스트뷰 핸들
int totB = 0;		//부서갯수
int totP = 0;		//직위갯수
int totR = 0;		//종교갯수
int selB = -1;		//선택된 부서 index
BASE* buseo;		//부서
BASE* position;		//직위
BASE* religion;		//종교

enum { IDC_INSERT = 1, IDC_MODIFY, IDC_DEL, ID_NAME, ID_CODE, ID_BLIST, ID_RLIST,ID_PLIST };
LRESULT CALLBACK MDIWndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	CLIENTCREATESTRUCT ccs;
	MDICREATESTRUCT mcs;

	switch (iMessage) {
	case WM_CREATE:
		InitCommonControls();
		//MDI Client 윈도우 만듬
		ccs.hWindowMenu = GetSubMenu(GetMenu(hWnd), 1);
		ccs.idFirstChild = IDM_WINDOWCHILD;
		g_hMDIClient = CreateWindow(TEXT("MDIClient"), NULL, WS_CHILD | WS_VSCROLL | WS_HSCROLL | WS_CLIPCHILDREN, 0, 0, 0, 0, hWnd, (HMENU)NULL, g_hInst, (LPSTR)&ccs);
		ShowWindow(g_hMDIClient, SW_SHOW);
		//초기에 부서,직위,종교 1개 사이즈로 할당
		buseo = (BASE*)malloc(sizeof(BASE));
		position = (BASE*)malloc(sizeof(BASE));
		religion = (BASE*)malloc(sizeof(BASE));
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
			//새 MDI 윈도우 만듬
		case IDM_BUSEO:		//기초정보관리(메뉴바)->부서
			mcs.szClass = TEXT("InitBuseoMDI");
			mcs.szTitle = TEXT("부서");
			mcs.hOwner = g_hInst;
			mcs.x = mcs.y = CW_USEDEFAULT;
			mcs.cx = mcs.cy = CW_USEDEFAULT;
			mcs.style = MDIS_ALLCHILDSTYLES;
			SendMessage(g_hMDIClient, WM_MDICREATE, 0, (LPARAM)(LPMDICREATESTRUCT)&mcs);
			break;
		case IDM_POSITION:	//기초정보관리(메뉴바)->직위
			mcs.szClass = TEXT("InitPosMDI");
			mcs.szTitle = TEXT("직위");
			mcs.hOwner = g_hInst;
			mcs.x = mcs.y = CW_USEDEFAULT;
			mcs.cx = mcs.cy = CW_USEDEFAULT;
			mcs.style = MDIS_ALLCHILDSTYLES;
			SendMessage(g_hMDIClient, WM_MDICREATE, 0, (LPARAM)(LPMDICREATESTRUCT)&mcs);
			break;
		case IDM_RELIGION:	//기초정보관리(메뉴바)->종교
			mcs.szClass = TEXT("InitRelMDI");
			mcs.szTitle = TEXT("종교");
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
		//할당된 부서,직위,종교 free
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
	TCHAR tCode[3], tName[21];		//임시 문자열

	switch (iMessage) {
	case WM_CREATE:
		//리스트뷰 생성
		hBuseoList = CreateWindow(WC_LISTVIEW, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_SHOWSELALWAYS, 50, 10, 200, 300, hWnd, (HMENU)ID_BLIST, g_hInst, NULL);

		//리스트에 헤더추가
		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 100;
		COL.pszText = (LPWSTR)TEXT("부서코드");
		COL.iSubItem = 0;
		ListView_InsertColumn(hBuseoList, 0, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 100;
		COL.pszText = (LPWSTR)TEXT("부서명");
		COL.iSubItem = 1;
		ListView_InsertColumn(hBuseoList, 1, &COL);
		//리스트뷰에 부서 채우기
		for (i = 0; i < totB; i++) {
			LI.mask = LVIF_TEXT;
			LI.iItem = i;
			LI.iSubItem = 0;
			LI.pszText = buseo[i].code;
			ListView_InsertItem(hBuseoList, &LI);
			ListView_SetItemText(hBuseoList, i, 1, (LPWSTR)buseo[i].name);
		}
		//부서코드 edit생성
		CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 370, 150, 70, 25, hWnd, (HMENU)ID_CODE, g_hInst, NULL);
		//부서명 edit생성
		CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 520, 150, 70, 25, hWnd, (HMENU)ID_NAME, g_hInst, NULL);
		//삽입버튼생성
		CreateWindow(TEXT("button"), TEXT("삽입"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 300, 250, 70, 25, hWnd, (HMENU)IDC_INSERT, g_hInst, NULL);
		//수정버튼생성
		CreateWindow(TEXT("button"), TEXT("수정"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 400, 250, 70, 25, hWnd, (HMENU)IDC_MODIFY, g_hInst, NULL);
		//삭제버튼생성
		CreateWindow(TEXT("button"), TEXT("삭제"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 500, 250, 70, 25, hWnd, (HMENU)IDC_DEL, g_hInst, NULL);
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_INSERT:	//삽입버튼
			lstrcpy(tCode, TEXT(""));
			lstrcpy(tName, TEXT(""));
			//부서코드와 부서이름 edit컨트롤의 값을 tCode,tName에 임시 저장
			GetDlgItemText(hWnd, ID_CODE, tCode, 3);
			GetDlgItemText(hWnd, ID_NAME, tName, 21);

			//중복값인지 체크
			for (i = 0; i < totB; i++) {
				if (lstrcmp(buseo[i].code, tCode) == 0 || lstrcmp(buseo[i].name, tName) == 0) {
					isDup = TRUE;
					break;
				}
			}
			//중복되지 않았다면 부서 추가해서 리스트뷰에 다시 보임
			if (isDup == FALSE) {
				buseo = (BASE*)realloc(buseo, (totB + 1) * sizeof(BASE));	//부서 포인터 재할당
				GetDlgItemText(hWnd, ID_CODE, buseo[totB].code, 3);			//부서코드 edit의 값을 부서포인터 마지막.code 에 담음
				GetDlgItemText(hWnd, ID_NAME, buseo[totB].name, 21);		//부서코드 edit의 값을 부서포인터 마지막.name 에 담음
				ListView_DeleteAllItems(hBuseoList);		//리스트뷰 비움

				totB++;		//부서갯수++

				//리스트뷰에 다시 있는값 채우기
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
				MessageBox(hWnd, TEXT("값 중복"), NULL, MB_OK);
			}

			break;
		case IDC_MODIFY:	//수정버튼

			ind = ListView_GetNextItem(hBuseoList, -1, LVNI_ALL | LVNI_SELECTED);
			if (ind == -1) {
				MessageBox(hWnd, TEXT("수정할 항목을 먼저 선택하십시오"), TEXT("알림"), MB_OK);
			}
			else {
				//ind번째 buseo의 값들을 바꿈
				GetDlgItemText(hWnd, ID_CODE, buseo[ind].code, 3);
				GetDlgItemText(hWnd, ID_NAME, buseo[ind].name, 21);
				//리스트뷰 비우고 다시채움
				ListView_DeleteAllItems(hBuseoList);		//리스트뷰 비움
				MessageBox(hWnd, NULL, NULL, MB_OK);
				for (i = 0; i < totB; i++) {
					LI.mask = LVIF_TEXT;
					LI.iItem = i;
					LI.iSubItem = 0;
					LI.pszText = buseo[i].code;
					ListView_InsertItem(hBuseoList, &LI);
					ListView_SetItemText(hBuseoList, i, 1, (LPWSTR)buseo[i].name);
				}
			}
			break;
		case IDC_DEL:
			ind = ListView_GetNextItem(hBuseoList, -1, LVNI_ALL | LVNI_SELECTED);
			if (ind == -1) {
				MessageBox(hWnd, TEXT("삭제할 항목을 먼저 선택하십시오"), TEXT("알림"), MB_OK);
			}
			else {
				ListView_DeleteItem(hBuseoList, ind);		//리스트뷰 아이템 지움

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

		//부서리스트뷰에서 선택된 항목 edit로 뿌리기
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
		TextOut(hdc, 300, 155, TEXT("부서코드"), 4);
		TextOut(hdc, 450, 155, TEXT("부서이름"), 4);
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
	TCHAR tCode[3], tName[21];		//임시 문자열

	switch (iMessage) {
	case WM_CREATE:
		//리스트뷰 생성
		hReligionList = CreateWindow(WC_LISTVIEW, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_SHOWSELALWAYS, 50, 10, 200, 300, hWnd, (HMENU)ID_RLIST, g_hInst, NULL);

		//리스트에 헤더추가
		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 100;
		COL.pszText = (LPWSTR)TEXT("종교코드");
		COL.iSubItem = 0;
		ListView_InsertColumn(hReligionList, 0, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 100;
		COL.pszText = (LPWSTR)TEXT("종교명");
		COL.iSubItem = 1;
		ListView_InsertColumn(hReligionList, 1, &COL);
		//리스트뷰에 종교 채우기
		for (i = 0; i < totB; i++) {
			LI.mask = LVIF_TEXT;
			LI.iItem = i;
			LI.iSubItem = 0;
			LI.pszText = religion[i].code;
			ListView_InsertItem(hReligionList, &LI);
			ListView_SetItemText(hReligionList, i, 1, (LPWSTR)religion[i].name);
		}
		//종교코드 edit생성
		CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 370, 150, 70, 25, hWnd, (HMENU)ID_CODE, g_hInst, NULL);
		//종교명 edit생성
		CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 520, 150, 70, 25, hWnd, (HMENU)ID_NAME, g_hInst, NULL);
		//삽입버튼생성
		CreateWindow(TEXT("button"), TEXT("삽입"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 300, 250, 70, 25, hWnd, (HMENU)IDC_INSERT, g_hInst, NULL);
		//수정버튼생성
		CreateWindow(TEXT("button"), TEXT("수정"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 400, 250, 70, 25, hWnd, (HMENU)IDC_MODIFY, g_hInst, NULL);
		//삭제버튼생성
		CreateWindow(TEXT("button"), TEXT("삭제"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 500, 250, 70, 25, hWnd, (HMENU)IDC_DEL, g_hInst, NULL);
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_INSERT:	//삽입버튼
			lstrcpy(tCode, TEXT(""));
			lstrcpy(tName, TEXT(""));
			//종교코드와 종교이름 edit컨트롤의 값을 tCode,tName에 임시 저장
			GetDlgItemText(hWnd, ID_CODE, tCode, 3);
			GetDlgItemText(hWnd, ID_NAME, tName, 21);

			//중복값인지 체크
			for (i = 0; i < totR; i++) {
				if (lstrcmp(religion[i].code, tCode) == 0 || lstrcmp(religion[i].name, tName) == 0) {
					isDup = TRUE;
					break;
				}
			}
			//중복되지 않았다면 종교 추가해서 리스트뷰에 다시 보임
			if (isDup == FALSE) {
				religion = (BASE*)realloc(religion, (totR + 1) * sizeof(BASE));	//종교 포인터 재할당
				GetDlgItemText(hWnd, ID_CODE, religion[totR].code, 3);			//종교코드 edit의 값을 부서포인터 마지막.code 에 담음
				GetDlgItemText(hWnd, ID_NAME, religion[totR].name, 21);			//종교코드 edit의 값을 부서포인터 마지막.name 에 담음
				ListView_DeleteAllItems(hReligionList);		//리스트뷰 비움

				totR++;		//종교갯수++

				//리스트뷰에 다시 있는값 채우기
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
				MessageBox(hWnd, TEXT("값 중복"), NULL, MB_OK);
			}

			break;
		case IDC_MODIFY:	//수정버튼

			ind = ListView_GetNextItem(hReligionList, -1, LVNI_ALL | LVNI_SELECTED);
			if (ind == -1) {
				MessageBox(hWnd, TEXT("수정할 항목을 먼저 선택하십시오"), TEXT("알림"), MB_OK);
			}
			else {
				//ind번째 religion의 값들을 바꿈
				GetDlgItemText(hWnd, ID_CODE, religion[ind].code, 3);
				GetDlgItemText(hWnd, ID_NAME, religion[ind].name, 21);
				//리스트뷰 비우고 다시채움
				ListView_DeleteAllItems(hReligionList);		//리스트뷰 비움
				for (i = 0; i < totR; i++) {
					LI.mask = LVIF_TEXT;
					LI.iItem = i;
					LI.iSubItem = 0;
					LI.pszText = religion[i].code;
					ListView_InsertItem(hReligionList, &LI);
					ListView_SetItemText(hReligionList, i, 1, (LPWSTR)religion[i].name);
				}
			}
			break;
		case IDC_DEL:
			ind = ListView_GetNextItem(hReligionList, -1, LVNI_ALL | LVNI_SELECTED);
			if (ind == -1) {
				MessageBox(hWnd, TEXT("삭제할 항목을 먼저 선택하십시오"), TEXT("알림"), MB_OK);
			}
			else {
				ListView_DeleteItem(hReligionList, ind);		//리스트뷰 아이템 지움

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

		//종교리스트뷰에서 선택된 항목 edit로 뿌리기
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
		TextOut(hdc, 300, 155, TEXT("종교코드"), 4);
		TextOut(hdc, 450, 155, TEXT("종교이름"), 4);
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
	TCHAR tCode[3], tName[21];		//임시 문자열

	switch (iMessage) {
	case WM_CREATE:
		//리스트뷰 생성
		hPositionList = CreateWindow(WC_LISTVIEW, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_SHOWSELALWAYS, 50, 10, 200, 300, hWnd, (HMENU)ID_PLIST, g_hInst, NULL);

		//리스트에 헤더추가
		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 100;
		COL.pszText = (LPWSTR)TEXT("직위코드");
		COL.iSubItem = 0;
		ListView_InsertColumn(hPositionList, 0, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 100;
		COL.pszText = (LPWSTR)TEXT("직위명");
		COL.iSubItem = 1;
		ListView_InsertColumn(hPositionList, 1, &COL);
		//리스트뷰에 종교 채우기
		for (i = 0; i < totP; i++) {
			LI.mask = LVIF_TEXT;
			LI.iItem = i;
			LI.iSubItem = 0;
			LI.pszText = position[i].code;
			ListView_InsertItem(hPositionList, &LI);
			ListView_SetItemText(hPositionList, i, 1, (LPWSTR)position[i].name);
		}
		//직위코드 edit생성
		CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 370, 150, 70, 25, hWnd, (HMENU)ID_CODE, g_hInst, NULL);
		//직위명 edit생성
		CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 520, 150, 70, 25, hWnd, (HMENU)ID_NAME, g_hInst, NULL);
		//삽입버튼생성
		CreateWindow(TEXT("button"), TEXT("삽입"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 300, 250, 70, 25, hWnd, (HMENU)IDC_INSERT, g_hInst, NULL);
		//수정버튼생성
		CreateWindow(TEXT("button"), TEXT("수정"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 400, 250, 70, 25, hWnd, (HMENU)IDC_MODIFY, g_hInst, NULL);
		//삭제버튼생성
		CreateWindow(TEXT("button"), TEXT("삭제"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 500, 250, 70, 25, hWnd, (HMENU)IDC_DEL, g_hInst, NULL);
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_INSERT:	//삽입버튼
			lstrcpy(tCode, TEXT(""));
			lstrcpy(tName, TEXT(""));
			//직위코드와 직위이름 edit컨트롤의 값을 tCode,tName에 임시 저장
			GetDlgItemText(hWnd, ID_CODE, tCode, 3);
			GetDlgItemText(hWnd, ID_NAME, tName, 21);

			//중복값인지 체크
			for (i = 0; i < totP; i++) {
				if (lstrcmp(position[i].code, tCode) == 0 || lstrcmp(position[i].name, tName) == 0) {
					isDup = TRUE;
					break;
				}
			}
			//중복되지 않았다면 부서 추가해서 리스트뷰에 다시 보임
			if (isDup == FALSE) {
				position = (BASE*)realloc(position, (totP + 1) * sizeof(BASE));	//직위 포인터 재할당
				GetDlgItemText(hWnd, ID_CODE, position[totP].code, 3);			//직위코드 edit의 값을 부서포인터 마지막.code 에 담음
				GetDlgItemText(hWnd, ID_NAME, position[totP].name, 21);			//직위코드 edit의 값을 부서포인터 마지막.name 에 담음
				ListView_DeleteAllItems(hPositionList);		//리스트뷰 비움

				totP++;		//직위갯수++

				//리스트뷰에 다시 있는값 채우기
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
				MessageBox(hWnd, TEXT("값 중복"), NULL, MB_OK);
			}

			break;
		case IDC_MODIFY:	//수정버튼

			ind = ListView_GetNextItem(hPositionList, -1, LVNI_ALL | LVNI_SELECTED);
			if (ind == -1) {
				MessageBox(hWnd, TEXT("수정할 항목을 먼저 선택하십시오"), TEXT("알림"), MB_OK);
			}
			else {
				//ind번째 position의 값들을 바꿈
				GetDlgItemText(hWnd, ID_CODE, position[ind].code, 3);
				GetDlgItemText(hWnd, ID_NAME, position[ind].name, 21);
				//리스트뷰 비우고 다시채움
				ListView_DeleteAllItems(hPositionList);		//리스트뷰 비움
				for (i = 0; i < totP; i++) {
					LI.mask = LVIF_TEXT;
					LI.iItem = i;
					LI.iSubItem = 0;
					LI.pszText = position[i].code;
					ListView_InsertItem(hPositionList, &LI);
					ListView_SetItemText(hPositionList, i, 1, (LPWSTR)position[i].name);
				}
			}
			break;
		case IDC_DEL:
			ind = ListView_GetNextItem(hPositionList, -1, LVNI_ALL | LVNI_SELECTED);
			if (ind == -1) {
				MessageBox(hWnd, TEXT("삭제할 항목을 먼저 선택하십시오"), TEXT("알림"), MB_OK);
			}
			else {
				ListView_DeleteItem(hPositionList, ind);		//리스트뷰 아이템 지움

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

		//직위리스트뷰에서 선택된 항목 edit로 뿌리기
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
		TextOut(hdc, 300, 155, TEXT("직위코드"), 4);
		TextOut(hdc, 450, 155, TEXT("직위이름"), 4);
		EndPaint(hWnd, &ps);
		return 0;
	}
	return (DefMDIChildProc(hWnd, iMessage, wParam, lParam));
}