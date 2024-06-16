#include "pch.h"
#include "D2DRenderer.h"
#include "BitmapScene.h"
#pragma comment(lib, "d2d1.lib")



D2DRenderer::D2DRenderer()
{

}

D2DRenderer::~D2DRenderer()
{

}

void D2DRenderer::Initialize()
{

}

void D2DRenderer::Uninitialize()
{

}

void D2DRenderer::Render(BitmapScene* pBitmap)
{
	m_pRenderTarget->SetTransform(pBitmap->m_WorldTransform);
	m_pRenderTarget->DrawBitmap(pBitmap->m_pBitmap);
}

