#pragma once
#include "../D2DEngine/WinGameApp.h"

class DemoObjectCullingApp :
    public WinGameApp
{
public:
	DemoObjectCullingApp();
	virtual ~DemoObjectCullingApp();
	void Initialize() override;
};
