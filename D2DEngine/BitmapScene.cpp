#include "pch.h"
#include "BitmapScene.h"
#include "ResourceManager.h"


BitmapScene::BitmapScene()
{

}

BitmapScene::~BitmapScene()
{
    /*
	if (m_pBitmap)
	{
		m_pBitmap->Release();
		m_pBitmap = nullptr;
	}
	*/

	//리소스 매니저를 통하여 비트맵을 해제한다.
	if (m_pBitmap)
	{
		ResourceManager::pInstance->ReleaseD2DBitmap(m_strBitmapFilePath);
		m_pBitmap = nullptr;
	}
}
void BitmapScene::LoadD2DBitmap(const std::wstring strFilePath)
{
	// 리소스 매니저를 통해 비트맵을 로드한다.
	m_strBitmapFilePath = strFilePath;
}

void BitmapScene::Update(float fTimeElapsed)
{
	UpdateTrasnform();
}

void BitmapScene::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	assert(m_pBitmap != nullptr);
	pRenderTarget->SetTransform(m_WorldTransform);
	pRenderTarget->DrawBitmap(m_pBitmap);
}

