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

	std::vector<Component*> m_OwnedComponents;	// ������ ������Ʈ��
	Scene* m_pRootScene = nullptr;				// ������Ʈ �߿� ����� ��Ʈ���� ����
	World* m_pOwnerWorld = nullptr;					// �� ���� ������Ʈ�� ���� ����
	AABB m_BoundBox;								// �ٿ�� �ڽ�

	void Update(float deltaTime);
	void Render(ID2D1RenderTarget* pRenderTarget);
	void SetRootScene(Scene* pRootComponent) { m_pRootScene = pRootComponent; }	
	const AABB& GetBoundBox() const { return m_BoundBox; }

	// ������Ʈ �� ��Ʋ�� �Լ��� �����մϴ�.
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

