/**
 * The btree is a linked structure which operates much like
 * a binary search tree, save the fact that multiple client
 * elements are stored in a single node.  Whereas a single element
 * would partition the tree into two ordered subtrees, a node 
 * that stores m client elements partition the tree 
 * into m + 1 sorted subtrees.
 */

#ifndef BTREE_H
#define BTREE_H

#include <iostream>
#include <cstddef>
#include <utility>
#include <memory>
#include <vector>
#include <queue>
#include <ostream>
#include <stack>
// we better include the iterator
#include "btree_iterator.h"

// we do this to avoid compiler errors about non-template friends
// what do we do, remember? :)
template <typename T> class btree;
template <typename T> std::ostream& operator<<(std::ostream& os, const btree<T>& tree);

template <typename T> 
class btree {
 public:
    friend class btree_iterator<T>;
    friend class btree_const_iterator<T>;

    typedef btree_iterator<T>                                    iterator;
    typedef btree_iterator<T>                              const_iterator;

    typedef btree_reverse_iterator<iterator>              reverse_iterator;
    typedef btree_reverse_iterator<const_iterator>  const_reverse_iterator;
  /** Hmm, need some iterator typedefs here... friends? **/

  /**
   * Constructs an empty btree.  Note that
   * the elements stored in your btree must
   * have a well-defined zero-arg constructor,
   * copy constructor, operator=, and destructor.
   * The elements must also know how to order themselves
   * relative to each other by implementing operator<
   * and operator==. (These are already implemented on
   * behalf of all built-ins: ints, doubles, strings, etc.)
   *
   * @param maxNodeElems the maximum number of elements
   *        that can be stored in each B-Tree node
   */
    btree(size_t maxNodeElems = 40): head_{nullptr}, size_{maxNodeElems} {};



    /**
    * Copy constructor
    * Creates a new B-Tree as a copy of original.
    *
    * @param original a const lvalue reference to a B-Tree object
    */
    btree(const btree<T>& original);

    /**
    * Move constructor
    * Creates a new B-Tree by "stealing" from original.
    *
    * @param original an rvalue reference to a B-Tree object
    */
    btree(btree<T>&& original);

    /**
    * Copy assignment
    * Replaces the contents of this object with a copy of rhs.
    *
    * @param rhs a const lvalue reference to a B-Tree object
    */
    btree<T>& operator=(const btree<T>& rhs);

    /**
    * Move assignment
    * Replaces the contents of this object with the "stolen"
    * contents of original.
    *
    * @param rhs a const reference to a B-Tree object
    */
    btree<T>& operator= (btree<T>&& rhs);

    /**
    * Puts a breadth-first traversal of the B-Tree onto the output
    * stream os. Elements must, in turn, support the output operator.
    * Elements are separated by space. Should not output any newlines.
    *
    * @param os a reference to a C++ output stream
    * @param tree a const reference to a B-Tree object
    * @return a reference to os
    */
    friend std::ostream& operator<< <T>(std::ostream& os, const btree<T>& tree);
//
  /**
   * The following can go here
   * -- begin()
   * -- end()
   * -- rbegin()
   * -- rend()
   * -- cbegin()
   * -- cend()
   * -- crbegin()
   * -- crend()
   */


    iterator begin() const { return iterator(head(), 0); }

    iterator end() const { return iterator(nullptr, 0); }

    const_iterator cbegin() const { return const_iterator(head(), 0); };

    const_iterator cend() const { return const_iterator(nullptr, 0); };

    reverse_iterator rbegin() { return reverse_iterator(end()); }

    const_iterator crbegin() const  { return  const_reverse_iterator(cend()); }

    reverse_iterator rend() { return  reverse_iterator(begin());}

    const_reverse_iterator crend() const { return const_reverse_iterator(cbegin());}
    /**
    * Returns an iterator to the matching element, or whatever
    * the non-const end() returns if the element could
    * not be found.
    *
    * @param elem the client element we are trying to match.  The elem,
    *        if an instance of a true class, relies on the operator< and
    *        and operator== methods to compare elem to elements already
    *        in the btree.  You must ensure that your class implements
    *        these things, else code making use of btree<T>::find will
    *        not compile.
    * @return an iterator to the matching element, or whatever the
    *         non-const end() returns if no such match was ever found.
    */
    iterator find(const T& elem);

