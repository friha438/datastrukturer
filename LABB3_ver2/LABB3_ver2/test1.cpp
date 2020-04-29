#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cassert>  //assert

#include "binarysearchtree.h"

int main() {
    /*************************************************/
    std::cout << "phase 0: insert, printtree, ";
    std::cout << "findmin, findmax\n\n";
    /*************************************************/
    {
        binarysearchtree<int> t;
        assert(binarysearchtree<int>::get_count_nodes() == 0);

        std::vector<int> v = {20, 10, 30, 5, 15, 35, 25, 12, 14, 33};

        for (auto j : v) {
            t.insert(j);
        }

        assert(binarysearchtree<int>::get_count_nodes() == 10);

        // display the tree
        std::cout << "tree: \n";
        t.printtree();
        std::cout << '\n';

        assert(t.findmin() == 5);
        assert(t.findmax() == 35);
    }
    assert(binarysearchtree<int>::get_count_nodes() == 0);

    /**************************************/
    std::cout << "\nphase 1: contains\n";
    /**************************************/
    {
        binarysearchtree<int> t;
        assert(binarysearchtree<int>::get_count_nodes() == 0);

        std::vector<int> v = {20, 10, 30, 5, 15, 35, 25, 12, 14, 33};

        for (auto j : v) {
            t.insert(j);
        }

        assert(binarysearchtree<int>::get_count_nodes() == 10);

        // uncomment this part if contains() returns a bool -- exercise 1
        // otherwise, comment it away
        std::vector<int> v1{2, 4, 6, 8, 16, 18, 22, 24, 26, 28, 52};

        for (auto j : v1) {
            assert(t.contains(j) == false);
        }

        std::vector<int> v2{10, 12, 14, 20, 30, 33, 35};

        for (auto j : v2) {
            assert(t.contains(j));
        }

        /* **************************** */

        // uncomment this part if contains() returns an iterator -- exercise 2
        // otherwise, comment it away
        /*std::vector<int> v1{2, 4, 6, 8, 16, 18, 22, 24, 26, 28, 52};

        for (auto j : v1) {
            assert(t.contains(j) == t.end());
        }

        std::vector<int> v2{10, 12, 14, 20, 30, 33, 35};

        for (auto j : v2) {
            assert(*t.contains(j) == j);
        }*/
    }

    assert(binarysearchtree<int>::get_count_nodes() == 0);

    /***********************************************/
    std::cout << "\nphase 2: copy constructor\n";
    /***********************************************/
    {
        binarysearchtree<int> t1;
        assert(binarysearchtree<int>::get_count_nodes() == 0);

        std::vector<int> v = {20, 10, 30, 5, 15, 35, 25, 12, 14, 33};

        for (auto j : v) {
            t1.insert(j);
        }

        assert(binarysearchtree<int>::get_count_nodes() == 10);

        binarysearchtree<int> t2{t1};

        assert(binarysearchtree<int>::get_count_nodes() == 20);

        // compare trees t1 and t2 -- should be equal
        std::ostringstream os1;
        std::ostringstream os2;

        t1.printtree(os1);
        t2.printtree(os2);
        assert(os1.str() == os2.str());
    }

    assert(binarysearchtree<int>::get_count_nodes() == 0);

    /**************************************/
    std::cout << "\nphase 3: makeempty\n";
    /**************************************/
    {
        binarysearchtree<int> t;
        assert(binarysearchtree<int>::get_count_nodes() == 0);

        std::vector<int> v = {20, 10, 30, 5, 15, 35, 25, 12, 14, 33};

        for (auto j : v) {
            t.insert(j);
        }

        assert(binarysearchtree<int>::get_count_nodes() == 10);

        t.makeempty();
        assert(binarysearchtree<int>::get_count_nodes() == 0);

        std::ostringstream os;
        t.printtree(os);
        assert(os.str() == "empty tree");
    }

    assert(binarysearchtree<int>::get_count_nodes() == 0);

    /**************************************/
    std::cout << "\nphase 4: operator=\n";
    /**************************************/
    {
        binarysearchtree<int> t1;
        assert(binarysearchtree<int>::get_count_nodes() == 0);

        std::vector<int> v1 = {20, 10, 30, 5, 15, 35, 25, 12, 14, 33};

        for (auto j : v1) {
            t1.insert(j);
        }

        assert(binarysearchtree<int>::get_count_nodes() == 10);

        std::ostringstream os1;
        t1.printtree(os1);

        t1 = t1;  // self-assignment

        assert(binarysearchtree<int>::get_count_nodes() == 10);

        std::ostringstream os2;
        t1.printtree(os2);
        assert(os1.str() == os2.str());

        /* ********************* */

        binarysearchtree<int> t2;
        std::vector<int> v2 = {33, -6, 8};

        for (auto j : v2) {
            t2.insert(j);
        }

        assert(binarysearchtree<int>::get_count_nodes() == 13);

        t2 = t1;

        assert(binarysearchtree<int>::get_count_nodes() == 20);

        // compare trees t1 and t2 -- should be equal
        std::ostringstream os3;

        t2.printtree(os3);
        assert(os1.str() == os3.str());
    }

    assert(binarysearchtree<int>::get_count_nodes() == 0);

    /**************************************/
     std::cout << "\nphase 5: get_parent\n";
    /**************************************/
    {
        binarysearchtree<int> t;
        assert(binarysearchtree<int>::get_count_nodes() == 0);

        std::vector<int> v = {20, 10, 30, 5, 15, 35, 25, 12, 14, 33};

        for (auto j : v) {
            t.insert(j);
        }

        assert(binarysearchtree<int>::get_count_nodes() == 10);


        assert(t.get_parent(14) == 12);
        assert(t.get_parent(10) == 20);
        assert(t.get_parent(33) == 35);      
        assert(t.get_parent(20) == 0);
        assert(t.get_parent(28) == 0);

    }
    
     assert(binarysearchtree<int>::get_count_nodes() == 0);

    /**************************************/
    std::cout << "\nphase 6: remove\n";
    /**************************************/
    {
        binarysearchtree<int> t;
        assert(binarysearchtree<int>::get_count_nodes() == 0);

        std::vector<int> v = {20, 10, 30, 5, 15, 35, 25, 12, 14, 33};

        for (auto j : v) {
            t.insert(j);
        }

        assert(binarysearchtree<int>::get_count_nodes() == 10);

        for (int i = 0; i < 35; i += 2) {
            t.remove(i);
        }

        assert(binarysearchtree<int>::get_count_nodes() == 5);

        // uncomment this part if contains() returns a boolean -- exercise 1
        // otherwise, comment it away
        std::vector<int> v1{10, 12, 14, 20, 30};

        for (auto j : v1) {
            assert(t.contains(j) == false);
        }

        std::vector<int> v2{5, 15, 25, 33, 35};

        for (auto j : v2) {
            assert(t.contains(j));
        }
        /* ********************* */

        // uncomment this part if contains() returns an iterator -- exercise 2
        // otherwise, comment it away
        /* std::vector<int> v1{10, 12, 14, 20, 30};

         for (auto j : v1) {
             assert(t.contains(j) == t.end());
         }

         std::vector<int> v2{5, 15, 25, 33, 35};

         for (auto j : v2) {
             assert(*t.contains(j) == j);
         }*/
    }

    assert(binarysearchtree<int>::get_count_nodes() == 0);

    /*****************************************************/
     std::cout << "\nphase 7: get_parent after remove\n";
    /*****************************************************/
    /* test pointers to the parent node after the remove */

    {
        binarysearchtree<int> t;
        assert(binarysearchtree<int>::get_count_nodes() == 0);

        std::vector<int> v = {20, 10, 30, 5, 15, 35, 25, 12, 14, 33};

        for (auto j : v) {
            t.insert(j);
        }

        assert(binarysearchtree<int>::get_count_nodes() == 10);

        // remove some nodes
        for (int i = 0; i < 35; i += 2) {
            t.remove(i);
        }

        assert(binarysearchtree<int>::get_count_nodes() == 5);

        assert(t.get_parent(5) == 15);
        
        assert(t.get_parent(15) == 25);
        assert(t.get_parent(25) == 0);
        assert(t.get_parent(33) == 35);
        assert(t.get_parent(35) == 25);
        
    }

    assert(binarysearchtree<int>::get_count_nodes() == 0);

    std::cout << "\nsuccess!!\n";
} 