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
    typedef btree_iterator<T> iterator;

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

//  /**
//   * The copy constructor and  assignment operator.
//   * They allow us to pass around B-Trees by value.
//   * Although these operations are likely to be expensive
//   * they make for an interesting programming exercise.
//   * Implement these operations using value semantics and
//   * make sure they do not leak memory.
//   */
//
//  /**
//   * Copy constructor
//   * Creates a new B-Tree as a copy of original.
//   *
//   * @param original a const lvalue reference to a B-Tree object
//   */
//  btree(const btree<T>& original);
//
//  /**
//   * Move constructor
//   * Creates a new B-Tree by "stealing" from original.
//   *
//   * @param original an rvalue reference to a B-Tree object
//   */
//  btree(btree<T>&& original);
//
//
//  /**
//   * Copy assignment
//   * Replaces the contents of this object with a copy of rhs.
//   *
//   * @param rhs a const lvalue reference to a B-Tree object
//   */
//  btree<T>& operator=(const btree<T>& rhs);
//
//  /**
//   * Move assignment
//   * Replaces the contents of this object with the "stolen"
//   * contents of original.
//   *
//   * @param rhs a const reference to a B-Tree object
//   */
//  btree<T>& operator=(btree<T>&& rhs);
//
//  /**
//   * Puts a breadth-first traversal of the B-Tree onto the output
//   * stream os. Elements must, in turn, support the output operator.
//   * Elements are separated by space. Should not output any newlines.
//   *
//   * @param os a reference to a C++ output stream
//   * @param tree a const reference to a B-Tree object
//   * @return a reference to os
//   */
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
//    iterator begin() {
//        return iterator(head_, 0);
//    }
//    iterator end() {
//        return iterator(nullptr, 0);
//    }
//
//  /**
//    * Returns an iterator to the matching element, or whatever
//    * the non-const end() returns if the element could
//    * not be found.
//    *
//    * @param elem the client element we are trying to match.  The elem,
//    *        if an instance of a true class, relies on the operator< and
//    *        and operator== methods to compare elem to elements already
//    *        in the btree.  You must ensure that your class implements
//    *        these things, else code making use of btree<T>::find will
//    *        not compile.
//    * @return an iterator to the matching element, or whatever the
//    *         non-const end() returns if no such match was ever found.
//    */
//  iterator find(const T& elem);
//
//  /**
//    * Identical in functionality to the non-const version of find,
//    * save the fact that what's pointed to by the returned iterator
//    * is deemed as const and immutable.
//    *
//    * @param elem the client element we are trying to match.
//    * @return an iterator to the matching element, or whatever the
//    *         const end() returns if no such match was ever found.
//    */
//  const_iterator find(const T& elem) const;
//
//  /**
//    * Operation which inserts the specified element
//    * into the btree if a matching element isn't already
//    * present.  In the event where the element truly needs
//    * to be inserted, the size of the btree is effectively
//    * increases by one, and the pair that gets returned contains
//    * an iterator to the inserted element and true in its first and
//    * second fields.
//    *
//    * If a matching element already exists in the btree, nothing
//    * is added at all, and the size of the btree stays the same.  The
//    * returned pair still returns an iterator to the matching element, but
//    * the second field of the returned pair will store false.  This
//    * second value can be checked to after an insertion to decide whether
//    * or not the btree got bigger.
//    *
//    * The insert method makes use of T's zero-arg constructor and
//    * operator= method, and if these things aren't available,
//    * then the call to btree<T>::insert will not compile.  The implementation
//    * also makes use of the class's operator== and operator< as well.
//    *
//    * @param elem the element to be inserted.
//    * @return a pair whose first field is an iterator positioned at
//    *         the matching element in the btree, and whose second field
//    *         stores true if and only if the element needed to be added
//    *         because no matching element was there prior to the insert call.
//    */
    std::pair<iterator, bool> insert(const T& elem);

  /**
    * Disposes of all internal resources, which includes
    * the disposal of any client objects previously
    * inserted using the insert operation.
    * Check that your implementation does not leak memory!
    */
//    ~btree();



private:
    // node
    class Node{
    public:
        std::vector<T> value_;
        std::vector<std::shared_ptr<Node>> children_;
        std::shared_ptr<Node> parent_;
        size_t size_;

        // member function
        Node(const T &value, size_t size,  std::shared_ptr<Node> parent = nullptr):
                value_(1, value), children_(size, nullptr), size_{size} ,parent_{parent} {};
        std::pair<unsigned int, bool> priority_insert(const T &);
        std::pair<unsigned int, bool> find_position(const T &);
    };
    size_t size_;
    std::shared_ptr<Node> head_;
    std::vector<std::pair<std::shared_ptr<Node>, unsigned int>> preorder_;
};



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
            value_.insert(value_.begin() + i, i);
            return std::pair<unsigned int, bool>(i, true);
        }
    }
}

template <typename T>
std::pair<unsigned int, bool> btree<T>::Node::find_position(const T &value) {
    for(unsigned int i; i <= size_; i++) {
        if (value > value_[i]) {
            continue;
        }
        else if (value == value_[i]) {
            return std::pair<unsigned int, bool>(i, false);
        }
        else {
             return std::pair<unsigned int, bool>(i, true);
        }
    }
    return std::pair<unsigned int, bool>(size_, true);
}

// insertion
template <typename T>
std::pair<typename btree<T>::iterator, bool> btree<T>::insert(const T &elem) {
    if (head_ == nullptr) {
        head_ = std::make_shared<btree<T>::Node>(elem, size_);
        return  std::pair<iterator, bool>(btree_iterator<T>(head_, 0), true);
    }
    auto root = head_;
    // do insertion
    while (true) {
        if (root->value_.size() < size_) {
            auto index = root->priority_insert(elem);
            return std::pair<iterator, bool>(btree_iterator<T>(root, index.first), index.second);
        }
        else {
            auto position = root->find_position(elem);
            if(position.second == false) {
                return std::pair<iterator, bool>(btree_iterator<T>(root, position.first), position.second);
            }
            else {
                if(root->children_[position.first] != nullptr) {
                    root = root->children_[position.first];
                } else {
                    auto new_node = std::make_shared<Node>(elem, size_, root);
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
    std::queue<std::shared_ptr<typename btree<T>::Node>>  bfs;
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
