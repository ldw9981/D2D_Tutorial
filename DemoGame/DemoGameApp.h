#pragma once
#include "../D2DEngine/WinGameApp.h"
#include "../D2DEngine/BitmapScene.h"

class DemoGameApp : public WinGameApp
{
public:
	//  virtual �� ����ص� ������
	// override�� keyword�� ����ϹǷν� �����Լ� "������" ��°��� Ȯ�����Ѵ�.
	// �θ� Ŭ������ �Լ��� virtual �� �ƴϸ� ������ ����.
	virtual void Initialize() override;
	virtual void Update(float fTimeElapsed) override;
	virtual void Render(ID2D1RenderTarget* pRenderTarget) override;
	
};
