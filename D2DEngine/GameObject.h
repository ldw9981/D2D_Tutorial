#pragma once
#include "AABB.h"

class Component;
class Scene;
class World;
class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	std::vector<Component*> m_OwnedComponents;	// 소유한 컴포넌트들
	Scene* m_pRootScene = nullptr;				// 컴포넌트 중에 어느게 루트인지 설정
	World* m_pOwnerWorld = nullptr;					// 이 게임 오브젝트가 속한 월드
	AABB m_BoundBox;								// 바운딩 박스

	void Update(float deltaTime);
	void Render(ID2D1RenderTarget* pRenderTarget);
	void SetRootScene(Scene* pRootComponent) { m_pRootScene = pRootComponent; }	
	const AABB& GetBoundBox() const { return m_BoundBox; }

	// 컴포넌트 를 템틀릿 함수로 생성합니다.
	template<typename T>
	T* CreateComponent()
	{
		bool bIsBase = std::is_base_of<Component, T>::value;
		assert(bIsBase == true);
		T* pComponent = new T();
		pComponent->SetOwner(this);
		m_OwnedComponents.push_back(pComponent);
		return pComponent;
	}
};

