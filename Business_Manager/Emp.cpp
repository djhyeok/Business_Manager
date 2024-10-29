#include "Emp.h"
#include "Common.h"

/*
에디트에 입력한 값을 리스트뷰에 뿌리고 에디트 컨트롤 초기화
삽입,수정,삭제 후 리스트뷰 다 비우고 다시 데이터수만큼 리스트뷰에 뿌리기
*/

extern HINSTANCE g_hInst;
extern int totB;			//부서갯수
extern int totP;			//직위갯수
extern int totR;			//종교갯수
extern int totWEmp;			//사원수
extern int totREmp;			//퇴직사원수
extern BASE* buseo;			//부서
extern BASE* position;		//직위
extern BASE* religion;		//종교
extern EMP* workEmp;		//사원
extern EMP* retireEmp;		//퇴직사원

HWND hEMPList, hEmpNo, hEmpBuseo, hEmpPoscode, hEmpIndate, hEmpName1, hEmpName2, hEmpName3, hEmpMale, hEmpFemale, hEmpBirth, hEmpAddress,
hEmpEmail, hEmpPhone1, hEmpPhone2, hEmpHeight, hEmpWeight, hEmpLefteye, hEmpRighteye, hEmpSingle, hEmpMarriage, hEmpRelligion;	//컨트롤 핸들
enum {
	ID_EMPLIST = 1, ID_EMPNO, ID_BUSEO, ID_POSCODE, ID_INDATE, ID_NAME1, ID_NAME2, ID_NAME3, ID_MALE, ID_FEMALE, ID_BIRTH, ID_ADDRESS, ID_EMAIL,
	ID_PHONE1, ID_PHONE2, ID_HEIGHT, ID_WEIGHT, ID_LEFTEYE, ID_RIGHTEYE, ID_SINGLE, ID_MARRIAGE, ID_RELLIGION, ID_RETIRE, IDC_INSERT, IDC_MODIFY, IDC_DELETE
};

