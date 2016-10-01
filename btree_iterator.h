#ifndef BTREE_ITERATOR_H
#define BTREE_ITERATOR_H

#include <iterator>
#include "btree.h"

/**
 * You MUST implement the btree iterators as (an) external class(es) in this file.
 * Failure to do so will result in a total mark of 0 for this deliverable.
 **/

// iterator related interface stuff here; would be nice if you called your
// iterator class btree_iterator (and possibly const_btree_iterator)

template <typename T> class btree;


// iterator, const iterator, reverse iterator, reverse const iterator

template <typename T>
class btree_iterator {
public:

    // iterator traits
    typedef std::bidirectional_iterator_tag iterator_category;
    typedef T                               value_type;
    typedef T*                              pointer;
    typedef T&                              reference;
    typedef std::ptrdiff_t                  difference_type;

    btree_iterator(const  std::shared_ptr<typename btree<T>::Node> pointee, const unsigned int &index):
            pointee_(pointee), index_{index} {}
    reference operator * () { return (*pointee_).value_[index_];};
    // prefix
    btree_iterator & operator++();

private:
    // save index and pointer
    // casue each node save multiple value by vector, so I need to save the value index in in the node's value vector
    unsigned int index_;
    std::shared_ptr<typename btree<T>::Node> pointee_;
};


template <typename T>
btree_iterator<T> & btree_iterator<T>::operator++() {
    auto root = pointee_;
    auto index =  index_;
    if(root->children_[index + 1] == nullptr) {
        // if not the last one
        if(index + 1 < root->value_.size()) {
            index_ = index + 1;
            return *this;
        } else {
            auto tmp = root->value_[index];
            root = root->parent_;
            while (true) {
                for (unsigned int i = 0; i < root->value_.size(); ++i) {
                    if(tmp < root->value_[i]) {
                        pointee_ = root;
                        index_ = i;
                        return *this;
                    }
                }
                if(root->parent_ != nullptr) {
                    root = root->parent_;
                } else {
                    pointee_ = nullptr;
                    index_ = 0;
                    return *this;
                }
            }
        }
    }
    else {
        root=root->children_[index + 1];
        while (root != nullptr) {
            if(root->children_[0] != nullptr) {
                root = root->children_[0];
            }
            else {
                break;
            }
        }
        pointee_ = root;
        index_ = 0;
        return *this;
    }

}








// nullptr, return?
#include "btree_iterator.tem"
#endif
