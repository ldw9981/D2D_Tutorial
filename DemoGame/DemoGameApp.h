#pragma once
#include "../D2DEngine/WinGameApp.h"

class DemoGameApp : public WinGameApp
{
public:
	//  virtual 만 사용해도 되지만
	// override를 keyword를 사용하므로써 가상함수 "재정의" 라는것을 확실히한다.
	// 부모 클래스의 함수가 virtual 이 아니면 컴파일 에러.
	virtual void Initialize() override;
};
