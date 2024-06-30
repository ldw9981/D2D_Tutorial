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
	__super::Initialize();	 // 윈도우 생성 , Direct2D 초기화
	// 태양, 지구,달	이미지 로딩

	// 태양,지구,달 부모 자식 관계 설정 
}

void DemoSolarSystemApp::Update(float fTimeElapsed)
{
	__super::Update(fTimeElapsed);

	// BitmapScene World Transform 업데이트
}

void DemoSolarSystemApp::Render(ID2D1RenderTarget* pRenderTarget)
{
	// 이후에 할일을 작성한다. 예 게임 렌더링
	pRenderTarget->BeginDraw();
	pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::CadetBlue));
	m_Sun.Render(pRenderTarget);
	pRenderTarget->EndDraw();
}
