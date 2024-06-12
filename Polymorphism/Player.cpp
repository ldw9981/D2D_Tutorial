#include "Player.h"
#include <iostream>

Player::Player()
{
	std::cout << __FUNCTION__ << std::endl;
}

Player::~Player()
{
	std::cout << __FUNCTION__ << std::endl;
}

void Player::Attack()
{
	// 재정의 했지만 부모의 Attack() 함수도 호출하고 싶다면
	__super::Attack();
	std::cout << __FUNCTION__ << std::endl;
}
