#pragma once
class Character
{
public:
	Character();
	virtual ~Character();

	int m_HP=100;	

	void Jump();
	void Damage(int _Damage);
	virtual void Attack();
};

