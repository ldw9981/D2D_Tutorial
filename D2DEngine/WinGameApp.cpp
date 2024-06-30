#include "pch.h"
#include "WinGameApp.h"
#include "D2DRenderer.h"
#include "ResourceManager.h"
#include "World.h"
#include "Helper.h"

WinGameApp::WinGameApp()
{
	m_pRenderer = new D2DRenderer;
	m_pResourceManager = new ResourceManager;
	m_pWorld = new World; // Default World
}

WinGameApp::~WinGameApp()
{	
	// 메모리 해제
	/*
	if (m_pWorld)
	{
		delete m_pWorld;
		m_pWorld = nullptr;
	}
	*/
	SAFE_DELETE(m_pWorld);
	SAFE_DELETE(m_pResourceManager);	
	SAFE_DELETE(m_pRenderer);
}

void WinGameApp::Initialize()
{
	// 공통으로 사용하는 윈도우 설정,생성부분을 작성한다.

	// Direct2D초기화를 작성한다.
	m_pRenderer->Initialize(m_hWnd);
}

void WinGameApp::Run()
{
	// 공통으로 사용하는 윈도우 게임 루프를 작성한다.
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
			float deltaTime = 0.016f;
			Update(deltaTime);					
			Render(m_pRenderer->GetRenderTarget());
		}
	}
}

void WinGameApp::Uninitialize()
{
	// Direct2D 해제를 호출한다.
	m_pRenderer->Uninitialize();
}


void WinGameApp::Update(float fTimeElapsed)
{
	m_pWorld->Update(fTimeElapsed);
}

void WinGameApp::Render(ID2D1RenderTarget* pRenderTarget)
{
	pRenderTarget->BeginDraw();
	pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::CadetBlue));
	m_pWorld->Render(pRenderTarget);
	pRenderTarget->EndDraw();
}

