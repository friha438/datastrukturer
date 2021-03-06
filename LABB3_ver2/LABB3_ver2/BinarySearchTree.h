/*  Moa Gutenwik, moagu002
    Frida Hartman, friha438 */

#include <iostream>
#include <iomanip>  //setw
#include <utility>  //std::move

#pragma once

#include "dsexceptions.h"
#include "FrequencyTable.h"

using namespace std;

// BinarySearchTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class BinarySearchTree {
private:
    struct Node;  // nested class defined in node.h

public:
    class Iterator;

    BinarySearchTree() : root{nullptr} {
    }

    /**
     * Copy constructor
     */
    BinarySearchTree(const BinarySearchTree &rhs) : root{nullptr} {
        root = clone(rhs.root);
    }

    /**
     * Destructor for the tree
     */
    ~BinarySearchTree() {
        makeEmpty();
    }

    /**
     * Copy assignment: copy and swap idiom
     */
    BinarySearchTree &operator=(BinarySearchTree _copy) {
        std::swap(root, _copy.root);
        return *this;
    }

    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable &findMin() const {
        if (isEmpty()) {
            throw UnderflowException{};
        }

        return findMin(root)->element;
    }

    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable &findMax() const {
        if (isEmpty()) {
            throw UnderflowException{};
        }

        return findMax(root)->element;
    }

    /**
     * Returns true if x is found in the tree.
     Use the first contains in test 1 and then the 
     second contains in test 2, 3 and Frequency table
     */

    //bool contains(const Comparable &x) const {
    //    return (contains(x, root) != nullptr);
    //}

    Iterator contains(const Comparable& x) const {
        
        if (contains(x, root) != nullptr) return Iterator(contains(x, root));
        else return Iterator(end());
    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty() const {
        return root == nullptr;
    }

    /**
     * Print the tree contents in sorted order.
     */
    void printTree(ostream &out = cout) const {
        if (isEmpty()) {
            out << "Empty tree";
        } else {
            //inorder(root, out);
            int indent = 0;
            preorder(root, out, indent);
        }
    }

    /**
     * Make the tree logically empty.
     */
    void makeEmpty() {
        root = makeEmpty(root);
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert(const Comparable &x) {
        root = insert(x, root);
    }

    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    void remove(const Comparable &x) {
        root = remove(x, root);
    }

    /** Return total number of existing nodes
     *
     * Used for debug purposes
     */
    static int get_count_nodes() {
        return Node::count_nodes;
    }

    /*Finds the Node with the element x and 
    returns the element of the Node's parent*/

    Comparable get_parent(Comparable x) const {
        Node* p = contains(x, root);
        if (p == nullptr) {
            return Comparable{ };
        }
        else {
            if (p->parent == nullptr) {
                return Comparable{}; 
            }
            return p->parent->element;
        }
    }

    /*Finds the predecessor and the successor of the element x
    and returns them as a pair (pred, succ)*/
    
    std::pair<Comparable, Comparable> find_pred_succ(const Comparable& x) const {
        
        if (isEmpty()) {
            throw UnderflowException{};
        }
        std::pair< Comparable, Comparable> predsucc;
        predsucc.first = x;
        predsucc.second = x;

        return find_pred_succ(predsucc, x, root);
    }

    /*Finds the smallest element in the tree and returns 
    an iterator of that Node*/

    Iterator begin() const
    {
        if (isEmpty()) return end();

        return Iterator(findMin(root));
    }

    /*Returns the end of the tree, which is a nullptr*/

    Iterator end() const
    {
        return Iterator(nullptr);
    }


private:
    Node *root;

    /**
     * Private member function to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Return a pointer to the node storing x.
     */
    Node *insert(const Comparable &x, Node *t) {
        if (t == nullptr) {
            t = new Node{ x, nullptr, nullptr, nullptr};
        }
         else if (x < t->element) {
            Node* lchild = insert(x, t->left);
            t->left = lchild;
            lchild->parent = t;
        } else if (t->element < x) {
            Node* rchild = insert(x, t->right);
            t->right = rchild;
            rchild->parent = t;
        } else {
            ;  // Duplicate; do nothing
        }

        return t;
    }

    /**
     * Private member function to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Return a pointer to the new root of the subtree that had root x
     */
    Node *remove(const Comparable &x, Node *t) {
        if (t == nullptr) {
            return t;  // Item not found
        }
        if (x < t->element) {
            t->left = remove(x, t->left);
        } else if (t->element < x) {
            t->right = remove(x, t->right);
        }

        else if (t->left != nullptr && t->right != nullptr)  // Two children
        {
            t->element = findMin(t->right)->element;
            t->right = remove(t->element, t->right);
        } 
        else {
            Node *oldNode = t;
            t = (t->left != nullptr) ? t->left : t->right;
            if (t != nullptr) {
                t->parent = oldNode->parent;
            }
            delete oldNode;
        }

        return t;
    }

    /**
     * Private member function to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    Node *findMin(Node *t) const {
        if (t == nullptr) {
            return nullptr;
        }
        if (t->left == nullptr) {
            return t;
        }

        // Tail recursion can be easily replaced by a loop
        return findMin(t->left);  // recursive call
    }

    /**
     * Private member function to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    Node *findMax(Node *t) const {
        if (t != nullptr) {
            while (t->right != nullptr) {
                t = t->right;
            }
        }

        return t;
    }

    /**
     * Private member function to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the subtree.
     * Return a pointer to the node storing x, if x is found
     * Otherwise, return nullptr
     */
    Node *contains(const Comparable &x, Node *t) const {
        if (t == nullptr) {
            return t;
        } else if (x < t->element) {
            return contains(x, t->left);
        } else if (t->element < x) {
            return contains(x, t->right);
        } else {
            return t;  // Match
        }
    }


    /****** NONRECURSIVE VERSION*************************
    Node *contains(const Comparable &x, Node *t) const {
        while (t != nullptr) {
            if (x < t->element) {
                t = t->left;
            } else if (t->element < x) {
                t = t->right;
            } else {
                return t;  // Match
            }
        }

        return t;  // No match
    }
    *****************************************************/

    /**
     * Private member function to make subtree empty.
     */
    Node *makeEmpty(Node *t) {
        if (t != nullptr) {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        return nullptr;
    }

    /**
     * Private member function to print a subtree rooted at t in sorted order.
     * In-order traversal is used
     */
    void inorder(Node *t, ostream &out) const {
        if (t != nullptr) {
            inorder(t->left, out);
            out << t->element << '\n';
            inorder(t->right, out);
        }
    }

    /**
    * Private member function to print a subtree rooted at t in sorted order.
    * Pre-order traversal is used
    * recently implemented
    */
    
    void preorder(Node *t, ostream& out, int indent) const {    
        if (t != nullptr) {  
            out << setw(indent) << t->element << '\n';
            preorder(t->left, out, indent+3);
            preorder(t->right, out, indent+3);
        }
    }

    /**
     * Private member function to clone subtree.
     */
    Node *clone(Node *t) const {
        if (t == nullptr) {
            return nullptr;
        } else {
            return new Node{t->element, clone(t->left), clone(t->right), t->parent }; //added clone(t->parent)  
        }
    }

    /*Private member function to find predecessor and successor of an element*/

    std::pair<Comparable, Comparable> find_pred_succ(std::pair<Comparable, Comparable> &predsucc, const Comparable& x, Node* t) const {

        if (t == nullptr) return predsucc;

        if (x < t->element) {
            predsucc.second = t->element;
            t = t->left;    
            predsucc = find_pred_succ(predsucc, x, t);
        }
        else if (x > t->element) {
            predsucc.first = t->element;
            t = t->right;
            predsucc = find_pred_succ(predsucc, x, t);
            
        }
        else if (x == t->element) {

            if (t->right != nullptr) {
                predsucc.second = findMin(t->right)->element;
            }
            else if (t->left != nullptr){
                predsucc.first = findMax(t->left)->element;
            }
            else  {
                ; //do nothing, all is well
            }
        }       
        return predsucc;
    }

    /*Private member function to find successor of a node.
    Is called from file iterator.h*/

    Node* find_successor(Node* t) {
        if (t != nullptr && t->right != nullptr) { //if the node has a left subtree
            return findMin(t->right);
        }
        else if (t == nullptr) {
            return nullptr;
        }
        Node* temp = t->parent;
        while (temp != nullptr) //climb up until child is left child of parent
        {               
            if (temp->element > t->element) {
              return temp;
            }
            temp = temp->parent;
        }
        return nullptr; //change to nullptr if strings
    }

    /*Private member function to find successor of a node.
    Is called from file iterator.h*/

    Node* find_predecessor(Node* t) {
        if (t != nullptr && t->left != nullptr) { //if the node has a left subtree
            return findMax(t->left);
        }
        else if (t == nullptr)
        {
            return nullptr;
        }
        Node* temp = t->parent; 
        while (temp != nullptr) //climb up until child is right child of parent
        {
            if (temp->element < t->element) {
                return temp;
            }
            temp = temp->parent;
        }
        return nullptr; 
    }
    
};

//Include the definition of class Node
#include "node.h"
#include "iterator.h"
#include "FrequencyTable.h"
