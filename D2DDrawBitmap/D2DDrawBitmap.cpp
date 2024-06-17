#include <windows.h>
#include <d2d1.h>
#include <wincodec.h>
#include <comdef.h>
#include <d2d1_1helper.h>

#pragma comment(lib,"d2d1.lib")
#pragma comment(lib,"windowscodecs.lib")

// 전역 변수:
HINSTANCE g_hInst;                                // 현재 인스턴스입니다.
HWND g_hWnd;

//  D2D 개체 인터페이스 포인터 변수
ID2D1Factory* g_pD2DFactory;
ID2D1HwndRenderTarget* g_pRenderTarget;

// D2D1비트맵 생성을 위한 이미지 처리 인터페이스
IWICImagingFactory* g_pWICFactory;

ID2D1Bitmap* g_pD2DBitmap=nullptr;


LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);


HRESULT CreateD2DBitmapFromFile(const WCHAR* szFilePath,ID2D1Bitmap** ppID2D1Bitmap)
{
    HRESULT hr;
	// Create a decoder
	IWICBitmapDecoder* pDecoder = NULL;
    IWICFormatConverter* pConverter = NULL;

	hr = g_pWICFactory->CreateDecoderFromFilename(
        szFilePath,                      // Image to be decoded
		NULL,                            // Do not prefer a particular vendor
		GENERIC_READ,                    // Desired read access to the file
		WICDecodeMetadataCacheOnDemand,  // Cache metadata when needed
		&pDecoder                        // Pointer to the decoder
	);

	// Retrieve the first frame of the image from the decoder
	IWICBitmapFrameDecode* pFrame = NULL;
	if (SUCCEEDED(hr))
	{
		hr = pDecoder->GetFrame(0, &pFrame);
	}

	//Step 3: Format convert the frame to 32bppPBGRA
	if (SUCCEEDED(hr))
	{
		hr = g_pWICFactory->CreateFormatConverter(&pConverter);
	}

	if (SUCCEEDED(hr))
	{
		hr = pConverter->Initialize(
			pFrame,                          // Input bitmap to convert
			GUID_WICPixelFormat32bppPBGRA,   // Destination pixel format
			WICBitmapDitherTypeNone,         // Specified dither pattern
			NULL,                            // Specify a particular palette 
			0.f,                             // Alpha threshold
			WICBitmapPaletteTypeCustom       // Palette translation type
		);
	}
    	
	if (SUCCEEDED(hr))
	{		
		hr = g_pRenderTarget->CreateBitmapFromWicBitmap(pConverter, NULL, ppID2D1Bitmap);
	}


    // 파일을 사용할때마다 다시 만든다.
    if(pConverter)  
        pConverter->Release();
       
    if (pDecoder)
        pDecoder->Release();
	
    if (pFrame)
        pFrame->Release();

    return hr;
}

