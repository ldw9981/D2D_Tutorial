#include "Character.h"
#include <iostream>

Character::Character()
{
	std::cout << __FUNCTION__  << std::endl;
}

Character::~Character()
{
	std::cout << __FUNCTION__ << std::endl;
}

void Character::Jump()
{
	std::cout << __FUNCTION__ << std::endl;
}

void Character::Damage(int _Damage)
{
	m_HP -= _Damage;
}

void Character::Attack()
{
	std::cout << __FUNCTION__ << std::endl;
}
