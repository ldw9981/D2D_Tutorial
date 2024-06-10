// BasicD2D.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include <windows.h>
#include <d2d1.h>

// 코드에서 d2d1.lib 라이브러리를 링크합니다.
// 프로젝트 속성에서 링크하려면 -> 링커 -> 입력 -> 추가 종속성 -> d2d1.lib 추가
#pragma comment(lib, "d2d1.lib")

// 윈도우 관련 변수,함수
HINSTANCE       g_hInst;                                // 현재 인스턴스입니다.
HWND            g_hWnd;

//  D2D 개체 인터페이스 포인터 변수
ID2D1Factory* g_pD2DFactory;

//무언가 그릴수있는 렌더타겟, 장치 의존 리소스
ID2D1HwndRenderTarget* g_pRenderTarget;

// 렌더타겟이 생성하는 리소스 역시 장치의존
ID2D1SolidColorBrush* g_pBlackBrush;
ID2D1SolidColorBrush* g_pGrayBrush;

LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

BOOL InitDirect2D()
{
	HRESULT hr = S_OK;
	// COM 사용 시작
	hr = CoInitialize(NULL);
	if (FAILED(hr))
		return FALSE;

	/*	장치에 바인딩되지 않은 리소스를 만듭니다.수명은 앱이 지속되는 동안 효과적으로 연장됩니다.
		이러한 리소스에는 Direct2D 및 DirectWrite 팩터리와
		DirectWrite 텍스트 형식 개체(특정 글꼴 특성을 식별하는 데 사용됨)가 포함됩니다.
	*/
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &g_pD2DFactory);
	if (FAILED(hr))
		return FALSE;


	/*
		Direct3D 장치에 바인딩된 리소스를 만듭니다.		
	*/
	RECT rc;
	GetClientRect(g_hWnd, &rc);

	D2D1_SIZE_U size = D2D1::SizeU(
		rc.right - rc.left,
		rc.bottom - rc.top);

	// Create a Direct2D render target.
	hr = g_pD2DFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(g_hWnd, size),
		&g_pRenderTarget);

	if (FAILED(hr))
		return FALSE;

	hr = g_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black),&g_pBlackBrush);
	if (FAILED(hr))
		return FALSE;

	hr = g_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Gray), &g_pGrayBrush);
	if (FAILED(hr))
		return FALSE;

	return TRUE;
}

void UninitDirect2D()
{
	if (g_pGrayBrush) g_pGrayBrush->Release();
	if (g_pBlackBrush) g_pBlackBrush->Release();
	if (g_pRenderTarget) g_pRenderTarget->Release();
	if (g_pD2DFactory) g_pD2DFactory->Release();

	// COM 사용 끝
	CoUninitialize();
}




int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// 윈도우 클래스 구조체 초기화
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;	// 윈도우 프로시저 함수
	wc.hInstance = hInstance;   // 인스턴스 핸들
	// NULL을 사용하면 현재 실행 중인 프로그램의 인스턴스 핸들을 사용하게 됩니다.두 번째 인자는 로드할 커서의 ID입니다.
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszClassName = L"BasicWindowClass";

	// 윈도우 클래스 등록
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, L"윈도우 클래스 등록 실패", L"에러", MB_OK | MB_ICONERROR);
		return 1;
	}

	// 원하는 크기가 조정되어 리턴
	SIZE clientSize = { 1920, 1280 };
	RECT clientRect = { 0, 0, clientSize.cx, clientSize.cy };
	AdjustWindowRect(&clientRect, WS_OVERLAPPEDWINDOW, FALSE);

	// 윈도우 생성
	g_hWnd = CreateWindowEx(
		0,
		L"BasicWindowClass",
		L"간단한 윈도우",
		WS_OVERLAPPEDWINDOW,	// OR연산으로 조합된 윈도우창 스타일
		0, 0,	// 시작위치
		clientRect.right - clientRect.left, clientRect.bottom - clientRect.top, // 너비, 높이
		NULL, NULL, hInstance, NULL
	);

	if (!g_hWnd)
	{
		MessageBox(NULL, L"윈도우 생성 실패", L"에러", MB_OK | MB_ICONERROR);
		return 1;
	}

	// 윈도우 표시
	ShowWindow(g_hWnd, nCmdShow);
	UpdateWindow(g_hWnd);

	if (!InitDirect2D())
		return FALSE;

	MSG msg;
	// 기본 메시지 루프입니다:
	while (TRUE)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

			//윈도우 메시지 처리 
			TranslateMessage(&msg); // 키입력관련 메시지 변환  WM_KEYDOWN -> WM_CHAR
			DispatchMessage(&msg);
		}
		else
		{
			g_pRenderTarget->BeginDraw();
			g_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::CadetBlue));

			D2D1_SIZE_F size = g_pRenderTarget->GetSize();
			for (float y=0 ; y< size.height ; y+=10 )
			{
				g_pRenderTarget->DrawLine(
					D2D1::Point2F(0.0f,y),
					D2D1::Point2F(size.width ,y),
					g_pBlackBrush, 0.5f

				);
			}

			g_pRenderTarget->FillRectangle(
				D2D1::RectF(size.width / 2 - 150.0f, size.height / 2 - 150.0f,
					size.width / 2 + 150.0f, size.height / 2 + 150.0f), g_pGrayBrush);
		
			g_pRenderTarget->DrawRectangle(
				D2D1::RectF(size.width/2 - 50.0f , size.height / 2 - 50.0f,
				size.width / 2 + 50.0f, size.height / 2 + 50.0f),g_pBlackBrush	);

			g_pRenderTarget->EndDraw();
			
		}
	}

	UninitDirect2D();
	return (int)msg.wParam;
}


// 윈도우 프로시저 함수 정의
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}
