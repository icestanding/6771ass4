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

    // const std::shared_ptr<typename List<T>::Node>
    btree_iterator(const std::shared_ptr<typename btree<T>::Node> npointer, unsigned int index):
            npointer_{npointer}, index_{index} {};
    reference operator * ();

private:
    // save node address
    std::shared_ptr<typename btree<T>::Node> npointer_;
    // save value index in that node
    unsigned int index_;
};

template <typename T>
typename btree_iterator<T>::reference btree_iterator<T>::operator*() {
    return npointer_->value_[index_];
}


#include "btree_iterator.tem"
#endif
