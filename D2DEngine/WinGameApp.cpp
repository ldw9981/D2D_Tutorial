#include "pch.h"
#include "WinGameApp.h"

void WinGameApp::Initialize()
{
	// 공통으로 사용하는 윈도우 설정,생성부분을 작성한다.

	// Direct2D초기화를 작성한다.
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
			ID2D1HwndRenderTarget* pRenderTarget = m_Renderer.GetRenderTarget();
			pRenderTarget->BeginDraw();
			pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::CadetBlue));
			Render(pRenderTarget);
			pRenderTarget->EndDraw();
		}
	}
}

void WinGameApp::Uninitialize()
{
	// Direct2D 해제를 호출한다.
}


void WinGameApp::Render(ID2D1HwndRenderTarget* pRenderTarget)
{

}

