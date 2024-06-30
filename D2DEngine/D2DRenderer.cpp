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

}

D2DRenderer::~D2DRenderer()
{

}

D2D1_MATRIX_3X2_F D2DRenderer::m_CameraTransform = D2D1::Matrix3x2F::Identity();

void D2DRenderer::Initialize(HWND hWnd)
{
	m_hWnd = hWnd;
	HRESULT hr = S_OK;
	// COM ��� ����
	hr = CoInitialize(NULL);
	if (SUCCEEDED(hr))
	{
		/*	��ġ�� ���ε����� ���� ���ҽ��� ����ϴ�.������ ���� ���ӵǴ� ���� ȿ�������� ����˴ϴ�.
			�̷��� ���ҽ����� Direct2D �� DirectWrite ���͸���
			DirectWrite �ؽ�Ʈ ���� ��ü(Ư�� �۲� Ư���� �ĺ��ϴ� �� ����)�� ���Ե˴ϴ�.
		*/
		hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pD2DFactory);
	}
	if (SUCCEEDED(hr))
	{
		/*
		Direct3D ��ġ�� ���ε��� ���ҽ��� ����ϴ�.
		Direct3D ��ġ�� �սǵ� ���(��: ���÷��� ����, ����, ���� ī�� ���� ��)
		���ҽ��� �ٽ� �����ؾ� �ϴ� ��츦 ����Ͽ� ��� ���⿡ �߾� ����ȭ�Ǿ� �ֽ��ϴ�.
		*/
		// Create a Direct2D render target.
		hr = m_pD2DFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(m_hWnd, m_ClientSize),
			&m_pRenderTarget);
	}

	if (SUCCEEDED(hr))
	{
		hr = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &m_pBrush);
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
		// DirectWrite ���͸��� ����ϴ�.
		hr = DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(m_pDWriteFactory),
			reinterpret_cast<IUnknown**>(&m_pDWriteFactory));
	}
	if (SUCCEEDED(hr))
	{
		// DirectWrite �ؽ�Ʈ ���� ��ü�� ����ϴ�.
		hr = m_pDWriteFactory->CreateTextFormat(
			L"", // FontName    ������-���������-�׸�-�۲�-Ŭ�� ���� �۲��̸� Ȯ�ΰ���
			NULL,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			15.0f,   // Font Size
			L"", //locale
			&m_pDWriteTextFormat
		);
	}

	// VRAM ������� ���� ��ü ����
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
	SAFE_RELEASE(m_pBrush);
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

