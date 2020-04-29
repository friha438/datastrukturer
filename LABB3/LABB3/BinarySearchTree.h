#include <iostream>
#include <iomanip>  //setw
#include <utility>  //std::move

#pragma once

#include "dsexceptions.h"

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
     */
    bool contains(const Comparable &x) const {
        return (contains(x, root) != nullptr);
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

    Comparable get_parent(Comparable x) const {
        Node* p = contains(x, root);
        //std::cout << p->parent->element << std::endl;
        if (p == nullptr) {
            //create a comparable??
            return Comparable{ };
        }
        else {
            if (p->parent == nullptr) {
                return Comparable{}; 
            }

            return p->parent->element;
        }
    }

    //Node* find(const Comparable& x, Node* t) const {
    //    if (isEmpty()) {
    //        throw UnderflowException{};
    //    }
    //    if (t == nullptr) {
    //        return t;
    //    }
    //    else if (x < t->element) {
    //        return contains(x, t->left);
    //    }
    //    else if (t->element < x) {
    //        return contains(x, t->right);
    //    }
    //    else {
    //        return t;  // Match
    //    }
    //}

    //Node*& find(const Comparable& element) const {
    //    if (isEmpty()) {
    //        throw UnderflowException{};
    //    }
    //    Node* t = root;
    //    while (element != t->element)
    //    {
    //        if (element < t->element) {
    //            t = t->left;
    //        }
    //        else if (t->element < element) {
    //            t = t->right;
    //        }
    //    }
    //    return t;
    //}


    
    std::pair< Comparable, Comparable> find_pred_succ(const Comparable& x) const {
        
        return find_pred_succ(x, root);
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

    std::pair< Comparable, Comparable> find_pred_succ(const Comparable& x, Node* t) const {

        Comparable pred;
        Comparable succ;

        /*if (t->element == x) {
            pred = t->left->element;
            succ = t->right->element;
        }*/
        if (x < t->element) {
            succ = t->element;
            t = t->left;    
            find_pred_succ(x, t);
        }
        else if (x > t->element) {
            pred = t->element;
            t = t->right;
            find_pred_succ(x, t);
        }
        else if (x == t->element) {

            if (t->left != nullptr && t->right != nullptr) {
                pred = t->left->element;
                succ = t->right->element;
            }

            else if (t->right != nullptr) {
                succ = t->right->element;
            }
            else if (t->left != nullptr){
                pred = t->left->element;
            }
            else  {
                ; //do nothing all is well
            }

        }

        //vi har inte tänkt den här tanken till slut

        return { pred, succ };
    }

    
};

//Include the definition of class Node
#include "node.h"

        /*
        if (x < root->element) {
            Node* succ = n->parent;
            if (t != nullptr && t->right != nullptr) {
                succ = findMin(t->right);
            }
            while (succ != nullptr && n == succ->right)
            {
                n = succ;
                succ = succ->parent;
            }
        }
        else if ( x > root->element ) {
            Node* pred = n->parent;
            if (t != nullptr && t->left != nullptr) {
                pred = findMax(t->left);
            }
            while (pred != nullptr && n == pred->left)
            {
                n = pred;
                pred = pred->parent;
            }
        }*/