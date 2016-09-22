#include <iostream>
#include "btree.h"

int main() {
    std::cout << "hello world" << std::endl;
    btree<int> a;
    a.insert(1);
    auto b = a.begin();
    std::cout<<*b;
    return 0;

    // my self iterator
}