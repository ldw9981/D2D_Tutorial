#include "pch.h"
#include "D2DRenderer.h"
#include "BitmapScene.h"
#include "Helper.h"

#pragma comment(lib, "d2d1.lib")
#pragma	comment(lib, "dwrite.lib")
#pragma	comment(lib, "windowscodecs.lib")
#pragma	comment(lib, "dxgi.lib")


D2DRenderer::D2DRenderer()
{
	Instance = this;
}

D2DRenderer::~D2DRenderer()
{

}

D2D1_MATRIX_3X2_F D2DRenderer::m_CameraTransform = D2D1::Matrix3x2F::Identity();

D2DRenderer* D2DRenderer::Instance = nullptr;

void D2DRenderer::Initialize(HWND hWnd)
{
	m_hWnd = hWnd;
	HRESULT hr = S_OK;
	// COM 사용 시작
	hr = CoInitialize(NULL);
	if (SUCCEEDED(hr))
	{
		/*	장치에 바인딩되지 않은 리소스를 만듭니다.수명은 앱이 지속되는 동안 효과적으로 연장됩니다.
			이러한 리소스에는 Direct2D 및 DirectWrite 팩터리와
			DirectWrite 텍스트 형식 개체(특정 글꼴 특성을 식별하는 데 사용됨)가 포함됩니다.
		*/
		hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pD2DFactory);
	}
	if (SUCCEEDED(hr))
	{
		/*
		Direct3D 장치에 바인딩된 리소스를 만듭니다.
		Direct3D 장치가 손실된 경우(예: 디스플레이 변경, 원격, 비디오 카드 제거 등)
		리소스를 다시 생성해야 하는 경우를 대비하여 모두 여기에 중앙 집중화되어 있습니다.
		*/
		// Create a Direct2D render target.
		hr = m_pD2DFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(m_hWnd, m_ClientSize),
			&m_pRenderTarget);
	}

	if (SUCCEEDED(hr))
	{
		hr = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &m_pBrushRed);
	}

	if (SUCCEEDED(hr))
	{
		// Create WIC factory
		hr = CoCreateInstance(
			CLSID_WICImagingFactory,
			NULL,
			CLSCTX_INPROC_SERVER,
			IID_PPV_ARGS(&m_pWICFactory)
		);
	}

	if (SUCCEEDED(hr))
	{
		// DirectWrite 팩터리를 만듭니다.
		hr = DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(m_pDWriteFactory),
			reinterpret_cast<IUnknown**>(&m_pDWriteFactory));
	}
	if (SUCCEEDED(hr))
	{
		// DirectWrite 텍스트 형식 개체를 만듭니다.
		hr = m_pDWriteFactory->CreateTextFormat(
			L"", // FontName    제어판-모든제어판-항목-글꼴-클릭 으로 글꼴이름 확인가능
			NULL,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			15.0f,   // Font Size
			L"", //locale
			&m_pDWriteTextFormat
		);
	}

	// VRAM 정보얻기 위한 개체 생성
	if (SUCCEEDED(hr))
	{
		// Create DXGI factory
		hr = CreateDXGIFactory1(__uuidof(IDXGIFactory4), (void**)&m_pDXGIFactory);
	}
	if (SUCCEEDED(hr))
	{
		m_pDXGIFactory->EnumAdapters(0, reinterpret_cast<IDXGIAdapter**>(&m_pDXGIAdapter));
	}
}

void D2DRenderer::Uninitialize()
{
	SAFE_RELEASE(m_pBrushRed);
	SAFE_RELEASE(m_pRenderTarget);
	SAFE_RELEASE(m_pD2DFactory);
	SAFE_RELEASE(m_pWICFactory);
	SAFE_RELEASE(m_pDWriteFactory);
	SAFE_RELEASE(m_pDWriteTextFormat);
	SAFE_RELEASE(m_pDXGIFactory);
	SAFE_RELEASE(m_pDXGIAdapter);
	CoUninitialize();
}

size_t D2DRenderer::GetUsedVRAM()
{
	DXGI_QUERY_VIDEO_MEMORY_INFO videoMemoryInfo;
	m_pDXGIAdapter->QueryVideoMemoryInfo(0, DXGI_MEMORY_SEGMENT_GROUP_LOCAL, &videoMemoryInfo);
	return videoMemoryInfo.CurrentUsage / 1024 / 1024;
}

