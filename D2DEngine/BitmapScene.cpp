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

	//���ҽ� �Ŵ����� ���Ͽ� ��Ʈ���� �����Ѵ�.
	if (m_pBitmap)
	{
		ResourceManager::pInstance->ReleaseD2DBitmap(m_strBitmapFilePath);
		m_pBitmap = nullptr;
	}
}
void BitmapScene::LoadD2DBitmap(const std::wstring strFilePath)
{
	// ���ҽ� �Ŵ����� ���� ��Ʈ���� �ε��Ѵ�.
	m_strBitmapFilePath = strFilePath;
}

void BitmapScene::Update(float fTimeElapsed)
{
	UpdateTrasnform();
}

void BitmapScene::Render(ID2D1RenderTarget* pRenderTarget)
{
	assert(m_pBitmap != nullptr);
	pRenderTarget->SetTransform(m_WorldTransform);
	pRenderTarget->DrawBitmap(m_pBitmap);
}

