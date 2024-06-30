#include "pch.h"
#include "World.h"
#include "D2DRenderer.h"

World::World()
{
	// ȭ��ũ�� ������ �����ͼ�
	float width = 640;
	float height = 480;
	m_CullingBoundDefault.SetExtent(width/2, height/2);
	m_CullingBoundDefault.SetCenter(0,0);
	SetCullingBound(&m_CullingBoundDefault);	
}

World::~World()
{

}


void World::Update(float deltaTime)
{
	for (auto& obj : m_GameObjects)
	{
		obj->Update(deltaTime);
	}
}

void World::Render(ID2D1RenderTarget* pRenderTarget)
{
	// �̰� �ø� �׽�Ʈ ���� ���� Render �ϴ°�
	for (auto& obj : m_GameObjects)
	{
		obj->Render(pRenderTarget);
	}
}

void World::Clear()
{
	m_GameObjects.clear();
}
