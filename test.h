//
// Created by chenyu on 21/09/16.
//

#ifndef  TEST_H
#define  TEST_H
#endif //ASS4_TEST_H


#include <iostream>
#include <cstddef>
#include <utility>
#include <memory>

#include "test_iterator.h"

template<typename T>
class List{
private:
    class Node{
    public:
        T value_;
        std::shared_ptr<Node> next_;
        Node(const T &value): value_{value}, next_{nullptr} {};
        T getv() {
            return value_;
        }
    };
    std::shared_ptr<Node> head_;


public:
    friend class List_iterator<T>;
    typedef List_iterator<T> iterator;

    // constructor
    List(): head_{nullptr} {};
    ~List() {
        head_ = nullptr;
    }

    //  member function
    iterator begin() {
        return iterator(head_);
    }

    iterator end() {
        return iterator(nullptr);
    }

    void insert(const T &value) {
        if (head_ == nullptr) {
            head_ = std::make_shared<Node>(value);
        } else {
            auto tmp = head_;
            while (tmp->next_ != nullptr) {
                tmp = tmp->next_;
            }
            tmp->next_ = std::make_shared<Node>(value);
        }
    }

};