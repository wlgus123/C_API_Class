#include <windows.h>									// 윈도우 헤더파일

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;										// 인스턴스 핸들
LPCTSTR lpszClass = TEXT("김지현_25311004");				// 제목 표시줄에 표시되는 내용

// 윈도우 메인 함수 - 기본적인 창 제작
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;											// 윈도우 핸들 선언
	MSG Message;										// 메세지 구조체 변수 선언
	WNDCLASS WndClass;									// Windows Class 구조체 변수 선언
	g_hInst = hInstance;								// hInstance값을 외부에서도 사용할 수 있도록 전역변수에 값을 저장

	// 윈도우 창 설정
	WndClass.cbClsExtra = 0;							// 예약 영역. 지금은 사용 X
	WndClass.cbWndExtra = 0;							// 예약 영역
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	// 윈도우의 배경 색상을 지정
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);		// 윈도우의 마우스포인터 모양을 지정
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);	// 윈도우의 커서 아이콘 모양 지정
	WndClass.hInstance = hInstance;						// 윈도우 클래스를 등록하는 프로그램 번호
	WndClass.lpfnWndProc = WndProc;						// 윈도우 메세지 처리 함수 지정
	WndClass.lpszClassName = lpszClass;					// 윈도우 클래스의 이름 지정
	WndClass.lpszMenuName = NULL;						// 메뉴 지정
	WndClass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;			// 윈도우의 스타일을 정의

	RegisterClass(&WndClass);							// WNDCLASS 구조체의 번지를 전달

	hWnd = CreateWindow(lpszClass, lpszClass,			// 윈도우를 생성
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT
		/* 100, 100, 500, 500 */, NULL, NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);

	// 메세지 루프를 실행 (중요)
	// 메세지가 없을 때까지 처리
	while (GetMessage(&Message, NULL, 0, 0)) 			// Queue에 있는 메세지를 읽어들인다
	{
		TranslateMessage(&Message);						// 키보드 입력 메세지를 가공하여 프로그램에서 쉽게
		// 사용할 수 있도록
		DispatchMessage(&Message);						// 메세지를 윈도우의 메세지 처리 함수 WndProc로 전달
	}
	return (int)Message.wParam;							// 탈출 코드. 프로그램 종료
}

// 윈도우 프로시저 함수
// 작업하고자 하는 내용(키 입력)을 처리하는 함수
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	// 키 입력 처리
	switch (iMessage)	// iMessage: 입력된 키
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		SetPixel(hdc, 10, 10, RGB(255, 0, 0));

		MoveToEx(hdc, 50, 50, NULL);
		LineTo(hdc, 300, 90);

		Rectangle(hdc, 50, 100, 200, 180);

		RoundRect(hdc, 300, 200, 400, 280, 20, 20);

		Ellipse(hdc, 220, 100, 400, 200);

		EndPaint(hWnd, &ps);
		return 0;

	case WM_DESTROY:			// 윈도우 종료 시 (창을 닫을 때 발생하는 메세지)
		PostQuitMessage(0);		// 메세지 큐에 종료 메세지 전달
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}