#include <iostream>
#include "Vector.h"

using Value = double;

int main()
{
    //Первый вектор
    Vector e;
    e.pushBack(7);
    e.pushBack(4);
    e.pushBack(6);
    e.pushBack(8);
    e.pushBack(1);
    e.pushBack(57.9897);
    std::cout << e[0] << std::endl;
    std::cout << e.size() << std::endl;
    std::cout << e.capacity() << std::endl;

    //Второй вектор
    Value mass[3] = {5.55, 8.888888, 7.865432349};
    Vector f(mass, 3, 2);
    std::cout << f[0] << std::endl;
    std::cout << f.size() << std::endl;
    std::cout << f.capacity() << std::endl;
    return 0;
}