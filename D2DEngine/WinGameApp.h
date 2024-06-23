#pragma once
#include "D2DRenderer.h"

class ResourceManager;
class D2DRenderer;
class WinGameApp
{
public:
	// 자식 클래스가 재정의 가능하도록 virtual keyword 를 붙인다.
	WinGameApp();
	virtual ~WinGameApp();

	virtual void Initialize();
	virtual void Run();
	virtual void Uninitialize();

	virtual void Update(float fTimeElapsed) {};
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget);

	D2DRenderer* m_pRenderer = nullptr;
	ResourceManager* m_pResourceManager = nullptr;
	HWND m_hWnd;
};

