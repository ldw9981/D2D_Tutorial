// Polymorphism.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Player.h"
#include "Enemy.h"
#include "Character.h"
#include "TestClass.h"

int main()
{
    Character character;
    TestClass test;
    Player  player;
    Enemy   enemy;

    std::cout << "부모클래스에서 상속받은 Jump 함수를 호출합니다. !\n";
    player.Jump();
    enemy.Jump();

    // 자식 클래스의 함수를 호출
    std::cout << "자식클래스 인스턴스로 재정의한 Attack 함수를 호출합니다. !\n";
    player.Attack();
    enemy.Attack();

    std::cout << "부모클래스 타입의 포인터변수에 인스턴스 주소를 지정하고 Attack 함수를 호출합니다. !\n";
    Character* pCharacter = nullptr;
    pCharacter = &player;
    pCharacter->Attack();

    pCharacter = &enemy;
    pCharacter->Attack();

    std::cout << "프로그램을 종료합니다.!\n";
}
