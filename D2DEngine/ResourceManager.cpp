#include "pch.h"
#include "ResourceManager.h"
#include "AnimationAsset.h"


ResourceManager::ResourceManager()
{
	ResourceManager::pInstance = this;
}

ResourceManager::~ResourceManager()
{
	assert(m_BitmapMap.empty());
	assert(m_AnimationAssetMap.empty());
}

ResourceManager* ResourceManager::pInstance = nullptr;

bool ResourceManager::CreateD2DBitmapFromFile(std::wstring strFilePath, ID2D1Bitmap** bitmap)
{
	if (m_BitmapMap.find(strFilePath) != m_BitmapMap.end())
	{
		*bitmap = m_BitmapMap[strFilePath];
		(*bitmap)->AddRef();
		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	// 기존과 같은 생성로직. D2D1Bitmap 생성하여 인터페이스 포인터 받는다.
	// 여기서는 생략한다.
	
	// 생성한 비트맵을 맵에 저장한다.
	m_BitmapMap[strFilePath] = *bitmap; 
	return true;
}

void ResourceManager::ReleaseD2DBitmap(std::wstring strFilePath)
{
	// 맵에 해당 키가 존재하면 비트맵을 해제한다.
	std::map<std::wstring, ID2D1Bitmap*>::iterator iter = m_BitmapMap.find(strFilePath);
	assert(iter != m_BitmapMap.end()); // 컨테이너에 없으면 Create/Release 짝이 잘못됐다.

	if (iter != m_BitmapMap.end())
	{
		ID2D1Bitmap* bitmap = m_BitmapMap[strFilePath];
		if (bitmap->Release() == 0)
		{
			m_BitmapMap.erase(iter);
		}		
	}
}

bool ResourceManager::CreateAnimationAsset(std::wstring strFilePath, AnimationAsset** asset)
{
	
}

void ResourceManager::ReleaseAnimationAsset(std::wstring strFilePath)
{

}
