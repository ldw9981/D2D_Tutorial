#include "pch.h"
#include "World.h"

World::World()
{

}

World::~World()
{

}


void World::Render(ID2D1RenderTarget* pRenderTarget)
{
	for (auto& obj : m_GameObjects)
	{
		obj->Render(pRenderTarget);
	}
}

void World::Clear()
{
	m_GameObjects.clear();
}
