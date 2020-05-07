/*  Moa Gutenwik, moagu002
    Frida Hartman, friha438 */

#pragma once

//#include "BinarySearchTree.h"



/* **********************************************************
 * Class to represent a bi-directional iterator for BSTs     *
 * Bi-directional iterators can be moved in both directions, *
 * increasing and decreasing order of items keys             *
 * ***********************************************************/

template <typename Comparable>
class BinarySearchTree<Comparable>::Iterator {
private:
    friend class BinarySearchTree;
    BinarySearchTree bst;

    Node* current;

    Iterator(Node* t) {
        current = t;
    }

public:
    Iterator() : current{ nullptr } { 
    }

    Iterator& operator++() { //pre-increment
        current = bst.find_successor(current);

        return *this;
    }

    Iterator operator++(int) { //post-increment
        Iterator temp = Iterator(current);
        operator++();

        return temp;
    }

    Iterator& operator--() { //pre-decrement
        current = bst.find_predecessor(current);

        return *this;
    }

    Iterator operator--(int) { //post-decrement
        Iterator temp = Iterator(current);
        operator--();

        return temp;
    }

    Comparable& operator*() const {
        return current->element;
    }

    Comparable* operator->() const {
        return &(operator*());
    }

    bool operator==(const Iterator& it) const {
        if (it.current == current) return true;
        else return false;
    }

    bool operator!=(const Iterator& it) const {
        return (!operator==(it));
    }


};


