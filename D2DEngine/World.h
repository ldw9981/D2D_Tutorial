#pragma once
#include "GameObject.h"
#include "AABB.h"

// 게임의 세계를 나타내는 클래스
// GameObect타입으로 생성된 객체들을 관리하여 Update, Render를 호출한다.
class World
{
public:
	World();
	virtual ~World();
	
	std::list<GameObject*> m_GameObjects;
	AABB* m_pCullingBound = nullptr;
	AABB m_CullingBoundDefault;	
public:	
	void Update(float deltaTime);
	void Render(ID2D1RenderTarget* pRenderTarget);
	void Clear();
	void SetCullingBound(AABB* pBound) { m_pCullingBound = pBound; }
	// 템플릿 함수로 GameObject를 생성한다.
	template<typename T>
	T* CreateGameObject()
	{
		bool bIsBase = std::is_base_of<GameObject, T>::value;
		assert(bIsBase == true);	// GameObject를 상속받은 클래스만 생성할 수 있다.
		T* newObject = new T();
		newObject->SetOwner(this);
		m_GameObjects.push_back(newObject);
		return newObject;
	}
};

