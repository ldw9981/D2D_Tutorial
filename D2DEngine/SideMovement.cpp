#include "pch.h"
#include "SideMovement.h"
#include "Movement.h"
#include "Helper.h"
#include "MathHelper.h"
#include "Scene.h"

float SideMovement::m_Gravity = 9.8f;

SideMovement::SideMovement()
{	
	m_GravityScaled = m_Gravity * m_GravityScale;	// 중력 가속도  
}

SideMovement::~SideMovement()
{
}

void SideMovement::Update(float DeltaTime)
{
	assert(m_pRootScene != nullptr);
	MathHelper::Vector2F Location = m_pRootScene->GetRelativeLocation();

	// x축 이동 속도
	m_Velocity.x = (MathHelper::Vector2F(m_Direction) * m_Speed).x;

	// y축 이동 속도
	m_SpeedY += m_GravityScaled * DeltaTime;	// y축 이동속도는 중력에 의해 점점 빨라진다.
	m_SpeedY = min(m_MaxSpeedY, m_SpeedY);				// 종단속도로 제한한다.
	m_Velocity.y = (MathHelper::Vector2F(0.0f, -1.0f) * m_SpeedY).y;

	//D2DHelper::Log(L"%f,%f\n", m_Velocity.x, m_Velocity.y);
	Location = Location + m_Velocity * DeltaTime;	// 시간변화 만큼 이동
	Location.y = max(0.0f, Location.y);						// 바닥이 없을때 무한낙하 방지 
	// 외부에서 착지 판단을 해야하는데 일단 0.0f보다 작거나 같으면 착지한 것으로 판단한다.	
	if (Location.y <= 0.0f)
	{
		EndJump();
	}

	//새로 계산된 위치를 적용한다.
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
		m_SpeedY = m_JumpSpeed * -1; // 점프는 중력의 반대
	}
}

void SideMovement::EndJump()
{
	m_IsJumping = false;
	m_SpeedY = 0.0f;
	//m_GravityScaled = 0.0f;	// 중력을 끄는게 맞을까?
}