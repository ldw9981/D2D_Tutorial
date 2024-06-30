// Polymorphism.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Player.h"
#include "Enemy.h"
#include "Character.h"
#include "TestClass.h"

int main()
{
    TestCharacter character;
    TestClass test;
    Player  player;
    Enemy   enemy;

    std::cout << "�θ�Ŭ�������� ��ӹ��� Jump �Լ��� ȣ���մϴ�. !\n";
    player.Jump();
    enemy.Jump();

    // �ڽ� Ŭ������ �Լ��� ȣ��
    std::cout << "�ڽ�Ŭ���� �ν��Ͻ��� �������� Attack �Լ��� ȣ���մϴ�. !\n";
    player.Attack();
    enemy.Attack();

    std::cout << "�θ�Ŭ���� Ÿ���� �����ͺ����� �ν��Ͻ� �ּҸ� �����ϰ� Attack �Լ��� ȣ���մϴ�. !\n";
    TestCharacter* pCharacter = nullptr;
    pCharacter = &player;
    pCharacter->Attack();

    pCharacter = &enemy;
    pCharacter->Attack();

    std::cout << "���α׷��� �����մϴ�.!\n";
}
