#pragma once
#include "BitmapScene.h"
class AnimationScene :
    public BitmapScene
{
public:
	AnimationScene();
	virtual ~AnimationScene();

	void Update(float fTimeElapsed);
	void Render(ID2D1HwndRenderTarget* pRenderTarget);
};

