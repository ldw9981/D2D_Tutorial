#include "framework.h"
#include "DemoSolarSystemApp.h"
#include "../D2DEngine/BitmapScene.h"


DemoSolarSystemApp::DemoSolarSystemApp()
{

}

DemoSolarSystemApp::~DemoSolarSystemApp()
{

}

void DemoSolarSystemApp::Initialize()
{
	__super::Initialize();	 // ������ ���� , Direct2D �ʱ�ȭ
	// �¾�, ����,��	�̹��� �ε�

	// �¾�,����,�� �θ� �ڽ� ���� ���� 
}

void DemoSolarSystemApp::Update(float fTimeElapsed)
{
	__super::Update(fTimeElapsed);

	// BitmapScene World Transform ������Ʈ
}

void DemoSolarSystemApp::Render(ID2D1RenderTarget* pRenderTarget)
{
	// ���Ŀ� ������ �ۼ��Ѵ�. �� ���� ������
	pRenderTarget->BeginDraw();
	pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::CadetBlue));
	m_Sun.Render(pRenderTarget);
	pRenderTarget->EndDraw();
}
