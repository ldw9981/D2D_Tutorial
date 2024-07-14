#pragma once
#include "RenderScene.h"
#include <set>

enum class ColliderType
{
	None,
	Circle,
	Box
};

enum class CollisionType
{
	NoCollision,
	Block,
	Overlap
};

class ColliderComponent;
class IColliderNotify
{
public:
	virtual void OnBlock(ColliderComponent* pOwnedComponent, ColliderComponent* pOtherComponent) = 0;
	virtual void OnBeginOverlap(ColliderComponent* pOwnedComponent, ColliderComponent* pOtherComponent) = 0;
	virtual void OnEndOverlap(ColliderComponent* pOwnedComponent, ColliderComponent* pOtherComponent) = 0;
};

/*
	�߻� Ŭ����
*/
class Collider :
	public RenderScene
{
public:
	Collider() = default;
	virtual ~Collider() = default;

protected:
	CollisionType m_CollisionType;		// �ø��� Ÿ�� (���ø���,��, ������)
	ColliderType m_ColliderType;		// �ö��̴� Ÿ�� (��,�ڽ�)
	D2D1_COLOR_F m_Color;				// �׸���� ����

	std::set<Collider*> m_CollideStateCurr;    // ���� �浹 ����
	std::set<Collider*> m_CollideStatePrev;	// ���� �浹 ����
public:

	CollisionType GetCollisionType() { return m_CollisionType; }
	void SetCollisionType(CollisionType Type) { m_CollisionType = Type; }
	ColliderType GetColliderType() { return m_ColliderType; }

	D2D1_COLOR_F GetColor() const { return m_Color; }
	void SetColor(D2D1_COLOR_F val) { m_Color = val; }
	void ClearAndBackupCollideState();

	bool IsEmptyCollideStateCurr() { return m_CollideStateCurr.empty(); }

	void InsertCollideState(Collider* pColliderComponent) { m_CollideStateCurr.insert(pColliderComponent); }
	void ProcessOverlap();
	void ProcessBlock(Collider* pOtherComponent);


	// Circle,Box ���� ���� �����ؾ��Ѵ�.
	virtual bool IsCollide(Collider* pOtherComponent) = 0;
};


