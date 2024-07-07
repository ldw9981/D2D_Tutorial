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

	// �浹�ڽ��� ���߿� ����Ѵٸ� �ڽ��� ����ٴϰ� �Ѵ�.
	// m_pCollisionBox = CreateComponent<CollisionBox>();
	//m_pCollisionBox->SetParentScene(m_pAnimationScene);	
}

Character::~Character()
{

}
