#include <iostream>
#include <vector>
#include "btree.h"



int main() {
    btree<int> graph;

    graph.insert(1);
    graph.insert(2);

    btree<int> abc = graph;
    abc.insert(123);
    std::cout<<graph;

}