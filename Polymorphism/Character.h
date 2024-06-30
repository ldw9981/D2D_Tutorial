#pragma once
class TestCharacter
{
public:
	TestCharacter();
	virtual ~TestCharacter(); // 파괴자에는 왜? virtual을 붙일까??

	int m_HP=100;	

	void Jump();
	virtual void Damage(int _Damage);
	virtual void Attack();
};

