#include <windows.h>
#include <d2d1.h>
#include <wincodec.h>
#include <comdef.h>
#include <d2d1_1helper.h>
#include <string>
#include <dwrite.h>

#pragma comment(lib,"d2d1.lib")
#pragma comment(lib,"dwrite.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"windowscodecs.lib")


using namespace D2D1;
using namespace std;

// 전역 변수:
HINSTANCE g_hInst;                                // 현재 인스턴스입니다.
HWND g_hWnd;

// 윌드행렬(복합변환)을 위한 행렬 
D2D_MATRIX_3X2_F g_matWorldScale = Matrix3x2F::Identity(); 
D2D_MATRIX_3X2_F g_matWorldRotation = Matrix3x2F::Identity(); 
D2D_MATRIX_3X2_F g_matWorldTranslation = Matrix3x2F::Identity(); 

D2D_MATRIX_3X2_F g_matWorld = Matrix3x2F::Identity(); // 월드 좌표계 변환을 위한 행렬

D2D_SIZE_U g_ScreenSize;
D2D_VECTOR_2F g_posCamera = { 0.0f, 0.0f };
D2D_MATRIX_3X2_F g_matCameraInv = Matrix3x2F::Identity(); // 카메라 좌표계 변환을 위한 행렬

//  D2D 개체 인터페이스 포인터 변수
ID2D1Factory* g_pD2DFactory;
ID2D1HwndRenderTarget* g_pRenderTarget;

// D2D1비트맵 생성을 위한 이미지 처리 인터페이스
IWICImagingFactory* g_pWICFactory;
ID2D1Bitmap* g_pD2DBitmap = nullptr;

// DWrite
IDWriteFactory* g_pDWriteFactory;
IDWriteTextFormat* g_pDWriteTextFormat;

ID2D1SolidColorBrush* g_pBrush; // 브러시 개체 인터페이스 포인터 변수

LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);


HRESULT CreateD2DBitmapFromFile(const WCHAR* szFilePath, ID2D1Bitmap** ppID2D1Bitmap)
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
    if (pConverter)
        pConverter->Release();

    if (pDecoder)
        pDecoder->Release();

    if (pFrame)
        pFrame->Release();

    return hr;
}

void PrintMatrix(const wchar_t* str,D2D_MATRIX_3X2_F& mat,float left,float top)
{
	WCHAR buffer[256]={0};
	swprintf_s(buffer, L"%.2f, %.2f\n%.2f, %.2f\n%.2f, %.2f\n",
		mat._11, mat._12, mat._21, mat._22, mat._31, mat._32);
	OutputDebugString(buffer);

    Matrix3x2F matRender = Matrix3x2F::Identity();    
    g_pRenderTarget->SetTransform(matRender);

    g_pBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Blue));
    g_pRenderTarget->FillRectangle(RectF(left, top, left + 100, top+150), g_pBrush);

    g_pBrush->SetColor(D2D1::ColorF(D2D1::ColorF::White));
    g_pRenderTarget->DrawTextW(str,(UINT32)wcslen(str), g_pDWriteTextFormat, RectF(left, top, left+300,top+300), g_pBrush);
    g_pRenderTarget->DrawTextW(buffer, (UINT32)wcslen(buffer),g_pDWriteTextFormat,RectF(left,top+60, left + 300, top+60 + 300),g_pBrush);

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

        g_ScreenSize = D2D1::SizeU(
            rc.right - rc.left,
            rc.bottom - rc.top);

        // Create a Direct2D render target.
        hr = g_pD2DFactory->CreateHwndRenderTarget(
            D2D1::RenderTargetProperties(),
            D2D1::HwndRenderTargetProperties(g_hWnd, g_ScreenSize),
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
		hr = CreateD2DBitmapFromFile(L"../Resource/tree.jpg", &g_pD2DBitmap);
	}

    if (SUCCEEDED(hr))
    {
		// DirectWrite 팩터리를 만듭니다.
		hr = DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(g_pDWriteFactory),
			reinterpret_cast<IUnknown**>(&g_pDWriteFactory));
    }

	if (SUCCEEDED(hr))
	{
	    // DirectWrite 텍스트 형식 개체를 만듭니다.
	    hr = g_pDWriteFactory->CreateTextFormat(
		    L"", // FontName    제어판-모든제어판-항목-글꼴-클릭 으로 글꼴이름 확인가능
		    NULL,
		    DWRITE_FONT_WEIGHT_NORMAL,
		    DWRITE_FONT_STYLE_NORMAL,
		    DWRITE_FONT_STRETCH_NORMAL,
		    15.0f,   // Font Size
		    L"", //locale
		    &g_pDWriteTextFormat
	    );
    }
    
  
    if (SUCCEEDED(hr))
    {
        hr = g_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::GreenYellow), &g_pBrush);
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
                   
            g_matWorldScale = Matrix3x2F::Scale(1.0f, 1.0f); 
            g_matWorldRotation = Matrix3x2F::Rotation(0.0f); // 회전각도
            g_matWorldTranslation = Matrix3x2F::Translation(0.0f, 0.0f); // 이동
			g_matWorld = g_matWorldScale * g_matWorldRotation * g_matWorldTranslation;

            // 카메라의 월드위치로 역행렬을 계산하여 카메라 좌표계로 변환하는 행렬
            g_matCameraInv = Matrix3x2F::Translation(g_posCamera.x, g_posCamera.y);
            D2D1InvertMatrix(&g_matCameraInv);

            D2D_MATRIX_3X2_F Transform = g_matWorld * g_matCameraInv;

            g_pRenderTarget->BeginDraw();
            g_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));            
            g_pRenderTarget->SetTransform(Transform);            
            g_pRenderTarget->DrawBitmap(g_pD2DBitmap);


            PrintMatrix(L"Transform", Transform, 0, 100);
           
            PrintMatrix(L"g_matWorld", g_matWorld, 300, 100);
            PrintMatrix(L"g_matCameraInv", g_matCameraInv, 400, 100);
           

            g_pRenderTarget->EndDraw();
        }
    }


    UninitDirect2D();

    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    std::wstring str;
    switch (message)
    {
	case WM_KEYDOWN:
		if (wParam == VK_LEFT)
		{
		    g_posCamera.x -= 10;
		}
		else if (wParam == VK_RIGHT)
		{
            g_posCamera.x += 10;
		}
		else if (wParam == VK_UP)
		{
            g_posCamera.y -= 10;
		}
		else if (wParam == VK_DOWN)
		{
            g_posCamera.y += 10;
		}	
             
     
        str = L"Camera X : " + to_wstring(g_posCamera.x) + L" Camera Y : " + std::to_wstring(g_posCamera.y);
        SetWindowText(hWnd, str.c_str());
		break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

