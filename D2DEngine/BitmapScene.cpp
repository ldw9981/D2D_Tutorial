#include "pch.h"
#include "BitmapScene.h"



BitmapScene::BitmapScene()
{

}

BitmapScene::~BitmapScene()
{
	if (m_pBitmap)
	{
		m_pBitmap->Release();
		m_pBitmap = nullptr;
	}
}
bool BitmapScene::Load(const std::wstring& strFileName)
{
	return true;
}

void BitmapScene::Update(float fTimeElapsed)
{
	UpdateTrasnform();
}