//사원관리 프로시져
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

		//리스트뷰 생성
		hEMPList = CreateWindow(WC_LISTVIEW, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_SHOWSELALWAYS, 350, 10, 1150, 700, hWnd, (HMENU)ID_EMPLIST, g_hInst, NULL);
		//리스트에 헤더추가
		//(사원번호,부서,직책,입사일,이름,성별,생년월일,주소,전자우편,연락처,신장,체중,시력(좌),시력(우),결혼관계,종교)
		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 150;
		COL.pszText = (LPWSTR)TEXT("사원번호");
		COL.iSubItem = 0;
		ListView_InsertColumn(hEMPList, 0, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 50;
		COL.pszText = (LPWSTR)TEXT("부서");
		COL.iSubItem = 1;
		ListView_InsertColumn(hEMPList, 1, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 60;
		COL.pszText = (LPWSTR)TEXT("직책");
		COL.iSubItem = 2;
		ListView_InsertColumn(hEMPList, 2, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 80;
		COL.pszText = (LPWSTR)TEXT("입사일");
		COL.iSubItem = 3;
		ListView_InsertColumn(hEMPList, 3, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 50;
		COL.pszText = (LPWSTR)TEXT("이름");
		COL.iSubItem = 4;
		ListView_InsertColumn(hEMPList, 4, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 70;
		COL.pszText = (LPWSTR)TEXT("영문이름");
		COL.iSubItem = 5;
		ListView_InsertColumn(hEMPList, 5, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 70;
		COL.pszText = (LPWSTR)TEXT("한자이름");
		COL.iSubItem = 6;
		ListView_InsertColumn(hEMPList, 6, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 50;
		COL.pszText = (LPWSTR)TEXT("성별");
		COL.iSubItem = 7;
		ListView_InsertColumn(hEMPList, 7, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 80;
		COL.pszText = (LPWSTR)TEXT("생년월일");
		COL.iSubItem = 8;
		ListView_InsertColumn(hEMPList, 8, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 100;
		COL.pszText = (LPWSTR)TEXT("주소");
		COL.iSubItem = 9;
		ListView_InsertColumn(hEMPList, 9, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 100;
		COL.pszText = (LPWSTR)TEXT("전자우편");
		COL.iSubItem = 10;
		ListView_InsertColumn(hEMPList, 10, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 100;
		COL.pszText = (LPWSTR)TEXT("연락처1");
		COL.iSubItem = 11;
		ListView_InsertColumn(hEMPList, 11, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 100;
		COL.pszText = (LPWSTR)TEXT("연락처2");
		COL.iSubItem = 12;
		ListView_InsertColumn(hEMPList, 12, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 40;
		COL.pszText = (LPWSTR)TEXT("신장");
		COL.iSubItem = 13;
		ListView_InsertColumn(hEMPList, 13, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 40;
		COL.pszText = (LPWSTR)TEXT("체중");
		COL.iSubItem = 14;
		ListView_InsertColumn(hEMPList, 14, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 60;
		COL.pszText = (LPWSTR)TEXT("결혼관계");
		COL.iSubItem = 15;
		ListView_InsertColumn(hEMPList, 15, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 50;
		COL.pszText = (LPWSTR)TEXT("종교");
		COL.iSubItem = 16;
		ListView_InsertColumn(hEMPList, 16, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 60;
		COL.pszText = (LPWSTR)TEXT("시력(좌)");
		COL.iSubItem = 17;
		ListView_InsertColumn(hEMPList, 17, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 60;
		COL.pszText = (LPWSTR)TEXT("시력(우)");
		COL.iSubItem = 18;
		ListView_InsertColumn(hEMPList, 18, &COL);

		//리스트뷰에 사원 채우기

		//사원번호 에디트컨트롤 생성
		hEmpNo = CreateWindow(TEXT("static"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 150, 10, 150, 25, hWnd, (HMENU)ID_EMPNO, g_hInst, NULL);
		//부서 콤보박스 생성
		hEmpBuseo = CreateWindow(TEXT("combobox"), NULL, WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST, 150, 45, 153, 200, hWnd, (HMENU)ID_BUSEO, g_hInst, NULL);
		for (i = 0; i < totB; i++) {
			SendMessage(hEmpBuseo, CB_ADDSTRING, 0, (LPARAM)buseo[i].name);
		}
		//직책 콤보박스 생성
		hEmpPoscode = CreateWindow(TEXT("combobox"), NULL, WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST, 150, 80, 153, 200, hWnd, (HMENU)ID_POSCODE, g_hInst, NULL);
		for (i = 0; i < totP; i++) {
			SendMessage(hEmpPoscode, CB_ADDSTRING, 0, (LPARAM)position[i].name);
		}
		//입사일 날짜컨트롤 생성
		hEmpIndate = CreateWindow(DATETIMEPICK_CLASS, NULL, WS_BORDER | WS_CHILD | WS_VISIBLE | DTS_SHORTDATEFORMAT, 150, 115, 153, 25, hWnd, (HMENU)ID_INDATE, g_hInst, NULL);
		//이름 에디트컨트롤 생성
		hEmpName1 = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 150, 150, 150, 25, hWnd, (HMENU)ID_NAME1, g_hInst, NULL);
		hEmpName2 = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 150, 185, 150, 25, hWnd, (HMENU)ID_NAME2, g_hInst, NULL);
		hEmpName3 = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 150, 220, 150, 25, hWnd, (HMENU)ID_NAME3, g_hInst, NULL);
		//성별 라디오버튼 생성
		hEmpMale = CreateWindow(TEXT("button"), TEXT("Male"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP, 150, 255, 70, 25, hWnd, (HMENU)ID_MALE, g_hInst, NULL);
		hEmpFemale = CreateWindow(TEXT("button"), TEXT("Female"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 225, 255, 70, 25, hWnd, (HMENU)ID_FEMALE, g_hInst, NULL);
		CheckRadioButton(hWnd, ID_MALE, ID_FEMALE, ID_MALE);
		//생년월일 날짜컨트롤 생성
		hEmpBirth = CreateWindow(DATETIMEPICK_CLASS, NULL, WS_BORDER | WS_CHILD | WS_VISIBLE | DTS_SHORTDATEFORMAT, 150, 290, 153, 25, hWnd, (HMENU)ID_BIRTH, g_hInst, NULL);
		//주소 에디트컨트롤 생성
		hEmpAddress = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 150, 325, 150, 25, hWnd, (HMENU)ID_ADDRESS, g_hInst, NULL);
		//이메일 에디트컨트롤 생성
		hEmpEmail = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 150, 360, 150, 25, hWnd, (HMENU)ID_EMAIL, g_hInst, NULL);
		//연락처 에디트컨트롤 생성
		hEmpPhone1 = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 150, 395, 150, 25, hWnd, (HMENU)ID_PHONE1, g_hInst, NULL);
		hEmpPhone2 = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 150, 430, 150, 25, hWnd, (HMENU)ID_PHONE2, g_hInst, NULL);
		//신장 에디트컨트롤 생성
		hEmpHeight = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 150, 465, 150, 25, hWnd, (HMENU)ID_HEIGHT, g_hInst, NULL);
		//체중 에디트컨트롤 생성
		hEmpWeight = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 150, 500, 150, 25, hWnd, (HMENU)ID_WEIGHT, g_hInst, NULL);
		//결혼관계 라디오버튼 생성
		hEmpSingle = CreateWindow(TEXT("button"), TEXT("Single"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP, 150, 535, 70, 30, hWnd, (HMENU)ID_SINGLE, g_hInst, NULL);
		hEmpMarriage = CreateWindow(TEXT("button"), TEXT("Marriage"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 220, 535, 80, 30, hWnd, (HMENU)ID_MARRIAGE, g_hInst, NULL);
		CheckRadioButton(hWnd, ID_SINGLE, ID_MARRIAGE, ID_SINGLE);
		//종교 콤보박스 생성
		hEmpRelligion = CreateWindow(TEXT("combobox"), NULL, WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST, 150, 580, 153, 200, hWnd, (HMENU)ID_RELLIGION, g_hInst, NULL);
		for (i = 0; i < totR; i++) {
			SendMessage(hEmpRelligion, CB_ADDSTRING, 0, (LPARAM)religion[i].name);
		}
		//시력 에디트컨트롤 생성
		hEmpLefteye = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 150, 615, 150, 25, hWnd, (HMENU)ID_LEFTEYE, g_hInst, NULL);
		hEmpRighteye = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 150, 650, 150, 25, hWnd, (HMENU)ID_RIGHTEYE, g_hInst, NULL);
		//퇴직처리 버튼생성
		CreateWindow(TEXT("button"), TEXT("퇴직처리"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 100, 685, 130, 30, hWnd, (HMENU)ID_RETIRE, g_hInst, NULL);

		//삽입버튼생성
		CreateWindow(TEXT("button"), TEXT("삽입"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 50, 720, 70, 25, hWnd, (HMENU)IDC_INSERT, g_hInst, NULL);
		//수정버튼생성
		CreateWindow(TEXT("button"), TEXT("수정"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 130, 720, 70, 25, hWnd, (HMENU)IDC_MODIFY, g_hInst, NULL);
		//삭제버튼생성
		CreateWindow(TEXT("button"), TEXT("삭제"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 210, 720, 70, 25, hWnd, (HMENU)IDC_DELETE, g_hInst, NULL);

		return 0;
	case WM_COMMAND:
	

		switch (LOWORD(wParam)) {
		case IDC_INSERT:	//삽입 버튼
			GetWindowText(hEmpBuseo, tempEmp.empBuseo, lstrlen(tempEmp.empBuseo));				//부서
			GetWindowText(hEmpPoscode, tempEmp.empPosCode, lstrlen(tempEmp.empPosCode));		//직책
			if (SendMessage(hEmpIndate, DTM_GETSYSTEMTIME, 0, (LPARAM)&st) == GDT_VALID) {
				tempEmp.empStartYear = st;														//입사일
			}
			else {
				MessageBox(hWnd, TEXT("입사일이 선택되지 않았습니다"), TEXT("입사일 선택 오류"), MB_OK);
				break;
			}
			GetWindowText(hEmpName1, tempEmp.pInfo.pName[0], lstrlen(tempEmp.pInfo.pName[0]));	//이름
			GetWindowText(hEmpName2, tempEmp.pInfo.pName[1], lstrlen(tempEmp.pInfo.pName[1]));	//영문이름
			GetWindowText(hEmpName3, tempEmp.pInfo.pName[2], lstrlen(tempEmp.pInfo.pName[2]));	//한자이름
			if (SendMessage(hWnd, BST_CHECKED, ID_MALE, lParam)) {
				tempEmp.pInfo.pSex = TRUE;														//남성
			}
			else {
				tempEmp.pInfo.pSex = FALSE;														//여성
			}
			if (SendMessage(hEmpBirth, DTM_GETSYSTEMTIME, 0, (LPARAM)&st) == GDT_VALID) {
				tempEmp.pInfo.pBirth = st;														//생일
			}
			else {
				MessageBox(hWnd, TEXT("생일이 선택되지 않았습니다"), TEXT("생일 선택 오류"), MB_OK);
				break;
			}
			GetWindowText(hEmpAddress, tempEmp.pInfo.pAddress, lstrlen(tempEmp.pInfo.pAddress));	//주소
			GetWindowText(hEmpEmail, tempEmp.pInfo.pEmail, lstrlen(tempEmp.pInfo.pEmail));		//전자우편
			GetWindowText(hEmpPhone1, tempEmp.pInfo.pPhone[0], lstrlen(tempEmp.pInfo.pPhone[0]));//연락처1
			GetWindowText(hEmpPhone2, tempEmp.pInfo.pPhone[1], lstrlen(tempEmp.pInfo.pPhone[1]));//연락처2
			GetWindowText(hEmpHeight, tempEmp.pInfo.pPhysical[0], lstrlen(tempEmp.pInfo.pPhysical[0]));//신장
			GetWindowText(hEmpWeight, tempEmp.pInfo.pPhysical[1], lstrlen(tempEmp.pInfo.pPhysical[1]));//체중
			if (SendMessage(hWnd, BST_CHECKED, ID_MARRIAGE, lParam)) {
				tempEmp.pInfo.pSex = TRUE;														//기혼
			}
			else {
				tempEmp.pInfo.pSex = FALSE;														//미혼
			}
			GetWindowText(hEmpRelligion, tempEmp.pInfo.pReligion, lstrlen(tempEmp.pInfo.pReligion));//종교
			GetWindowText(hEmpLefteye, tempEmp.pInfo.pPhysical[2], lstrlen(tempEmp.pInfo.pPhysical[2]));//시력(좌)
			GetWindowText(hEmpRighteye, tempEmp.pInfo.pPhysical[3], lstrlen(tempEmp.pInfo.pPhysical[3]));//시력(우)

			if (lstrlen(tempEmp.empBuseo) && lstrlen(tempEmp.empPosCode) && lstrlen(tempEmp.pInfo.pName[0])
				&& lstrlen(tempEmp.pInfo.pName[1]) && lstrlen(tempEmp.pInfo.pName[2]) && lstrlen(tempEmp.pInfo.pAddress)
				&& lstrlen(tempEmp.pInfo.pEmail) && lstrlen(tempEmp.pInfo.pPhone[0]) && lstrlen(tempEmp.pInfo.pPhone[1])
				&& lstrlen(tempEmp.pInfo.pPhysical[0]) && lstrlen(tempEmp.pInfo.pPhysical[1]) && lstrlen(tempEmp.pInfo.pReligion)
				&& lstrlen(tempEmp.pInfo.pPhysical[2]) && lstrlen(tempEmp.pInfo.pPhysical[3])) {
				MessageBox(hWnd, TEXT("길이가 0인 값은 추가할 수 없습니다."), TEXT("입력값 오류"), MB_OK);
			}
			break;
		case IDC_MODIFY:	//수정 버튼

			break;
		case IDC_DELETE:	//삭제 버튼

			break;
		case ID_RETIRE:		//퇴직처리 버튼

			break;
		}
		return 0;
	case WM_NOTIFY:
		LPNMHDR hdr;
		LPNMLISTVIEW nlv;
		hdr = (LPNMHDR)lParam;
		nlv = (LPNMLISTVIEW)lParam;
		TCHAR str[255],tstr[255];

		//부서리스트뷰에서 선택된 항목 컨트롤들로 뿌리기
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
		hFont = CreateFont(18, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("맑은 고딕"));
		OldFont = (HFONT)SelectObject(hdc, hFont);
		SetBkMode(hdc, TRANSPARENT);
		TextOut(hdc, 65, 13, TEXT("사원번호"), lstrlen(TEXT("사원번호")));
		TextOut(hdc, 65, 48, TEXT("부서"), lstrlen(TEXT("부서")));
		TextOut(hdc, 65, 83, TEXT("직책"), lstrlen(TEXT("직책")));
		TextOut(hdc, 65, 118, TEXT("입사일"), lstrlen(TEXT("입사일")));
		TextOut(hdc, 65, 153, TEXT("이름"), lstrlen(TEXT("이름")));
		TextOut(hdc, 65, 188, TEXT("영문이름"), lstrlen(TEXT("영문이름")));
		TextOut(hdc, 65, 223, TEXT("한문이름"), lstrlen(TEXT("한문이름")));
		TextOut(hdc, 65, 258, TEXT("성별"), lstrlen(TEXT("성별")));
		TextOut(hdc, 65, 293, TEXT("생년월일"), lstrlen(TEXT("생년월일")));
		TextOut(hdc, 65, 328, TEXT("주소"), lstrlen(TEXT("주소")));
		TextOut(hdc, 65, 363, TEXT("전자우편"), lstrlen(TEXT("전자우편")));
		TextOut(hdc, 65, 398, TEXT("연락처1"), lstrlen(TEXT("연락처1")));
		TextOut(hdc, 65, 433, TEXT("연락처2"), lstrlen(TEXT("연락처2")));
		TextOut(hdc, 65, 470, TEXT("신장"), lstrlen(TEXT("신장")));
		TextOut(hdc, 65, 505, TEXT("체중"), lstrlen(TEXT("체중")));
		TextOut(hdc, 65, 545, TEXT("결혼관계"), lstrlen(TEXT("결혼관계")));
		TextOut(hdc, 65, 585, TEXT("종교"), lstrlen(TEXT("종교")));
		TextOut(hdc, 65, 620, TEXT("시력(좌)"), lstrlen(TEXT("시력(좌)")));
		TextOut(hdc, 65, 655, TEXT("시력(우)"), lstrlen(TEXT("시력(우)")));
		DeleteObject(hFont);
		EndPaint(hWnd, &ps);
		return 0;
	}
	return (DefMDIChildProc(hWnd, iMessage, wParam, lParam));
}
