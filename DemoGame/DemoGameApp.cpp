#include "framework.h"
#include "DemoGameApp.h"


void DemoGameApp::Initialize()
{
	// �����Ǹ� ������ �θ� Ŭ������ Initialize()�� ȣ���Ѵ�.
	__super::Initialize();	 // ������ ���� , Direct2D �ʱ�ȭ

	// ���Ŀ� ������ �ۼ��Ѵ�. �� ���� ���ҽ� �ε�,
}

void DemoGameApp::Update(float fTimeElapsed)
{
	__super::Update(fTimeElapsed);

	// ���Ŀ� ������ �ۼ��Ѵ�. �� ���� ���� ó��
	
}

void DemoGameApp::Render(ID2D1RenderTarget* pRenderTarget)
{
	pRenderTarget->BeginDraw();
	pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::CadetBlue));
	pRenderTarget->EndDraw();
}
