#pragma once
#include "D2DRenderer.h"

class WinGameApp
{
public:
	// 자식 클래스가 재정의 가능하도록 virtual keyword 를 붙인다.
	virtual void Initialize();
	virtual void Run();
	virtual void Uninitialize();

	virtual void Update(float fTimeElapsed)=0;
	virtual void Render()=0;

	D2DRenderer m_Renderer;
};

