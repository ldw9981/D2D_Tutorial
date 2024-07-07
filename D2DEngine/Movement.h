#pragma once
#include "Component.h"
#include "MathHelper.h"

class Scene;
class Movement :
    public Component
{
public:
	Movement() = default;
	virtual ~Movement() = default;
protected:
	float			m_Speed = 0.0f;		// 1�ʴ� �̵��� �ӷ�
	MathHelper::Vector2F	m_Direction {0.0f,0.0f };	// ���� ���ֺ���
	MathHelper::Vector2F	m_Velocity;		// �ӵ� ����
	Scene* m_pRootSceneComponent; // ��ġ�� ������ ������Ʈ
public:
	virtual void Update(float deltaTime);

	void SetRootSceneComponent(Scene* val) { m_pRootSceneComponent = val; }
	void SetSpeed(float speed) { m_Speed = speed; };
	float GetSpeed() { return m_Speed; };
	virtual void SetDirection(const MathHelper::Vector2F& Direction);
	const MathHelper::Vector2F& GetDirection() { return m_Direction; };
};

