#include "pch.h"
#include "Movement.h"
#include "Scene.h"
#include "Helper.h"
#include "MathHelper.h"

// 가속도 개념없이 일정한 속도로 이동한다.
void Movement::Update(float DeltaTime)
{
	assert(m_pRootSceneComponent != nullptr);
	// 현재 위치를 가져온다.
	MathHelper::Vector2F Location = m_pRootSceneComponent->GetRelativeLocation();
	m_Velocity = m_Direction * m_Speed;

	// 새로운 위치를 계산한다.
	Location += m_Velocity * DeltaTime;

	//새로 계산된 위치를 적용한다.
	m_pRootSceneComponent->SetRelativeLocation(Location);
}

void Movement::SetDirection(const MathHelper::Vector2F& Direction)
{
	m_Direction = Direction;
	m_Direction.Normalize();
}


