#include "pch.h"
#include "Scene.h"
#include "D2DRenderer.h"

Scene::Scene()
{
	m_RelativeTransform = m_WorldTransform = D2D1::Matrix3x2F::Identity();
}

Scene::~Scene()
{

}

void Scene::UpdateTrasnform()
{
	m_RelativeTransform = D2D1::Matrix3x2F::Scale(D2D1::SizeF(m_RelativeScale.x, m_RelativeScale.y)) *
		D2D1::Matrix3x2F::Rotation(m_RelativeRotation) *
		D2D1::Matrix3x2F::Translation(m_RelativeLocation.x, m_RelativeLocation.y);

	if (m_pParentScene != nullptr)
		m_WorldTransform = m_RelativeTransform * m_pParentScene->m_WorldTransform;
	else
		m_WorldTransform = m_RelativeTransform;
}

void Scene::Update(float deltaTime)
{
	UpdateTrasnform();
}


void Scene::Render(ID2D1RenderTarget* pRenderTarget)
{
#if _DEBUG	
	pRenderTarget->SetTransform(m_WorldTransform);
	pRenderTarget->DrawRectangle(D2D1::RectF(-2, -2, 2, 2), D2DRenderer::Instance->m_pBrushRed);	
#endif // _DEBUG
}
