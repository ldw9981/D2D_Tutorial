#pragma once
#include "../D2DEngine/WinGameApp.h"
#include "../D2DEngine/BitmapScene.h"

class DemoSolarSystemApp : public WinGameApp
{
public:
	DemoSolarSystemApp();
	~DemoSolarSystemApp();

	virtual void Initialize() override;	
	virtual void Render(ID2D1RenderTarget* pRenderTarget) override;
	virtual void Update(float fTimeElapsed) override;

	BitmapScene m_Sun;
	BitmapScene m_Earth;
	BitmapScene m_Moon;
};

