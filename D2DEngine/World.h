#pragma once
#include "GameObject.h"

class World
{
public:
	World();
	virtual ~World();
		
	std::list<GameObject*> m_GameObjects;
public:	
	void Update();
	void Render(ID2D1RenderTarget* pRenderTarget);
	void Clear();

	// ���ø� �Լ��� GameObject�� �����Ѵ�.
	template<typename T>
	T* CreateGameObject()
	{
		bool bIsBase = std::is_base_of<GameObject, T>::value;
		assert(bIsBase == true);	// GameObject�� ��ӹ��� Ŭ������ ������ �� �ִ�.
		T* newObject = new T();
		newObject->SetOwner(this);
		m_GameObjects.push_back(newObject);
		return newObject;
	}
};

