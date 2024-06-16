#include "DemoGameApp.h"
#include "../D2DEngine/D2DRenderer.h"

void DemoGameApp::Initialize()
{
	// 재정의를 하지만 부모 클래스의 Initialize()는 호출한다.
	__super::Initialize();	 // 윈도우 생성 , Direct2D 초기화

	// 이후에 할일을 작성한다. 예 게임 리소스 로딩,
}

void DemoGameApp::Update(float fTimeElapsed)
{
	__super::Update(fTimeElapsed);

	// 이후에 할일을 작성한다. 예 게임 로직 처리
	
}

void DemoGameApp::Render()
{
	
}
