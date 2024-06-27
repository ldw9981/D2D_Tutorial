#include "TestVectorAndClass.h"
#include <vector>
#include <iostream>
#include <stdio.h>
#include <assert.h>

class Test
{
public:
    Test* pInstance = nullptr;
    static int ConstructCount;
    static int DestructCount;
    Test()
    {
        pInstance = this;
        ConstructCount++;
        std::cout << "������ ȣ���" << this << ConstructCount << std::endl;
       
    }
    Test(const Test& other)
    {
        pInstance = this;
        ConstructCount++;
        std::cout << "���� ������ ȣ���" << this << ConstructCount << std::endl;
    }
    ~Test()
    {
        DestructCount++;
        std::cout << "�ı��� ȣ���" << this;
        assert(pInstance == this);

        std::cout << DestructCount << std::endl;
        
    }
};
int Test::ConstructCount = 0;
int Test::DestructCount = 0;

void mainTestVectorAndClass()
{
    std::vector<Test> Container;
    Test item;

    std::cout << "Container.push_back(item)" << std::endl;
    Container.push_back(item);   
    Container.push_back(item);
    Container.push_back(item);
    Container.push_back(item);
    Container.push_back(item);
    Container.push_back(item);



    std::cout << "Ű�������� ����" << std::endl;
    system("pause");
}
