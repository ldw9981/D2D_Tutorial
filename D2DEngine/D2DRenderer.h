#pragma once
#include <d2d1.h>

class BitmapScene;
class D2DRenderer
{
public:
	D2DRenderer();
	~D2DRenderer();

	void Initialize();
	void Uninitialize();

	ID2D1Factory* GetFactory() { return m_pFactory; }
	ID2D1HwndRenderTarget* GetRenderTarget() { return m_pRenderTarget; }
public:
	ID2D1Factory* m_pFactory = nullptr;
	ID2D1HwndRenderTarget* m_pRenderTarget = nullptr;
};




