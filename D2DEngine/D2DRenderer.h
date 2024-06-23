#pragma once


class BitmapScene;
class D2DRenderer
{
public:
	D2DRenderer();
	~D2DRenderer();

	static D2D1_MATRIX_3X2_F m_CameraTransform;		// 카메라의 좌표계로 변환하는 카메라 월드의 역행렬

	void Initialize();
	void Uninitialize();

	ID2D1Factory* GetFactory() { return m_pFactory; }
	ID2D1HwndRenderTarget* GetRenderTarget() { return m_pRenderTarget; }
public:
	ID2D1Factory* m_pFactory = nullptr;
	ID2D1HwndRenderTarget* m_pRenderTarget = nullptr;
};




