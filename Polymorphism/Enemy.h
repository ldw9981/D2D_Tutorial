#pragma once
#include "Character.h"
class Enemy :
    public TestCharacter
{
public:
	Enemy();
	~Enemy();

	// 부모의 Attack() 가상함수를 재정의 한다.
	// override 키워드를 사용하면 부모의 가상함수를 재정의 했음을 명시적으로 표시할 수 있다.
	// 부모의 함수가 virtual 로 선언되어 있지 않으면 컴파일러가 오류를 발생시킨다.
	// 자식의 함수에서는 virtual 키워드를 생략 가능하다.
	void Attack() override;
};

