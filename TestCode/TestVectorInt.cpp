#include <iostream>
#include <vector>

int TestVectorInt() {
    std::vector<int> vec;
    vec.reserve(2); // �ʱ� �뷮�� 2�� ����

    for (int i = 0; i < 5; ++i) {
        vec.push_back(i);
        std::cout << "Added " << i
            << ", size: " << vec.size()
            << ", capacity: " << vec.capacity()
            << ", address of first element: " << &vec[0]
            << std::endl;
    }

    return 0;
}