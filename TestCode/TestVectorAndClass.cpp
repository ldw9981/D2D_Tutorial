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
        std::cout << "생성자 호출됨" << this << ConstructCount << std::endl;
       
    }
    Test(const Test& other)
    {
        pInstance = this;
        ConstructCount++;
        std::cout << "복사 생성자 호출됨" << this << ConstructCount << std::endl;
    }
    ~Test()
    {
        DestructCount++;
        std::cout << "파괴자 호출됨" << this;
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



    std::cout << "키를눌러야 진행" << std::endl;
    system("pause");
}
