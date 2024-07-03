#pragma once

/*
	���� ������Ʈ�� ����� ������Ʈ ������ �и��ϱ� ���� �߻� Ŭ����
	���ӿ�����Ʈ�� ������Ʈ�� �������� �̷������.
	������Ʈ�� ������ GameObject�� CreateComponent<T> �� ���� �̷������.
*/
class GameObject;
class Component
{
public:
	Component();
	virtual ~Component();

	GameObject* m_pOwner = nullptr;

public:

	GameObject* GetOwner() { return m_pOwner; }
	void SetOwner(GameObject* pOwner) { m_pOwner = pOwner; }

	virtual void Update(float deltaTime);
	virtual void Render(ID2D1RenderTarget* pRenderTarget);
};

