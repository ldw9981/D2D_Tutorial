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

