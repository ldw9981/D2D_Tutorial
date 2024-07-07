#include "pch.h"
#include "Movement.h"
#include "Scene.h"
#include "Helper.h"
#include "MathHelper.h"

// ���ӵ� ������� ������ �ӵ��� �̵��Ѵ�.
void Movement::Update(float DeltaTime)
{
	assert(m_pSceneComponent != nullptr);
	// ���� ��ġ�� �����´�.
	MathHelper::Vector2F Location = m_pSceneComponent->GetRelativeLocation();
	m_Velocity = m_Direction * m_Speed;

	// ���ο� ��ġ�� ����Ѵ�.
	Location += m_Velocity * DeltaTime;

	//���� ���� ��ġ�� �����Ѵ�.
	m_pSceneComponent->SetRelativeLocation(Location);
}

void Movement::SetDirection(const MathHelper::Vector2F& Direction)
{
	m_Direction = Direction;
	m_Direction.Normalize();
}

