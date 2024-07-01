#include "framework.h"
#include "DemoObjectCullingApp.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/World.h"
#include "../D2DEngine/Character.h"
DemoObjectCullingApp::DemoObjectCullingApp()
{

}

DemoObjectCullingApp::~DemoObjectCullingApp()
{

}

void DemoObjectCullingApp::Initialize()
{
	m_pWorld->CreateGameObject<Character>();

}
