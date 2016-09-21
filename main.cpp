#include <iostream>
#include "test.h"

int main() {
    std::cout << "boring life" << std::endl;
    List<int> a;
    a.insert(1);
    a.insert(2);
    a.insert(3);
    a.insert(4);
    auto c = a.begin();
    std::cout<<*c;
    return 0;

    // my self iterator
}