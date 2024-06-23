#pragma once
#include "Scene.h"


class D2DRenderer;
class BitmapScene :
	public Scene
{
public:
	BitmapScene();
	virtual ~BitmapScene();

	void LoadD2DBitmap(const std::wstring strFilePath);

	std::wstring m_strBitmapFilePath;
	ID2D1Bitmap* m_pBitmap = nullptr;	
	

	void Update(float fTimeElapsed);
	void Render(ID2D1HwndRenderTarget* pRenderTarget);
};




