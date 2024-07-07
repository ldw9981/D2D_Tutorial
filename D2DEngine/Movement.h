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
	float			m_Speed = 0.0f;		// 1초당 이동할 속력
	MathHelper::Vector2F	m_Direction {0.0f,0.0f };	// 방향 유닛벡터
	MathHelper::Vector2F	m_Velocity;		// 속도 벡터
	Scene* m_pSceneComponent; // 위치를 변경할 컴포넌트
public:
	virtual void Update(float deltaTime);

	void SetSceneComponent(Scene* val) { m_pSceneComponent = val; }
	void SetSpeed(float speed) { m_Speed = speed; };
	float GetSpeed() { return m_Speed; };
	virtual void SetDirection(const MathHelper::Vector2F& Direction);
	const MathHelper::Vector2F& GetDirection() { return m_Direction; };
};

