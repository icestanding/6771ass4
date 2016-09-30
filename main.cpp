#include <iostream>
#include <vector>
#include "btree.h"



int main() {
    btree<int> a;
    for (unsigned int i = 80; i <90 ; ++i) {
        a.insert(i);
    }
    for (unsigned int i = 50; i <60 ; ++i) {
        a.insert(i);
    }
    for (unsigned int i = 91; i <100 ; ++i) {
        a.insert(i);
    }
    for (unsigned int i = 91; i <100 ; ++i) {
        a.insert(i);
    }

    for (unsigned int j = 3; j < 4; ++j) {
        a.insert(j);
    }
    for (unsigned int i = 1000; i < 1020 ; ++i) {
        a.insert(i);
    }
    std::cout<<a<<"\n";



}