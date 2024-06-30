#include "Character.h"
#include <iostream>

TestCharacter::TestCharacter()
{
	std::cout << __FUNCTION__  << std::endl;
}

TestCharacter::~TestCharacter()
{
	std::cout << __FUNCTION__ << std::endl;
}

void TestCharacter::Jump()
{
	std::cout << __FUNCTION__ << std::endl;
}

void TestCharacter::Damage(int _Damage)
{
	m_HP -= _Damage;
}

void TestCharacter::Attack()
{
	std::cout << __FUNCTION__ << std::endl;
}