    /**
    * Identical in functionality to the non-const version of find,
    * save the fact that what's pointed to by the returned iterator
    * is deemed as const and immutable.
    *
    * @param elem the client element we are trying to match.
    * @return an iterator to the matching element, or whatever the
    *         const end() returns if no such match was ever found.
    */
    const_iterator find(const T& elem) const;

//
    /**
    * Operation which inserts the specified element
    * into the btree if a matching element isn't already
    * present.  In the event where the element truly needs
    * to be inserted, the size of the btree is effectively
    * increases by one, and the pair that gets returned contains
    * an iterator to the inserted element and true in its first and
    * second fields.
    *
    * If a matching element already exists in the btree, nothing
    * is added at all, and the size of the btree stays the same.  The
    * returned pair still returns an iterator to the matching element, but
    * the second field of the returned pair will store false.  This
    * second value can be checked to after an insertion to decide whether
    * or not the btree got bigger.
    *
    * The insert method makes use of T's zero-arg constructor and
    * operator= method, and if these things aren't available,
    * then the call to btree<T>::insert will not compile.  The implementation
    * also makes use of the class's operator== and operator< as well.
    *
    * @param elem the element to be inserted.
    * @return a pair whose first field is an iterator positioned at
    *         the matching element in the btree, and whose second field
    *         stores true if and only if the element needed to be added
    *         because no matching element was there prior to the insert call.
    */
    std::pair<iterator, bool> insert(const T& elem);

  /**
    * Disposes of all internal resources, which includes
    * the disposal of any client objects previously
    * inserted using the insert operation.
    * Check that your implementation does not leak memory!
    */
    // use smart pointer all the time
    ~btree(){};



private:
    // node
    class Node{
    public:
        // vector save the sub-node value
        std::vector<T> value_;
        // vector save each children pointer
        std::vector<Node*> children_;
        Node * parent_;
        size_t size_;
        // member function
        Node(const T &value, size_t size,  Node * parent = nullptr):
                value_(1, value), children_(size + 1, nullptr), parent_{parent}, size_{size} {};
        Node(const Node &cpy);
        std::pair<unsigned int, bool> priority_insert(const T &);
        std::pair<unsigned int, bool> find_position(const T &);

    };
    Node * head_;
    size_t size_;
 

    Node * head() const;
    Node * tail() const;

};
// copy assignment
template <typename T>
btree<T> & btree<T>::operator=(const btree<T> &rhs) {
    if(head_ == rhs.head_ && size_ == rhs.size_) {
        return *this;
    }
    size_ = rhs.size_;
    auto node =  new Node(*rhs.head_);
    head_ = node;
    return *this;
}


// move assignment
template <typename T>
btree<T> & btree<T>::operator = (btree<T> &&rhs) {
    if(head_ == rhs.head_ && size_ == rhs.size_) {
        return *this;
    }
    head_ = rhs.head_;
    rhs.head_ = nullptr;
    size_ = rhs.size_;
    return *this;
}

// return head
template <typename T>
typename btree<T>::Node* btree<T>::head() const {
    if(head_ == nullptr) {
        return head_;
    }
    auto root = head_;
    while (root != nullptr) {
        if(root->children_[0] != nullptr) {
            root = root->children_[0];
        }
        else {
            break;
        }
    }
    return root;
}

// tail
template <typename T>
typename btree<T>::Node* btree<T>::tail() const {
    if(head_ == nullptr) {
        return head_;
    }
    auto root = head_;
    while (root != nullptr) {
        for (unsigned int i = 0; i < root->value_.size(); ++i) {
            if(root->value_.size() < size_) {
                return root;
            }
            if(root->children_[size_] == nullptr) {
                return root;
            } else {
                root = root->children_[size_];
            }
        }
    }
}


// node copy constructor
template <typename T>
btree<T>::Node::Node(const Node &cpy) {
    size_ = cpy.size_;
    for (unsigned int k = 0; k < size_ + 1; ++k) {
        children_.push_back(nullptr);
    }
    for (unsigned int i = 0; i < cpy.value_.size(); ++i) {
        value_.push_back(cpy.value_[i]);
    }
    for (unsigned int j = 0; j < cpy.children_.size(); ++j) {
        if(cpy.children_[j] != nullptr) {
            auto node = new Node(*cpy.children_[j]);
            children_[j] = node;

        }
    }
}
// copy constructor
template <typename T>
btree<T>::btree(const btree<T> &original) {
    size_ = original.size_;
    auto new_head = new Node(*original.head_);
    head_ = new_head;
}
// move constructor
template <typename T>
btree<T>::btree(btree<T> &&original) {
    size_ = std::move(original.size_);
    head_ = original.head_;
    original.head_ = nullptr;
}
// find
template <typename T>
typename btree<T>::iterator btree<T>::find(const T &elem) {
    if (head_ == nullptr) {
        return iterator(nullptr, 0);
    }
    auto root = head_;
    while (true) {
        if (root->value_.size() < size_) {
            for (unsigned int i = 0; i < root->value_.size(); ++i) {
                if(root->value_[i] == elem) {
                    return iterator(root, i);
                }
            }
            return iterator(nullptr, 0);
        }
        else {
            auto position = root->find_position(elem);
            if(position.second == false) {
                return iterator(root, position.first);

            }
            else {
                if(root->children_[position.first] != nullptr) {
                    root = root->children_[position.first];
                } else {
                    return iterator(nullptr, 0);
                }
            }
        }
    }
}

