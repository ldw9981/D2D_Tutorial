#include "pch.h"
#include "Character.h"
#include "AnimationScene.h"
#include "Helper.h"

Character::Character()
{
	m_pMovement = CreateComponent<Movement>();
	m_pAnimationScene = CreateComponent<AnimationScene>();
	SetRootScene(m_pAnimationScene);
	m_pMovement->SetRootSceneComponent(m_pAnimationScene);

	// 충돌박스를 나중에 사용한다면 박스가 따라다니게 한다.
	// m_pCollisionBox = CreateComponent<CollisionBox>();
	//m_pCollisionBox->SetParentScene(m_pAnimationScene);	
}

Character::~Character()
{

}
