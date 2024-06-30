#include "pch.h"
#include "World.h"
#include "D2DRenderer.h"

World::World()
{
	// 화면크기 정보를 가져와서
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
	// 이건 컬링 테스트 없이 전부 Render 하는것
	for (auto& obj : m_GameObjects)
	{
		obj->Render(pRenderTarget);
	}
}

void World::Clear()
{
	m_GameObjects.clear();
}
