#pragma once
#include "D2DRenderer.h"

class ResourceManager;
class D2DRenderer;
class World;
class WinGameApp
{
public:
	// �ڽ� Ŭ������ ������ �����ϵ��� virtual keyword �� ���δ�.
	WinGameApp();
	virtual ~WinGameApp();

	virtual void Initialize();
	virtual void Run();
	virtual void Uninitialize();

	virtual void Update(float fTimeElapsed);
	virtual void Render(ID2D1RenderTarget* pRenderTarget);

	D2DRenderer* m_pRenderer = nullptr;
	ResourceManager* m_pResourceManager = nullptr;
	World* m_pWorld = nullptr;
	HWND m_hWnd;
};

