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
	// ������ ���� ��������. D2D1Bitmap �����Ͽ� �������̽� ������ �޴´�.
	// ���⼭�� �����Ѵ�.
	
	// ������ ��Ʈ���� �ʿ� �����Ѵ�.

//	m_BitmapMap.insert(make_pair(strFilePath, *bitmap));
	m_BitmapMap[strFilePath] = *bitmap; 
	return true;
}

void ResourceManager::ReleaseD2DBitmap(std::wstring strFilePath)
{
	// �ʿ� �ش� Ű�� �����ϸ� ��Ʈ���� �����Ѵ�.
	std::map<std::wstring, ID2D1Bitmap*>::iterator iter = m_BitmapMap.find(strFilePath);
	assert(iter != m_BitmapMap.end()); // �����̳ʿ� ������ Create/Release ¦�� �߸��ƴ�.

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
	if (m_AnimationAssetMap.find(strFilePath) != m_AnimationAssetMap.end())
	{
		*asset = m_AnimationAssetMap[strFilePath];
		(*asset)->AddRef();
		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	// ������ ���� ��������. AnimationAsset �����Ͽ� �������̽� ������ �޴´�.
	// ���⼭�� �����Ѵ�.

	AnimationAsset* pTemp = new AnimationAsset;	
	// ������ �ִϸ��̼� ���¿� �ִϸ��̼� �����͸� �ε��Ѵ�.
	if (pTemp->LoadAnimation(strFilePath) == false)
	{
		delete pTemp;	
		return false;
	}
	else
	{
		*asset = pTemp;
	}
	// ������ �ִϸ��̼� ������ �ʿ� �����Ѵ�.
	//	m_AnimationAssetMap.insert(make_pair(strFilePath, *asset));
	m_AnimationAssetMap[strFilePath] = *asset;
	return true;
}

void ResourceManager::ReleaseAnimationAsset(std::wstring strFilePath)
{
	// �ʿ� �ش� Ű�� �����ϸ� �ִϸ��̼� ������ �����Ѵ�.
	std::map<std::wstring, AnimationAsset*>::iterator iter = m_AnimationAssetMap.find(strFilePath);
	assert(iter != m_AnimationAssetMap.end()); // �����̳ʿ� ������ Create/Release ¦�� �߸��ƴ�.

	if (iter != m_AnimationAssetMap.end())
	{
		AnimationAsset* asset = m_AnimationAssetMap[strFilePath];
		if (asset->Release() == 0)
		{
			m_AnimationAssetMap.erase(iter);
		}
	}
}
