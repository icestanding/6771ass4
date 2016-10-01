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

    std::cout<<a<<"\n";
    auto b = a.begin();
    for (unsigned int k = 0; k < 20; ++k) {
        std::cout<<*b<<"\n";
        ++b;
    }
    std::cout<<*b<<"\n";
    std::cout<<"decrease"<<"\n";
    for (unsigned int k = 0; k < 20; ++k) {
        --b;
        std::cout << *b << "\n";
    }


}