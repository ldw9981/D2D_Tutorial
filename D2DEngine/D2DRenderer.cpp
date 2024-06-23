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

D2D1_MATRIX_3X2_F D2DRenderer::m_CameraTransform = D2D1::Matrix3x2F::Identity();

void D2DRenderer::Initialize()
{

}

void D2DRenderer::Uninitialize()
{

}


