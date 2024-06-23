#include "pch.h"
#include "WinGameApp.h"
#include "D2DRenderer.h"
#include "ResourceManager.h"

WinGameApp::WinGameApp()
{
	m_pRenderer = new D2DRenderer;
	m_pResourceManager = new ResourceManager;
}

WinGameApp::~WinGameApp()
{
	if (m_pResourceManager)
	{
		delete m_pResourceManager;
		m_pResourceManager = nullptr;
	}

	if (m_pRenderer)
	{
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}
}

void WinGameApp::Initialize()
{
	// 공통으로 사용하는 윈도우 설정,생성부분을 작성한다.

	// Direct2D초기화를 작성한다.
	m_pRenderer->Initialize();
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


void WinGameApp::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	pRenderTarget->BeginDraw();
	pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::CadetBlue));
	pRenderTarget->EndDraw();
}

