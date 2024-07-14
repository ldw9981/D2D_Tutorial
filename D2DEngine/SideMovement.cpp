#include "pch.h"
#include "SideMovement.h"
#include "Movement.h"
#include "Helper.h"
#include "MathHelper.h"
#include "Scene.h"

float SideMovement::m_Gravity = 9.8f;

SideMovement::SideMovement()
{	
	m_GravityScaled = m_Gravity * m_GravityScale;	// �߷� ���ӵ�  
}

SideMovement::~SideMovement()
{
}

void SideMovement::Update(float DeltaTime)
{
	assert(m_pRootScene != nullptr);
	MathHelper::Vector2F Location = m_pRootScene->GetRelativeLocation();

	// x�� �̵� �ӵ�
	m_Velocity.x = (MathHelper::Vector2F(m_Direction) * m_Speed).x;

	// y�� �̵� �ӵ�
	m_SpeedY += m_GravityScaled * DeltaTime;	// y�� �̵��ӵ��� �߷¿� ���� ���� ��������.
	m_SpeedY = min(m_MaxSpeedY, m_SpeedY);				// ���ܼӵ��� �����Ѵ�.
	m_Velocity.y = (MathHelper::Vector2F(0.0f, -1.0f) * m_SpeedY).y;

	//D2DHelper::Log(L"%f,%f\n", m_Velocity.x, m_Velocity.y);
	Location = Location + m_Velocity * DeltaTime;	// �ð���ȭ ��ŭ �̵�
	Location.y = max(0.0f, Location.y);						// �ٴ��� ������ ���ѳ��� ���� 
	// �ܺο��� ���� �Ǵ��� �ؾ��ϴµ� �ϴ� 0.0f���� �۰ų� ������ ������ ������ �Ǵ��Ѵ�.	
	if (Location.y <= 0.0f)
	{
		EndJump();
	}

	//���� ���� ��ġ�� �����Ѵ�.
	m_pRootScene->SetRelativeLocation(Location);
}

void SideMovement::SetDirection(const MathHelper::Vector2F& Direction)
{
	m_Direction.x = Direction.x;
	m_Direction.y = 0;
}

void SideMovement::Jump()
{
	if (m_IsJumping == false)
	{
		m_GravityScaled = SideMovement::m_Gravity * m_GravityScale;
		m_IsJumping = true;
		m_SpeedY = m_JumpSpeed * -1; // ������ �߷��� �ݴ�
	}
}

void SideMovement::EndJump()
{
	m_IsJumping = false;
	m_SpeedY = 0.0f;
	//m_GravityScaled = 0.0f;	// �߷��� ���°� ������?
}