#include "Emp.h"

extern HINSTANCE g_hInst;
extern int totB;			//부서갯수
extern int totP;			//직위갯수
extern int totR;			//종교갯수
extern BASE* buseo;			//부서
extern BASE* position;		//직위
extern BASE* religion;		//종교

HWND hEMPList, hEmpNo, hEmpBuseo, hEmpPoscode, hEmpIndate, hEmpName, hEmpMale, hEmpFemale, hEmpBirth, hEmpAddress,
hEmpEmail, hEmpPhone, hEmpHeight, hEmpWeight, hEmpLefteye, hEmpRighteye, hEmpSingle, hEmpMarriage, hEmpRelligion;	//컨트롤 핸들
enum {
	ID_EMPLIST = 1, ID_EMPNO, ID_BUSEO, ID_POSCODE, ID_INDATE, ID_NAME, ID_MALE, ID_FEMALE, ID_BIRTH, ID_ADDRESS, ID_EMAIL,
	ID_PHONE, ID_HEIGHT, ID_WEIGHT, ID_LEFTEYE, ID_RIGHTEYE, ID_SINGLE, ID_MARRIAGE, ID_RELLIGION, IDB_RETIRE
};

//사원관리 프로시져
LRESULT CALLBACK InitEMPMDIProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	LVCOLUMN COL;
	HDC hdc;
	PAINTSTRUCT ps;
	INITCOMMONCONTROLSEX icex;

	switch (iMessage) {
	case WM_CREATE:
		InitCommonControlsEx(&icex);

		//리스트뷰 생성
		hEMPList = CreateWindow(WC_LISTVIEW, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_SHOWSELALWAYS, 350, 10, 1130, 700, hWnd, (HMENU)ID_EMPLIST, g_hInst, NULL);
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
		COL.cx = 50;
		COL.pszText = (LPWSTR)TEXT("성별");
		COL.iSubItem = 5;
		ListView_InsertColumn(hEMPList, 5, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 80;
		COL.pszText = (LPWSTR)TEXT("생년월일");
		COL.iSubItem = 6;
		ListView_InsertColumn(hEMPList, 6, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 100;
		COL.pszText = (LPWSTR)TEXT("주소");
		COL.iSubItem = 7;
		ListView_InsertColumn(hEMPList, 7, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 100;
		COL.pszText = (LPWSTR)TEXT("전자우편");
		COL.iSubItem = 8;
		ListView_InsertColumn(hEMPList, 8, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 100;
		COL.pszText = (LPWSTR)TEXT("연락처");
		COL.iSubItem = 9;
		ListView_InsertColumn(hEMPList, 9, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 40;
		COL.pszText = (LPWSTR)TEXT("신장");
		COL.iSubItem = 10;
		ListView_InsertColumn(hEMPList, 10, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 40;
		COL.pszText = (LPWSTR)TEXT("체중");
		COL.iSubItem = 11;
		ListView_InsertColumn(hEMPList, 11, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 60;
		COL.pszText = (LPWSTR)TEXT("시력(좌)");
		COL.iSubItem = 12;
		ListView_InsertColumn(hEMPList, 12, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 60;
		COL.pszText = (LPWSTR)TEXT("시력(우)");
		COL.iSubItem = 13;
		ListView_InsertColumn(hEMPList, 13, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 60;
		COL.pszText = (LPWSTR)TEXT("결혼관계");
		COL.iSubItem = 11;
		ListView_InsertColumn(hEMPList, 11, &COL);

		COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		COL.fmt = LVCFMT_LEFT;
		COL.cx = 50;
		COL.pszText = (LPWSTR)TEXT("종교");
		COL.iSubItem = 12;
		ListView_InsertColumn(hEMPList, 12, &COL);

		//리스트뷰에 부서 채우기

		//사원번호 에디트컨트롤 생성
		hEmpNo = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 150, 33, 150, 25, hWnd, (HMENU)ID_EMPNO, g_hInst, NULL);
		//부서 콤보박스 생성
		hEmpBuseo = CreateWindow(TEXT("combobox"), NULL, WS_CHILD | WS_VISIBLE | CBS_DROPDOWN, 150, 70, 153, 200, hWnd, (HMENU)ID_BUSEO, g_hInst, NULL);
		//직책 콤보박스 생성
		hEmpPoscode = CreateWindow(TEXT("combobox"), NULL, WS_CHILD | WS_VISIBLE | CBS_DROPDOWN, 150, 110, 153, 200, hWnd, (HMENU)ID_POSCODE, g_hInst, NULL);
		//입사일 날짜컨트롤 생성
		hEmpIndate = CreateWindow(DATETIMEPICK_CLASS, NULL, WS_BORDER | WS_CHILD | WS_VISIBLE | DTS_SHORTDATEFORMAT, 150, 150, 153, 25, hWnd, (HMENU)ID_INDATE, g_hInst, NULL);
		//이름 에디트컨트롤 생성
		hEmpName = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 150, 190, 150, 25, hWnd, (HMENU)ID_NAME, g_hInst, NULL);
		//성별 라디오버튼 생성
		hEmpMale = CreateWindow(TEXT("button"), TEXT("Male"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP, 150, 230, 70, 25, hWnd, (HMENU)ID_MALE, g_hInst, NULL);
		hEmpFemale = CreateWindow(TEXT("button"), TEXT("Female"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 225, 230, 70, 25, hWnd, (HMENU)ID_FEMALE, g_hInst, NULL);
		CheckRadioButton(hWnd, ID_MALE, ID_FEMALE, ID_MALE);
		//생년월일 날짜컨트롤 생성
		hEmpBirth = CreateWindow(DATETIMEPICK_CLASS, NULL, WS_BORDER | WS_CHILD | WS_VISIBLE | DTS_SHORTDATEFORMAT, 150, 270, 153, 25, hWnd, (HMENU)ID_BIRTH, g_hInst, NULL);
		//주소 에디트컨트롤 생성
		hEmpAddress = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 150, 310, 150, 25, hWnd, (HMENU)ID_ADDRESS, g_hInst, NULL);
		//이메일 에디트컨트롤 생성
		hEmpEmail = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 150, 350, 150, 25, hWnd, (HMENU)ID_EMAIL, g_hInst, NULL);
		//연락처 에디트컨트롤 생성
		hEmpPhone = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 150, 390, 150, 25, hWnd, (HMENU)ID_PHONE, g_hInst, NULL);
		//신장 에디트컨트롤 생성
		hEmpHeight = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 150, 430, 150, 25, hWnd, (HMENU)ID_HEIGHT, g_hInst, NULL);
		//체중 에디트컨트롤 생성
		hEmpWeight = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 150, 470, 150, 25, hWnd, (HMENU)ID_WEIGHT, g_hInst, NULL);
		//결혼관계 라디오버튼 생성
		hEmpSingle = CreateWindow(TEXT("button"), TEXT("Single"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP, 150, 510, 70, 30, hWnd, (HMENU)ID_SINGLE, g_hInst, NULL);
		hEmpMarriage = CreateWindow(TEXT("button"), TEXT("Marriage"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 225, 510, 70, 30, hWnd, (HMENU)ID_MARRIAGE, g_hInst, NULL);
		CheckRadioButton(hWnd, ID_SINGLE, ID_MARRIAGE, ID_SINGLE);
		//종교 콤보박스 생성
		hEmpRelligion = CreateWindow(TEXT("combobox"), NULL, WS_CHILD | WS_VISIBLE | CBS_DROPDOWN, 150, 550, 153, 200, hWnd, (HMENU)ID_RELLIGION, g_hInst, NULL);
		//시력 에디트컨트롤 생성
		hEmpLefteye = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 150, 590, 150, 25, hWnd, (HMENU)ID_LEFTEYE, g_hInst, NULL);
		hEmpRighteye = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 150, 630, 150, 25, hWnd, (HMENU)ID_RIGHTEYE, g_hInst, NULL);
		//퇴직처리 버튼생성
		CreateWindow(TEXT("button"), TEXT("퇴직처리"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 100, 670, 130, 30, hWnd, (HMENU)IDB_RETIRE, g_hInst, NULL);

		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 50, 35, TEXT("사원번호"), lstrlen(TEXT("사원번호")));
		TextOut(hdc, 50, 75, TEXT("부서"), lstrlen(TEXT("부서")));
		TextOut(hdc, 50, 115, TEXT("직책"), lstrlen(TEXT("직책")));
		TextOut(hdc, 50, 155, TEXT("입사일"), lstrlen(TEXT("입사일")));
		TextOut(hdc, 50, 195, TEXT("이름"), lstrlen(TEXT("이름")));
		TextOut(hdc, 50, 235, TEXT("성별"), lstrlen(TEXT("성별")));
		TextOut(hdc, 50, 275, TEXT("생년월일"), lstrlen(TEXT("생년월일")));
		TextOut(hdc, 50, 315, TEXT("주소"), lstrlen(TEXT("주소")));
		TextOut(hdc, 50, 355, TEXT("전자우편"), lstrlen(TEXT("전자우편")));
		TextOut(hdc, 50, 395, TEXT("연락처"), lstrlen(TEXT("연락처")));
		TextOut(hdc, 50, 435, TEXT("신장"), lstrlen(TEXT("신장")));
		TextOut(hdc, 50, 475, TEXT("체중"), lstrlen(TEXT("체중")));
		TextOut(hdc, 50, 515, TEXT("결혼관계"), lstrlen(TEXT("결혼관계")));
		TextOut(hdc, 50, 555, TEXT("종교"), lstrlen(TEXT("종교")));
		TextOut(hdc, 50, 595, TEXT("시력(좌)"), lstrlen(TEXT("시력(좌)")));
		TextOut(hdc, 50, 635, TEXT("시력(우)"), lstrlen(TEXT("시력(우)")));
		EndPaint(hWnd, &ps);
		return 0;
	}
	return (DefMDIChildProc(hWnd, iMessage, wParam, lParam));
}
