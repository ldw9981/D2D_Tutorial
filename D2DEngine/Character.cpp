#include "pch.h"
#include "Character.h"
#include "AnimationScene.h"
#include "Helper.h"

Character::Character()
{
	m_pAnimationScene = CreateComponent<AnimationScene>();
	SetRootScene(m_pAnimationScene);

	// �浹�ڽ��� ���߿� ����Ѵٸ� �ڽ��� ����ٴϰ� �Ѵ�.
	//m_pCollisionBox->SetParentScene(m_pAnimationScene);	
}

Character::~Character()
{

}
