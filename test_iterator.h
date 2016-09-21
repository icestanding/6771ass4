//
// Created by chenyu on 21/09/16.
//

#ifndef TEST_ITERATOR_H
#define TEST_ITERATOR_H

#endif //ASS4_TEST_ITERATOR_H

#include <iterator>


template <typename T> class List;

template<typename  T>
class List_iterator{
public:
    // iterator traits
    typedef std::bidirectional_iterator_tag iterator_category;
    typedef T                               value_type;
    typedef T*                              pointer;
    typedef T&                              reference;
    typedef std::ptrdiff_t                  difference_type;
    List_iterator(const std::shared_ptr<typename List<T>::Node> in): point_{in} {}
    reference operator*() const;
private:
     typename std::shared_ptr<typename List<T>::Node> point_;
};

template <typename T> typename List_iterator<T>::reference
List_iterator<T>::operator*() const {
    return point_->value_;
}
