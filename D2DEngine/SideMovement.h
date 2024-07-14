#pragma once
#include "Movement.h"
class SideMovement :
    public Movement
{
	SideMovement();
	virtual ~SideMovement();
	static float m_Gravity;		// 중력 가속도	
protected:
	bool  m_IsJumping = false;				// 점프중인지
	float m_GravityScaled = 0.0f;			// 스케일된 중력
	float m_JumpSpeed = 500.0f;				// 점프의 속력
	float m_GravityScale = 100.0f;			// 9.8을 그대로 쓰면  1초에 9.8 픽셀이 적용됨
	float m_SpeedY = 0.0f;		            // Y축 속력 
	float m_MaxSpeedY = 600.0f;				// 중력의 종단 속도
public:
	virtual void Update(float DeltaTime) override;
	virtual void SetDirection(const MathHelper::Vector2F& Direction);
	void SetGravityScale(float val) { m_GravityScale = val; }
	void ResetGravity() { m_GravityScaled = m_Gravity * m_GravityScale; }
	void Jump();
	void EndJump();
};

