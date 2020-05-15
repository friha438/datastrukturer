/*********************************************
 * file:	~\tnd004\lab\lab4a\digraph.cpp       *
 * remark: implementation of directed graphs  *
 **********************************************/
/*  Frida Hartman, friha438
    Moa Gutenwik, moagu002 */

#include <iostream>
#include <iomanip>
#include <cassert>
#include <limits>

// using namespace std;

#include "digraph.h"
#include "queue.h"

//const int INF = std::numeric_limits<std::size_t>::max();
const int INF = 99999;

// Note: graph vertices are numbered from 1 -- i.e. there is no vertex zero

// -- CONSTRUCTORS

Digraph::Digraph(int n) : size{n}, n_edges{0} {
    assert(n >= 1);

    table.resize(size + 1);
    dist.resize(size + 1);
    path.resize(size + 1);
    done.resize(size + 1);
}

// Create a digraph with n vertices and the edges in V
Digraph::Digraph(const std::vector<std::tuple<int, int, int>> &V, int n) : Digraph{n} {
    for (auto [u, v, w] : V)  // C++17
    {
        insertEdge(u, v, w);
    }
}

// -- MEMBER FUNCTIONS

// insert directed edge (u, v) with weight w
// update weight w if edge (u, v) is present
void Digraph::insertEdge(int u, int v, int w) {
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    table[u].insert(v, w);

    n_edges += 1;
}

// remove directed edge (u, v)
void Digraph::removeEdge(int u, int v) {
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    table[u].remove(v);

    n_edges -= 1;
}

// unweighted single source shortest paths
// *** TODO ***
void Digraph::uwsssp(int s) const {
    if (s < 1 || s > size) {
        std::cout << "\nERROR: expected source s in range 1.." << size << " !\n";
        return;
    }


    for (int i = 0; i <= size ; i++) {
        dist[i] = INF;
        path[i] = 0;
        done[i] = false;
    }

    Queue<int> Q;
    dist[s] = 0;
    Q.enqueue(s);

    while (!Q.isEmpty()) {
        int v = Q.getFront();
        Q.dequeue();
        
        Node* temp = table[v].getFirst(); 
        while (temp != nullptr) {
            if (dist[temp->vertex] == INF) {
                dist[temp->vertex] = dist[v] + 1;
                path[temp->vertex] = v;
                Q.enqueue(temp->vertex);
            }
            temp = temp->next;
        }
    }    
}

int Digraph::find_smallest_undone_distance_vertex() const
{
	// Initialize min value 
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

// positive weighted single source shortest paths
// Dijktra’s algorithm
// *** TODO ***
void Digraph::pwsssp(int s) const {
    if (s < 1 || s > size) {
        cout << "\nERROR: expected source s in range 1.." << size << " !\n";
        return;
    }

    for (int i = 0; i <= size; i++) {
        dist[i] = INF;
        path[i] = 0;
        done[i] = false;
    }

    dist[s] = 0;
    done[s] = true;

    int v = s;
    while(true)
    {
        Node* temp = table[v].getFirst(); 
        while(temp != nullptr)
        {
            if(done[temp->vertex] == false && dist[temp->vertex] > dist[v] + temp->weight)
            {
                dist[temp->vertex] = dist[v] + temp->weight;
                path[temp->vertex] = v;
			}

            temp = table[v].getNext();
            
		}
        v = find_smallest_undone_distance_vertex();
        if (v == 0) break;
        done[v] = true;
	}

}


// print graph
void Digraph::printGraph() const {
    std::cout << "------------------------------------------------------------------\n";
    std::cout << "vertex  adjacency list                  \n";
    std::cout << "------------------------------------------------------------------\n";

    for (int v = 1; v <= size; v++) {
        std::cout << setw(4) << v << " : ";
        table[v].print();
    }

    std::cout << "------------------------------------------------------------------\n";
}

// print shortest path tree for s
void Digraph::printTree() const {
    std::cout << "----------------------\n";
    std::cout << "vertex    dist    path\n";
    std::cout << "----------------------\n";

    for (int v = 1; v <= size; v++) {
        std::cout << std::setw(4) << v << " :" << std::setw(8)
                  << ((dist[v] == std::numeric_limits<int>::max()) ? -1 : dist[v]) << std::setw(8)
                  << path[v] << "\n";
    }

    std::cout << "----------------------\n";
}

// print shortest path from s to t
// *** TODO ***
void Digraph::printPath(int t) const {
    if (t < 1 || t > size) {
        std::cout << "\nERROR: expected target t in range 1.." << size << " !\n";
        return;
    }

    showPath(t);

    cout << " (" << dist[t] << ")";
    
}

 void Digraph::showPath(int t) const {

    if (path[t] != 0) {
        showPath(path[t]);
    }
    cout << setw(5);
    cout << t;
}
