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
	// ������ ���� �������� �������ڵ� ����
	// �̺�Ʈ �޼��� ����
	// �̺�Ʈ�� �߻����� �� �ٸ� ������ �޾ƿ��� ������
	HDC hdc;			// Device Context Handle â ���� ������ �������� ����
	PAINTSTRUCT ps;		// �׸��� ����
	static bool i = false;

	// Ű �Է� ó��
	switch (iMessage)	// iMessage: �Էµ� Ű
	{
		// �� ���⿡ ���ǹ��� �־� �۾�

	case WM_RBUTTONDOWN:	// ���콺 ��Ŭ�� ���� ��
		hdc = GetDC(hWnd);
		// �޼��� ���
		TextOut(hdc, 300, 200, TEXT("!!! :)"), 6);
		ReleaseDC(hWnd, hdc);
		return 0;

	case WM_LBUTTONDOWN:	// ���콺 ��Ŭ�� ���� ��
		i = !i;
		InvalidateRect(hWnd, NULL, TRUE);
		// -> â�� �ִ� �۾����� ����� case WM_PAINT: ���ǹ����� �̵�
		hdc = GetDC(hWnd);	// ���� Ȱ��ȭ �Ǿ��ִ� â�� DC�� ������
		// �޼��� ����ϱ�
		TextOut(hdc, 200, 200, TEXT("Beautiful Seoul"), 15);
		ReleaseDC(hWnd, hdc);	// GetDC()�� ��ȯ�ϱ� ���ؼ��� ReleaseDC() ���
		// BeginPaint(), EndPaint()�� ���� ����
		// ��κ� GetDC(), ReleaseDC()�� ���
		return 0;

		// -> WM_LBUTTONDOWN, WM_RBUTTONDOWN�� â ũ�Ⱑ �����Ǹ� �����

	case WM_PAINT:
		// â�� �����ϸ� ������ ���� ���� ����Ǵ� ���� ��ɾ�
		// â�� ũ�Ⱑ ����Ǿ ���� ����Ǿ ���
		hdc = BeginPaint(hWnd, &ps);							// �׸��� ����
		// BeginPaint(), EndPaint() ���̿� �׷��� �� �� �۾�
		TextOut(hdc, 100, 100, TEXT("Beautiful Korea"), 15);	// �۾� ��ġ ���� �� ����ϱ�. 15�� ���� ��
		if (i)	// ���콺 ��Ŭ�� �� â ũ������ ���� ��, ���� ��µǰ�
		{
			TextOut(hdc, 200, 200, TEXT("Beautiful Seoul"), 15);
		}
		EndPaint(hWnd, &ps);									// BeginPaint()�� ������ EndPaint()�� �־�� ��
		return 0;

	case WM_DESTROY:			// ������ ���� �� (â�� ���� �� �߻��ϴ� �޼���)
		PostQuitMessage(0);		// �޼��� ť�� ���� �޼��� ����
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}