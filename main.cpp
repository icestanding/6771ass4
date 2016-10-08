#include <iostream>
#include <vector>
#include "btree.h"



int main() {

    auto a = new btree<int>(3);
    a->insert(1);
    a->insert(4);
    a->insert(3);
    a->insert(5);
    a->insert(6);
    a->insert(100);
    a->insert(122);
    a->insert(1223);
    btree<int> b;
    b = *a;

    auto hobv = a->rbegin();
    std::cout<<*hobv;

}