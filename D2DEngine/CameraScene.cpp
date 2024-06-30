#include "pch.h"
#include "CameraScene.h"

CameraScene::CameraScene()
{
	float width = 640;
	float height = 480;

	m_ViewBoundBox.SetExtent(width / 2, height / 2);
}

CameraScene::~CameraScene()
{

}



void CameraScene::Update(float deltaTime)
{
	Scene::UpdateTrasnform();	
	m_ViewBoundBox.m_Center = GetWorldLocation();
}