BOOL InitDirect2D()
{
	WCHAR buffer[MAX_PATH];
	// Get the current working directory
	DWORD result = GetCurrentDirectory(MAX_PATH, buffer);
    OutputDebugString(buffer);

    HRESULT hr = S_OK;
    // COM 사용 시작
    hr = CoInitialize(NULL);
    if (SUCCEEDED(hr))
    {
        /*	장치에 바인딩되지 않은 리소스를 만듭니다.수명은 앱이 지속되는 동안 효과적으로 연장됩니다.
            이러한 리소스에는 Direct2D 및 DirectWrite 팩터리와
            DirectWrite 텍스트 형식 개체(특정 글꼴 특성을 식별하는 데 사용됨)가 포함됩니다.
        */
        hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &g_pD2DFactory); 
    }
	if (SUCCEEDED(hr))
	{
        /*
        Direct3D 장치에 바인딩된 리소스를 만듭니다.
        Direct3D 장치가 손실된 경우(예: 디스플레이 변경, 원격, 비디오 카드 제거 등)
        리소스를 다시 생성해야 하는 경우를 대비하여 모두 여기에 중앙 집중화되어 있습니다.
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
    }

	if (SUCCEEDED(hr))
	{
		// Create WIC factory
		hr = CoCreateInstance(
			CLSID_WICImagingFactory,
			NULL,
			CLSCTX_INPROC_SERVER,
			IID_PPV_ARGS(&g_pWICFactory)
		);
    }

	if (SUCCEEDED(hr))
	{
        hr = CreateD2DBitmapFromFile(L"../Resource/atk_1.png", &g_pD2DBitmap);
    }

	if (FAILED(hr))
	{
		_com_error err(hr);
		::MessageBox(g_hWnd, err.ErrorMessage(), L"FAILED", MB_OK);
		return false;
	}
    return true;
}

void UninitDirect2D()
{    
    if (g_pD2DBitmap)   g_pD2DBitmap->Release();
    if (g_pWICFactory) g_pWICFactory->Release();
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
			g_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity()); // 변환 초기화

			//1. 0,0 위치에 비트맵 전체영역 그린다. (변환은 초기화)
			g_pRenderTarget->DrawBitmap(g_pD2DBitmap);						

			//2. DestPos(화면 위치) 설정과 SrcPos(비트맵 위치)로 그리기
			D2D1_VECTOR_2F DestPos{0,0} , SrcPos{0,0}; // 화면 위치, 비트맵 위치
			D2D1_SIZE_F size{0,0};	//	그릴 크기
			D2D1_RECT_F DestRect{ 0,0,0,0 }, SrcRect{ 0,0,0,0 }; // 화면 영역, 비트맵 영역
			D2D1_MATRIX_3X2_F transform;	// 변환 행렬

			size = g_pD2DBitmap->GetSize();		
			DestPos = { 300,300 };
			DestRect = {DestPos.x , DestPos.y, DestPos.x + size.width -1 ,DestPos.y + size.height -1};			
			g_pRenderTarget->DrawBitmap(g_pD2DBitmap, DestRect);            
            
            
			//3. DestRect(그릴 영역) 설정과 SrcRect(비트맵 일부 영역)로 그리기
			size = { 100,100 };
			DestPos = { 600,600 };
			DestRect = { DestPos.x , DestPos.y, DestPos.x + size.width - 1 ,DestPos.y + size.height - 1 };

			SrcPos = { 0,0};	
			SrcRect = { SrcPos.x,SrcPos.y, SrcPos.x + size.width - 1 ,SrcPos.y + size.height - 1 };						
			g_pRenderTarget->DrawBitmap(g_pD2DBitmap, DestRect,1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,&SrcRect);
			
			
			//4. 변환을 사용한 반전으로 DestRect(그릴 영역) 설정과 SrcRect(비트맵 일부 영역)로 그리기
			DestPos = { 800,600 };
			DestRect = { DestPos.x , DestPos.y, DestPos.x + size.width - 1 ,DestPos.y + size.height - 1 };			
            
			transform = D2D1::Matrix3x2F::Scale(-1.0f,1.0f,  // x축 반전
				D2D1::Point2F(DestPos.x, DestPos.y));        // 기준점
			g_pRenderTarget->SetTransform(transform);
			g_pRenderTarget->DrawBitmap(g_pD2DBitmap, DestRect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, &SrcRect);

			//5. 복합변환을 사용한 반전으로 DestRect(그릴 영역) 설정과 SrcRect(비트맵 일부 영역)로 그리기
			DestPos = { 0,0 };   // 그릴 위치는 0,0으로 하고 이동변환을 사용한다.
			DestRect = { DestPos.x , DestPos.y, DestPos.x + size.width - 1 ,DestPos.y + size.height - 1 };

			transform = D2D1::Matrix3x2F::Scale(1.0f, 1.0f,D2D1::Point2F(0.0f,0.0f)) *
				D2D1::Matrix3x2F::Rotation(90.0f, D2D1::Point2F(0.0f, 0.0f)) * // 90도 회전
				D2D1::Matrix3x2F::Translation(900.0f, 900.0f);  // 이동
			// 기준점
			g_pRenderTarget->SetTransform(transform);
			g_pRenderTarget->DrawBitmap(g_pD2DBitmap, DestRect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, &SrcRect);


			g_pRenderTarget->EndDraw();
		}
	}


    UninitDirect2D();

    return (int) msg.wParam;
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
