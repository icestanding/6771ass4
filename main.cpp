#include <iostream>
#include <vector>
#include "btree.h"



int main() {
    btree<int> a;
    for (unsigned int i = 6; i < 10 ; ++i) {
        a.insert(i);
    }
    for (unsigned int i = 1; i <5 ; ++i) {
        a.insert(i);
    }
    for (unsigned int i = 20; i <25 ; ++i) {
        a.insert(i);
    }
    for (unsigned int i = 30; i <35 ; ++i) {
        a.insert(i);
    }
    for (unsigned int i = 15; i <20 ; ++i) {
        a.insert(i);
    }
    auto c = a.crend();
    std::cout<<*c;



}