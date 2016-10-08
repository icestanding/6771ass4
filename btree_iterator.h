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
template <typename T> class btree_const_iterator;

// iterator, const iterator, reverse iterator, reverse const iterator

template <typename T>
class btree_iterator {
public:
    friend class btree_const_iterator<T>;
    // iterator traits
    typedef std::bidirectional_iterator_tag iterator_category;
    typedef T                               value_type;
    typedef T*                              pointer;
    typedef T&                              reference;
    typedef std::ptrdiff_t                  difference_type;

    // constructor
    btree_iterator(typename btree<T>::Node *pointee = nullptr, const unsigned int &index = 0):
            pointee_(pointee), index_{index} {}
    reference operator * () const {  return (*pointee_).value_[index_]; };
    pointer operator->() const { return &(*pointee_).value_[index_];}
    // prefix
    btree_iterator & operator++();
    void operator ++ (int) { ++(*this); };
    btree_iterator & operator--();
    void operator -- (int) { --(*this); };
    bool operator == (const btree_iterator& other) const { return (this->pointee_ == other.pointee_)
                                                                &&(this->index_ == other.index_); }
    bool operator != (const btree_iterator& other) const { return !operator==(other); }
    // converstions from const to non-const version of iterator
    btree_iterator & operator = (const btree_const_iterator<T>& constIt) {
        pointee_ = constIt.pointee_;
        index_ = constIt.index_;
    }
    bool operator == (const btree_const_iterator<T>& other) const { return (this->pointee_ == other.pointee_)
                                                                           &&(this->index_ == other.index_); }
    bool operator!= (const btree_const_iterator<T>& other) const { return !operator==(other); }

private:
    // save index and pointer
    // casue each node save multiple value by vector, so I need to save the value index in in the node's value vector
    typename btree<T>::Node * pointee_;
    unsigned int index_;
};

template <typename T>
class btree_const_iterator {
public:
    friend class btree_iterator<T>;
    // iterator traits
    typedef std::bidirectional_iterator_tag iterator_category;
    typedef T                               value_type;
    typedef T*                              pointer;
    typedef T&                              reference;
    typedef std::ptrdiff_t                  difference_type;

    btree_const_iterator(typename btree<T>::Node *pointee = nullptr, const unsigned int &index = 0):
            pointee_(pointee), index_{index} {}
    reference operator * () const { return (*pointee_).value_[index_];};
    // prefix
    pointer operator->() const { return &(*pointee_).value_[index_];}
    btree_const_iterator & operator++();
    btree_const_iterator & operator--();
    void operator++(int) { ++(*this); }
    void operator--(int) { --(*this); }
    bool operator==(const btree_const_iterator& other) const { return this->pointee_ == other.pointee_
                                                                      &&(this->index_ == other.index_);; }

    bool operator!=(const btree_const_iterator& other) const { return !operator==(other); }

    btree_const_iterator(const btree_iterator<T>& nonConstIt) : pointee_(nonConstIt.pointee_),
                                                               index_(nonConstIt.index_) {}

    btree_const_iterator& operator=(const btree_iterator<T>& nonConstIt) {
        pointee_ = nonConstIt.pointee_;
        index_ = nonConstIt.index_;
    }
    bool operator==(const btree_iterator<T>& other) const { return this->pointee_ == other.pointee_
                                                                   &&(this->index_ == other.index_);; }
    bool operator!=(const btree_iterator<T>& other) const { return !operator==(other); }

private:
    typename btree<T>::Node * pointee_;
    unsigned int index_;
};

template <typename ForwardItType>
class btree_reverse_iterator {
public:
    typedef typename ForwardItType::difference_type      difference_type;
    typedef typename ForwardItType::iterator_category    iterator_category;
    typedef typename ForwardItType::value_type           value_type;
    typedef typename ForwardItType::pointer              pointer;
    typedef typename ForwardItType::reference            reference;

    btree_reverse_iterator() : current_() {}
    btree_reverse_iterator(ForwardItType forit) : current_(forit) {}
    btree_reverse_iterator(const btree_reverse_iterator& other) : current_(other.current_) {}


    template <typename OtherItType>
    btree_reverse_iterator(const btree_reverse_iterator<OtherItType>& other) : current_(other.base()) {}

    ForwardItType base() const { return current_; }

    reference operator*() const {
        ForwardItType tmp = current_;
        return *--tmp;
    }
    pointer operator->() const { return &(operator*()); }
    btree_reverse_iterator& operator++() { --current_; return *this; }
    void operator++(int) { ++(*this); }
    btree_reverse_iterator& operator--() { ++current_; return *this; }
    void operator--(int) { --(*this); }

    bool operator==(const btree_reverse_iterator& other) const { return base() == other.base(); }
    bool operator!=(const btree_reverse_iterator& other) const { return !operator==(other); }


protected:
    ForwardItType current_;
};



#include "btree_iterator.tem"
#endif
