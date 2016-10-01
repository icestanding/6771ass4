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
    btree_iterator(const  std::shared_ptr<typename btree<T>::Node> pointee, const unsigned int &index):
            pointee_(pointee), index_{index} {}

    reference operator * () const { return (*pointee_).value_[index_];};
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
    btree_iterator & operator=(const btree_const_iterator<T>& constIt) {
        pointee_ = constIt.pointee_;
        index_ = constIt.index_;
    }
    bool operator == (const btree_const_iterator<T>& other) const { return (this->pointee_ == other.pointee_)
                                                                         &&(this->index_ == other.index_); }
    bool operator!= (const btree_const_iterator<T>& other) const { return !operator==(other); }

private:
    // save index and pointer
    // casue each node save multiple value by vector, so I need to save the value index in in the node's value vector
    unsigned int index_;
    std::shared_ptr<typename btree<T>::Node> pointee_;
};

template <typename T>
class btree_const_iterator {
public:

    // iterator traits
    typedef std::bidirectional_iterator_tag iterator_category;
    typedef T                               value_type;
    typedef T*                              pointer;
    typedef T&                              reference;
    typedef std::ptrdiff_t                  difference_type;

    btree_const_iterator(const  std::shared_ptr<typename btree<T>::Node> pointee, const unsigned int &index):
            pointee_(pointee), index_{index} {}
    reference operator * () const { return (*pointee_).value_[index_];};
    // prefix
    pointer operator->() const { return &(*pointee_).value_[index_];}
    btree_const_iterator & operator++();
    btree_const_iterator & operator--();


private:
    unsigned int index_;
    std::shared_ptr<typename btree<T>::Node> pointee_;
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












// ++
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

// becasue my data structure of my btree, so it is hard to implement backward -, -
template <typename T>
btree_iterator<T> & btree_iterator<T>::operator--() {
    auto root = pointee_;
    auto index =  index_;
    if(root->children_[index] != nullptr) {
        root = root->children_[index];
        while (root->children_[root->value_.size()] != nullptr) {
            root = root->children_[root->value_.size()];
        }
        pointee_ = root;
        index_ = root->value_.size() - 1;
        return *this;
    }
    else {
        if(index != 0) {
            index_ = index - 1;
            return *this;
        }
        else {
            auto tmp = root->value_[0];
            if(root->parent_ != nullptr) {
                root = root->parent_;
                while (true) {
                    for (unsigned int i = 0; i < root->value_.size(); ++i) {
                        if (tmp < root->value_[i]) {
                            if(i == 0) {
                                if(root->parent_ != nullptr) {
                                    root = root->parent_;
                                }
                                else{
                                    return *this;
                                }
                            }
                            else {
                                pointee_ = root;
                                index_ = i - 1;
                                return *this;
                            }
                        } else {
                            if(i == root->value_.size() - 1) {
                                pointee_ = root;
                                index_ = i;
                                return *this;
                            }
                        }
                    }
                }
            }
            else {
                return *this;
            }
        }
    }
}

// const iterator ++
template <typename T>
btree_const_iterator<T> & btree_const_iterator<T>::operator++() {
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

// const iterator --
template <typename T>
btree_const_iterator<T> & btree_const_iterator<T>::operator--() {
    auto root = pointee_;
    auto index =  index_;
    if(root->children_[index] != nullptr) {
        root = root->children_[index];
        while (root->children_[root->value_.size()] != nullptr) {
            root = root->children_[root->value_.size()];
        }
        pointee_ = root;
        index_ = root->value_.size() - 1;
        return *this;
    }
    else {
        if(index != 0) {
            index_ = index - 1;
            return *this;
        }
        else {
            auto tmp = root->value_[0];
            if(root->parent_ != nullptr) {
                root = root->parent_;
                while (true) {
                    for (unsigned int i = 0; i < root->value_.size(); ++i) {
                        if (tmp < root->value_[i]) {
                            if(i == 0) {
                                if(root->parent_ != nullptr) {
                                    root = root->parent_;
                                }
                                else{
                                    return *this;
                                }
                            }
                            else {
                                pointee_ = root;
                                index_ = i - 1;
                                return *this;
                            }
                        } else {
                            if(i == root->value_.size() - 1) {
                                pointee_ = root;
                                index_ = i;
                                return *this;
                            }
                        }
                    }
                }
            }
            else {
                return *this;
            }
        }
    }
}

// nullptr, return?
#include "btree_iterator.tem"
#endif
