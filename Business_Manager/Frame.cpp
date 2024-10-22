#include "Frame.h"
#include "Common.h"

#define IDM_WINDOWCHILD 8000

extern HINSTANCE g_hInst;
extern HWND g_hMDIClient;	//Ŭ���̾�Ʈ ������ �ڵ�
extern int totB;			//�μ�����
extern int totP;			//��������
extern int totR;			//��������
extern BASE* buseo;			//�μ�
extern BASE* position;		//����
extern BASE* religion;		//����
extern EMP* workEmp;		//���
extern EMP* retireEmp;		//�������

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
		//�ʱ⿡ ���,������� 1�� ������� �Ҵ�
		workEmp = (EMP*)malloc(sizeof(EMP));
		retireEmp = (EMP*)malloc(sizeof(EMP));

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
		//�Ҵ�� �μ�,����,����,���,������� free
		free(buseo);
		free(position);
		free(religion);
		free(workEmp);
		free(retireEmp);
		return 0;
	}
	return(DefFrameProc(hWnd, g_hMDIClient, iMessage, wParam, lParam));
}
