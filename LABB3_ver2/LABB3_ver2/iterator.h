//#include <iostream>
#include "BinarySearchTree.h"
//#include "node.h"

#pragma once

/* **********************************************************
 * Class to represent a bi-directional iterator for BSTs     *
 * Bi-directional iterators can be moved in both directions, *
 * increasing and decreasing order of items keys             *
 * ***********************************************************/

template <typename Comparable>
class BinarySearchTree<Comparable>::Iterator {
private:
    Node* current;

    Iterator(Node* p = nullptr) : current{ p } {};


public:
    Iterator() {
    }

    Comparable& operator*() const;
    Comparable* operator->() const;
    bool operator==(const Iterator& it) const;
    bool operator!=(const Iterator& it) const;
    Iterator& operator++(); //pre-increment
    Iterator& operator--(); //pre-decrement


private:

    Node* find_successor(Node* t) {
        if (t != nullptr && t->right != nullptr) {
            return findMin(t->right);
        }
        else {
            Node* p = t->parent;
            while (p != nullptr && t == p->right)
            {
                t = p;
                p = p->parent;
            }
            return p;
            //start loop {
            //climb to parent
            //check that last node was right child
            // }
            //exits loop when child is left child
            //returns the value in the current iterator
        }
    }
};


