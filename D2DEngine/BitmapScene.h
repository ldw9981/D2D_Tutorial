#pragma once
#include "Scene.h"
#include "Component.h"

class D2DRenderer;
class BitmapScene :
	public Scene, public Component
{
public:
	BitmapScene();
	virtual ~BitmapScene();

	void LoadD2DBitmap(const std::wstring strFilePath);

	std::wstring m_strBitmapFilePath;
	ID2D1Bitmap* m_pBitmap = nullptr;	
	

	virtual void Update(float fTimeElapsed);
	virtual void Render(ID2D1RenderTarget* pRenderTarget);
};




