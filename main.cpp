#include <iostream>
#include <vector>
#include "btree.h"



int main() {
    btree<int> a;
    for (unsigned int i = 10; i < 15; ++i) {
        a.insert(i);
    }
    for (unsigned int j = 0; j < 5; ++j) {
        a.insert(j);
    }
//    std::cout<<a<<"\n";
    auto b = a.begin();
//    std::cout<<*b;
}