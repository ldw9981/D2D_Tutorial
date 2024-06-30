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
	// �޸� ����
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
	// �������� ����ϴ� ������ ����,�����κ��� �ۼ��Ѵ�.

	// Direct2D�ʱ�ȭ�� �ۼ��Ѵ�.
	m_pRenderer->Initialize(m_hWnd);
}

void WinGameApp::Run()
{
	// �������� ����ϴ� ������ ���� ������ �ۼ��Ѵ�.
	MSG msg;
	// �⺻ �޽��� �����Դϴ�:
	while (TRUE)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

			//������ �޽��� ó�� 
			TranslateMessage(&msg); // Ű�Է°��� �޽��� ��ȯ  WM_KEYDOWN -> WM_CHAR
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
	// Direct2D ������ ȣ���Ѵ�.
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

