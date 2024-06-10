#pragma once
class WinGameApp
{
public:
	// 자식 클래스가 재정의 가능하도록 virtual keyword 를 붙인다.
	virtual void Initialize();
	virtual void Run();
	virtual void Uninitialize();
};

