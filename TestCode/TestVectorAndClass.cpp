#include "TestVectorAndClass.h"
#include <vector>
#include <iostream>



class Test
{
public:
    static int ConstructCount;
    static int DestructCount;
    Test()
    {
        ConstructCount++;
        std::cout << "������ ȣ���" << ConstructCount << std::endl;
       
    }
    ~Test()
    {
        DestructCount++;
        std::cout << "�ı��� ȣ���" << DestructCount << std::endl;
        
    }
};
int Test::ConstructCount = 0;
int Test::DestructCount = 0;

void mainTestVectorAndClass()
{
    std::vector<Test> Container;
    Test item;


    Container.push_back(item);
    Container.push_back(item);
    Container.push_back(item);
}
