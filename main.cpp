#include <iostream>
#include <vector>
#include "btree.h"



int main() {
//    std::cout << "hello world" << std::endl;
//    std::vector<int> a;
//    for (int i = 0; i < 10; ++i) {
//        a.push_back(i);
//    }
//    a.insert(a.begin(), -1);
////    for (int j = 0; j < a.size(); ++j) {
////        std::cout<<a[]
////    }
    btree<int> a;
    a.insert(1);
//    auto b = a.begin();
//    std::cout<<*b;
    for (int i = 0;  i <  100; ++i) {
        a.insert(i);
    }
    std::cout<<a;

//
//    std::priority_queue<int> q;
//    for (int i = 0; i < 100; ++i) {
//        q.push(i);
//    }
//    print_queue(q);
//
//
//    std::priority_queue<int, std::vector<int>, std::greater<int> > q2;
//
//    for(int n : {1,8,5,6,3,4,0,9,7,2})
//        q2.push(n);
//
//    print_queue(q2);
//
//    return 0;

    // my self iterator
}