// const find;
template <typename T>
typename btree<T>::const_iterator btree<T>::find(const T &elem) const {
    if (head_ == nullptr) {
        return const_iterator(nullptr, 0);
    }
    auto root = head_;
    while (true) {
        if (root->value_.size() < size_) {
            for (unsigned int i = 0; i < root->value_.size(); ++i) {
                if(root->value_[i] == elem) {
                    return const_iterator(root, i);
                }
            }
            return const_iterator(nullptr, 0);
        }
        else {
            auto position = root->find_position(elem);
            if(position.second == false) {
                return const_iterator(root, position.first);

            }
            else {
                if(root->children_[position.first] != nullptr) {
                    root = root->children_[position.first];
                } else {
                    return const_iterator(nullptr, 0);
                }
            }
        }
    }
}

// insert with priority
template <typename T>
std::pair<unsigned int, bool> btree<T>::Node::priority_insert(const T &value) {
    for (unsigned int i = 0; i < value_.size(); ++i) {
        if (value > value_[i]) {
            continue;
        }
        else if (value == value_[i]) {
            return std::pair<unsigned int, bool>(i, false);
        }
        else {
            value_.insert(value_.begin() + i, value);
            return std::pair<unsigned int, bool>(i, true);
        }
    }
    value_.push_back(value);
    return std::pair<unsigned int, bool>(value_.size() - 1, true);
}

// find position;
template <typename T>
std::pair<unsigned int, bool> btree<T>::Node::find_position(const T &value) {

    for (unsigned int i = 0; i <= size_ ; ++i) {
        if(i == 0) {
            if(value < value_[i]) {
                return std::pair<unsigned int, bool>(0, true);
            } else if (value == value_[0]) {
                return std::pair<unsigned int, bool>(0, false);
            } else {
                continue;
            }
        } else {
            if(value < value_[i]) {
                return std::pair<unsigned int, bool>(i, true);
            } else if (value == value_[i]) {
                return std::pair<unsigned int, bool>(0, false);
            } else {
                continue;
            }
        }
    }
    return std::pair<unsigned int, bool>(size_, true);
}




// insertion
template <typename T>
std::pair<typename btree<T>::iterator, bool> btree<T>::insert(const T &elem) {
    if (head_ == nullptr) {
        head_ = new Node(elem, size_);
        return  std::pair<iterator, bool>(btree_iterator<T>(head_, 0), true);
    }
    auto root = head_;
    // do insertion
    while (true) {
        if (root->value_.size() < size_) {
            auto index = root->priority_insert(elem);
            return std::pair<iterator, bool>(btree<T>::find(elem), index.second);
        }
        else {
            auto position = root->find_position(elem);
            if(position.second == false) {
                return std::pair<iterator, bool>(btree_iterator<T>(root, position.first), position.second);
            }
            else {
                if(root->children_[position.first] != nullptr) {
                    root = root->children_[position.first];
                }
                else {
                    auto new_node = new Node(elem, size_, root);
                    root->children_[position.first] = new_node;
                    return std::pair<iterator, bool>(btree_iterator<T>(new_node, 0), true);
                }
            }
        }
    }
}

// print function
template <typename T>
std::ostream& operator<< (std::ostream& os, const btree<T>& tree) {
    if(tree.head_ == nullptr) {
        return os;
    }
    std::queue<typename btree<T>:: Node *>  bfs;
    std::vector<T> answer;
    bfs.push(tree.head_);
    while(!bfs.empty()) {
        auto node = bfs.front();
        bfs.pop();
        for (unsigned int i = 0; i < node->value_.size(); ++i) {
            answer.push_back(node->value_[i]);
        }
        for (unsigned int i = 0; i < node->children_.size(); ++i) {
            if (node->children_[i] != nullptr) {
                bfs.push(node->children_[i]);
            }
        }
    }
    for (unsigned int j = 0; j < answer.size(); ++j) {
        if(j == answer.size() - 1) {
            os<<answer[j];
            break;
        }
        os<<answer[j]<<" ";
    }
    return os;
}

// question << stream

#include "btree.tem"

#endif
