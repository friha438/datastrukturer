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
    Node* current;

public:
    BinarySearchTree::Iterator() : current{ nullptr } { //BST??
    }

    Iterator(Node* t) {
        current = t;
    }

    Iterator& operator++() { //pre-increment
        current = find_successor(current);

        return *this;
    }

    Iterator& operator--() { //pre-decrement
        current = find_predecessor(current);

        return *this;
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



private:


    Node* find_successor(Node* t) {
        if (t != nullptr && t->right != nullptr) {
            return findMin(t->right);
        }
        else {
            while (t->parent != nullptr && t == t->parent->right)
            {
                t = t->parent;
            }
            return t->parent;
            
            //start loop {
            //climb to parent
            //check that last node was right child
            // }
            //exits loop when child is left child
            //returns the value in the current iterator
        }

        //while (t->parent != nullptr)
        //{
        //    if (t->parent->element > t->element) {
        //        return t->parent;
        //    }

        //    t = t->parent;
        //}
        //return nullptr; //change to nullptr if strings
    }

    Node* find_predecessor(Node* t) {
        if (t != nullptr && t->left != nullptr) {
            return findMin(t->left);
        }
        else {
            while (t->parent != nullptr && t == t->parent->left)
            {
                t = t->parent;
            }
            return t->parent;
        }
    }


    Node* findMin(Node* t) const
    {
        while (t->left)
            t = t->left;
        return t;
    }

    Comparable& operator*(Node* current) {
        return current->element;
    }
};


