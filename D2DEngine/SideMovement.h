#pragma once
#include "Movement.h"
class SideMovement :
    public Movement
{
	SideMovement();
	virtual ~SideMovement();
	static float m_Gravity;		// �߷� ���ӵ�	
protected:
	bool  m_IsJumping = false;				// ����������
	float m_GravityScaled = 0.0f;			// �����ϵ� �߷�
	float m_JumpSpeed = 500.0f;				// ������ �ӷ�
	float m_GravityScale = 100.0f;			// 9.8�� �״�� ����  1�ʿ� 9.8 �ȼ��� �����
	float m_SpeedY = 0.0f;		            // Y�� �ӷ� 
	float m_MaxSpeedY = 600.0f;				// �߷��� ���� �ӵ�
public:
	virtual void Update(float DeltaTime) override;
	virtual void SetDirection(const MathHelper::Vector2F& Direction);
	void SetGravityScale(float val) { m_GravityScale = val; }
	void ResetGravity() { m_GravityScaled = m_Gravity * m_GravityScale; }
	void Jump();
	void EndJump();
};

