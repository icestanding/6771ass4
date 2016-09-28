#ifndef BTREE_ITERATOR_H
#define BTREE_ITERATOR_H

#include <iterator>

/**
 * You MUST implement the btree iterators as (an) external class(es) in this file.
 * Failure to do so will result in a total mark of 0 for this deliverable.
 **/

// iterator related interface stuff here; would be nice if you called your
// iterator class btree_iterator (and possibly const_btree_iterator)

template <typename T> class btree;


template <typename T>
class btree_iterator {
public:
    // iterator traits
    typedef std::bidirectional_iterator_tag iterator_category;
    typedef T                               value_type;
    typedef T*                              pointer;
    typedef T&                              reference;
    typedef std::ptrdiff_t                  difference_type;

    btree_iterator(const std::vector<T*> &result, const unsigned int &index = 0): pointee_(result), index_{index}{}
    reference operator * () { return *pointee_[index_];};
//    reference operator -> () const {
//        return &(operator*());
//    };
    pointer operator->() const { return pointee_[index_]; }
    // pre-increment
    btree_iterator<T> & operator++() {
        if(index_ + 1 < pointee_.size()) {
            index_ += 1;
        }
        return *this;
    }
    // post-increment
    void operator ++(int) { ++(*this); }

    btree_iterator<T> & operator--() {
        if(index_ - 1 >= 0 ) {
            index_ -= 1;
        }
        return *this;
    }
    void operator--(int) { --(*this); }

    bool operator==(const btree_iterator<T>& other) const { return this->pointee_[index_] == other.pointee_[index_]; }
    bool operator!=(const btree_iterator<T>& other) const { return !operator==(other); }

//    // converstions from const to non-const version of iterator
//    btree_iterator& operator=(const btree_const_iterator<T>& constIt) {
//        pointee_ = constIt.pointee_;
//        btree_ = constIt.btree_;
//    }
//    bool operator==(const btree_const_iterator<T>& other) const { return this->pointee_ == other.pointee_; }
//    bool operator!=(const btree_const_iterator<T>& other) const { return !operator==(other); }


private:
    // save index and pointer
    unsigned int index_;
    std::vector<pointer> pointee_;
};


//template <typename T>
//class btree_const_iterator {
//public:
//    // iterator traits
//    typedef std::bidirectional_iterator_tag iterator_category;
//    typedef T                               value_type;
//    typedef T*                              pointer;
//    typedef T&                              reference;
//    typedef std::ptrdiff_t                  difference_type;
//
//    btree_iterator(const std::vector<T*> &result, const unsigned int &index = 0): pointee_(result), index_{index}{}
//    reference operator * () { return *pointee_[index_];};
////    reference operator -> () const {
////        return &(operator*());
////    };
//    pointer operator->() const { return pointee_[index_]; }
//    // pre-increment
//    btree_iterator<T> & operator++() {
//        if(index_ + 1 < pointee_.size()) {
//            index_ += 1;
//        }
//        return *this;
//    }
//    // post-increment
//    void operator ++(int) { ++(*this); }
//
//    btree_iterator<T> & operator--() {
//        if(index_ - 1 >= 0 ) {
//            index_ -= 1;
//        }
//        return *this;
//    }
//    void operator--(int) { --(*this); }
//
//    bool operator==(const btree_iterator<T>& other) const { return this->pointee_[index_] == other.pointee_[index_]; }
//    bool operator!=(const btree_iterator<T>& other) const { return !operator==(other); }
//
////    // converstions from const to non-const version of iterator
////    btree_iterator& operator=(const btree_const_iterator<T>& constIt) {
////        pointee_ = constIt.pointee_;
////        btree_ = constIt.btree_;
////    }
////    bool operator==(const btree_const_iterator<T>& other) const { return this->pointee_ == other.pointee_; }
////    bool operator!=(const btree_const_iterator<T>& other) const { return !operator==(other); }
//
//
//private:
//    // save index and pointer
//    unsigned int index_;
//    std::vector<pointer> pointee_;
//};

// nullptr, return?
#include "btree_iterator.tem"
#endif
