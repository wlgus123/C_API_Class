#include <windows.h>									// ������ �������

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;										// �ν��Ͻ� �ڵ�
LPCTSTR lpszClass = TEXT("������_25311004");				// ���� ǥ���ٿ� ǥ�õǴ� ����

// ������ ���� �Լ� - �⺻���� â ����
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;											// ������ �ڵ� ����
	MSG Message;										// �޼��� ����ü ���� ����
	WNDCLASS WndClass;									// Windows Class ����ü ���� ����
	g_hInst = hInstance;								// hInstance���� �ܺο����� ����� �� �ֵ��� ���������� ���� ����

	// ������ â ����
	WndClass.cbClsExtra = 0;							// ���� ����. ������ ��� X
	WndClass.cbWndExtra = 0;							// ���� ����
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	// �������� ��� ������ ����
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);		// �������� ���콺������ ����� ����
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);	// �������� Ŀ�� ������ ��� ����
	WndClass.hInstance = hInstance;						// ������ Ŭ������ ����ϴ� ���α׷� ��ȣ
	WndClass.lpfnWndProc = WndProc;						// ������ �޼��� ó�� �Լ� ����
	WndClass.lpszClassName = lpszClass;					// ������ Ŭ������ �̸� ����
	WndClass.lpszMenuName = NULL;						// �޴� ����
	WndClass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;			// �������� ��Ÿ���� ����

	RegisterClass(&WndClass);							// WNDCLASS ����ü�� ������ ����

	hWnd = CreateWindow(lpszClass, lpszClass,			// �����츦 ����
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT
		/* 100, 100, 500, 500 */, NULL, NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);

	// �޼��� ������ ���� (�߿�)
	// �޼����� ���� ������ ó��
	while (GetMessage(&Message, NULL, 0, 0)) 			// Queue�� �ִ� �޼����� �о���δ�
	{
		TranslateMessage(&Message);						// Ű���� �Է� �޼����� �����Ͽ� ���α׷����� ����
		// ����� �� �ֵ���
		DispatchMessage(&Message);						// �޼����� �������� �޼��� ó�� �Լ� WndProc�� ����
	}
	return (int)Message.wParam;							// Ż�� �ڵ�. ���α׷� ����
}

// ������ ���ν��� �Լ�
// �۾��ϰ��� �ϴ� ����(Ű �Է�)�� ó���ϴ� �Լ�
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	static PAINTSTRUCT ps;
	static int clickCnt = 0;
	static int x = 100;
	static int y = 200;
	static const int plusPos = 10;	// �� ��� ������
	static bool isClickL = false;

	// Ű �Է� ó��
	switch (iMessage)	// iMessage: �Էµ� Ű
	{
	case WM_LBUTTONDOWN:	// ���콺 ��Ŭ�� ���� ��
		isClickL = true;	// ��Ŭ�� ���� ������ ����
		++clickCnt;	// Ŭ�� Ƚ�� ����
		InvalidateRect(hWnd, NULL, FALSE);
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// �׸���
		if(isClickL)	// ��Ŭ�� ������ ���
		{
			for(int i = 1; i <= clickCnt; i++)
			{
				Ellipse(hdc, x + (plusPos * i), x + (plusPos * i), y + (plusPos * i), y + (plusPos * i));
			}
		}
		EndPaint(hWnd, &ps);
		return 0;

	case WM_DESTROY:			// ������ ���� �� (â�� ���� �� �߻��ϴ� �޼���)
		PostQuitMessage(0);		// �޼��� ť�� ���� �޼��� ����
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}