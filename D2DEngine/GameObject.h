#pragma once
class GameObject
{
public:
	GameObject();
	virtual ~GameObject();



	void Update(float deltaTime);
	void Render(ID2D1RenderTarget* pRenderTarget);
};

