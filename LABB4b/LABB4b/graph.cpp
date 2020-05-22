/*********************************************
 * file:	~\tnd004\lab\lab4b\graph.h        *
 * remark:implementation of undirected graphs *
 **********************************************/

 /*  Frida Hartman, friha438
     Moa Gutenwik, moagu002 */

#include <iostream>
#include <iomanip>
#include <cassert>  //assert
#include <limits>   //std::numeric_limits

// using namespace std;

#include "graph.h"
#include "edge.h"
#include "heap.h"
#include "dsets.h"

const long long int INF = std::numeric_limits<int>::max();

// Note: graph vertices are numbered from 1 -- i.e. there is no vertex zero

// -- CONSTRUCTORS

// Create an empty graph with n vertices
Graph::Graph(int n) : size{n}, n_edges{0} {
    assert(n >= 1);

    table.resize(size + 1);
}

Graph::Graph(const std::vector<std::tuple<int, int, int>> &V, int n) : Graph{n} {
    for (auto [u, v, w] : V)  // C++17
    {
        insertEdge(u, v, w);
    }
}

// -- MEMBER FUNCTIONS

// insert undirected edge (u, v) with weight w
// update weight w if edge (u, v) is present
void Graph::insertEdge(int u, int v, int w) {
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    table[u].insert(v, w);
    table[v].insert(u, w);

    n_edges += 2;
}

// remove undirected edge (u, v)
void Graph::removeEdge(int u, int v) {
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    table[u].remove(v);
    table[v].remove(u);

    n_edges -= 2;
}

int Graph::find_smallest_undone_distance_vertex(const std::vector<int>& dist, const std::vector<int>& done) const{
    int min = INF;
    int min_index = 0;

    for (int v = 1; v <= size; v++) {
        if (done[v] == false && dist[v] <= min) { //if there is a smaller distance
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

// Prim's minimum spanning tree algorithm
void Graph::mstPrim() const {

    std::vector<int> dist(size + 1);
    std::vector<int> path(size + 1);
    std::vector<int> done(size + 1);
    for (int v = 0; v <= size; v++) {
        dist[v] = INF;
        path[v] = 0;
        done[v] = false;
    }
    dist[1] = 0;
    done[1] = true;
    int v = 1;
    int weight_prim = 0;
    while(true)
    {
        Node* temp = table[v].getFirst();
        while (temp != nullptr) {
            if (done[temp->vertex] == false && dist[temp->vertex] > temp->weight) {
                path[temp->vertex] = v;
                dist[temp->vertex] = temp->weight;
            }
            temp = table[v].getNext();            
		}
        v = find_smallest_undone_distance_vertex(dist, done);
        if (v == 0) break; //exit the loop
        done[v] = true;
        weight_prim += dist[v];
        std::cout << "("<<  path[v] << ", " << v << ", " << dist[v] << ")" << std::endl;
	}

    std::cout << std::endl << "Total weight = " << weight_prim << std::endl;
}


// Kruskal's minimum spanning tree algorithm
void Graph::mstKruskal() const {

    Heap<Edge> H(size);
    DSets D(size);
    for (int j = 1; j <= size; j++) {
        Node* temp = table[j].getFirst();

        while (temp != nullptr) {
            if (j < temp->vertex) {
                H.insert(Edge(j, temp->vertex, temp->weight));
            }
            temp = table[j].getNext();
        }
    }

    int counter = 0;
    int counter_weight = 0;
    Edge E;
    while(counter < size - 1) { //n = size
        E = H.deleteMin();
        int v = E.tail;
        int u = E.head;

        if (D.find(u) != D.find(v)) {
            std::cout << "(" << u << ", " << v << ", " << E.weight << ")" << std::endl;
            D.join(D.find(u), D.find(v));
            counter++;
            counter_weight += E.weight;
        }
	} 
    std::cout << std::endl << "Total weight = " << counter_weight << std::endl;
}

// print graph
void Graph::printGraph() const {
    std::cout << "------------------------------------------------------------------\n";
    std::cout << "vertex  adjacency list                                            \n";
    std::cout << "------------------------------------------------------------------\n";

    for (int v = 1; v <= size; v++) {
        std::cout << std::setw(4) << v << " : ";
        table[v].print();
    }

    std::cout << "------------------------------------------------------------------\n";
}
