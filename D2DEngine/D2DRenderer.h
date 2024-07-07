#pragma once
#include <d2d1.h>

class BitmapScene;
class D2DRenderer
{
public:
	D2DRenderer();
	~D2DRenderer();

	static D2D1_MATRIX_3X2_F m_CameraWorldInverse;		// ī�޶��� ��ǥ��� ��ȯ�ϴ� ī�޶� ������ �����
	static D2DRenderer* Instance;					// �̱��� �ν��Ͻ�

	void Initialize(HWND hWnd);
	void Uninitialize();

	ID2D1Factory* GetFactory() { return m_pD2DFactory; }
	ID2D1HwndRenderTarget* GetRenderTarget() { return m_pRenderTarget; }
	size_t GetUsedVRAM();
public:
	ID2D1Factory* m_pD2DFactory;		// D2D ��ü �������̽� ������ ����
	ID2D1HwndRenderTarget* m_pRenderTarget;
	IWICImagingFactory* m_pWICFactory;	// D2D��Ʈ�� ������ ���� �̹��� ó�� �������̽�
	IDWriteFactory* m_pDWriteFactory;	// TextFormat������ ���� ���丮
	IDWriteTextFormat* m_pDWriteTextFormat; // �⺻ �ؽ�Ʈ ����� ���� Format
	ID2D1SolidColorBrush* m_pBrushRed;	// ����Ÿ���� �����ϴ� ���ҽ� ���� ��ġ����

	IDXGIFactory4* m_pDXGIFactory;		// DXGI���丮
	IDXGIAdapter3* m_pDXGIAdapter;		// ����ī�� ������ ���� ������ �������̽�
	HWND m_hWnd;						// ����Ÿ���� ������ ������ �ڵ�
	D2D_SIZE_U	m_ClientSize;			// ����Ÿ���� ũ��
};




