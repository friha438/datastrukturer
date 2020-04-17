#include "set.h"
#include "node.h"

int Set::Node::count_nodes = 0;  // initialize total number of existing nodes to zero

/*****************************************************
 * Implementation of the member functions             *
 ******************************************************/

// Used for debug purposes
// Return number of existing nodes
int Set::get_count_nodes() {
    return Set::Node::count_nodes;
}

void Set::remove(Node* temp)
{
    temp->prev->next = temp->next;

    temp->next->prev = temp->prev;
   
    counter--;
    delete temp;

}

// Default constructor
Set::Set() : head{ new Node(0, nullptr, nullptr) }, tail{ new Node(0, nullptr, head) }, counter{ 0 } 
{
    head->next = tail;
}

// Conversion constructor
Set::Set(int n)
    : Set{}  // create an empty list
{
    Node* newNode = new Node(n, tail, head); 

    tail->prev = newNode;
    head->next = newNode;
    counter++;
}

// Constructor to create a Set from a sorted vector v
Set::Set(const std::vector<int>& v)
    : Set{}  // create an empty list
{

    for (int i = 0; i < v.size(); i++)
    {
        
        Node* temp = new Node(v[i], tail, tail->prev);
        tail->prev->next = temp;
        tail->prev = temp;
        
        
        counter++;
    }
}


// Make the set empty
void Set::make_empty() {

    Node* current = head->next;

    while (current != tail)
    {
        Node* temp = current;

        current = current->next;
        delete temp;
        
    }

    counter = 0;

    head->next = tail;
    tail->prev = head;
    current = nullptr;
   
}

Set::~Set() {
    
    Set::make_empty();
     
    counter = 0;
    
    delete head;
    delete tail;
   
}

// Copy constructor
Set::Set(const Set& source)
    : Set{}  // create an empty list
{
    Node* temp = source.head->next;

    while (temp != source.tail) {
       // p->next = new Node(temp->value, tail, tail->prev);

        Node* p = new Node(temp->value, tail, tail->prev);
        tail->prev->next = p;
        tail->prev = p;
        temp = temp->next;

        counter++;
    }

}

// Copy-and-swap assignment operator
Set& Set::operator=(Set source) {

    std::swap(head, source.head);
    std::swap(tail, source.tail);
    std::swap(counter, source.counter);

    return *this;
}

// Test whether a set is empty
bool Set::is_empty() const {
    return (counter == 0);
}

// Test set membership
bool Set::is_member(int val) const {
    Node* temp = head;

    while ((temp != tail) && (temp->value != val)) {
        temp = temp->next;
    }

    if (temp == tail) {
        return false;
    }
    else {
        return true;
    }

}

// Return number of elements in the set
size_t Set::cardinality() const {
    return counter;
}

// Return true, if the set is a subset of b, otherwise false
// a <= b iff every member of a is a member of b
bool Set::operator<=(const Set& b) const {
    
    Node* p1 = head->next;
    Node* p2 = b.head->next;

    if (p2 == b.tail && p1 == tail) {
        return true;
    }
    
    while (p2 != b.tail)
    {
        if (p1->value == p2->value)
        {
            p1 = p1->next;
            if (p1 == tail) return true;
       
        }
        else if (p1->value < p2->value)
        {
            //p2 = p2->next;
            //p1 = p1->next;
            return false;
        }

        p2 = p2->next;

    }
    return false;

}

// Return true, if the set is equal to set b
// a == b, iff a <= b and b <= a
bool Set::operator==(const Set& b) const {
   
    if (*this <= b && b <= *this) return true;
    return false;

}

// Return true, if the set is different from set b
// a == b, iff a <= b and b <= a
bool Set::operator!=(const Set& b) const {

    if (!(operator<=(b) && operator<=(*this))) return true;
    else return false;

}

// Return true, if the set is a strict subset of S, otherwise false
// a == b, iff a <= b but not b <= a
bool Set::operator<(const Set& b) const {

        if(b.operator<=(*this) && !b.operator==(*this)) return true;
        else return false;

}

// Modify *this such that it becomes the union of *this with Set S
// Add to *this all elements in Set S (repeated elements are not allowed)
Set& Set::operator+=(const Set& S) {
    
    Node* pointS = S.head->next;
    Node* t = head->next;
    
    // Merge S1 with S2
    while (t != (*this).tail && pointS != S.tail) {
        if (t->value < pointS->value) {
            t = t->next;          
            
        }
        else if (pointS->value < t->value) {
            Node* p = new Node(pointS->value, t, t->prev);
            t->prev = t->prev->next = p;
            pointS = pointS->next;
            
        }
        else  // S1[count1] == S2[count2]
        {
            t = t->next;
            pointS = pointS->next;
            
        }
    }

    // copy any remaining values from S2 to S3
    while (pointS != S.tail) {
        Node* p = new Node(pointS->value, t, t->prev);
        t->prev = t->prev->next = p;
        pointS = pointS->next;
        
    }

    return *this;
}

// Modify *this such that it becomes the intersection of *this with Set S
Set& Set::operator*=(const Set& S) {
    // IMPLEMENT
    Node* pointS = S.head->next;
    Node* t = head->next;


    while (t != (*this).tail && pointS != S.tail) {
        if (t->value < pointS->value) {
            t = t->next;

        }
        else if (pointS->value < t->value) {
            //Node* p = new Node(pointS->value, t, t->prev);
            //t->prev = t->prev->next = p;
            pointS = pointS->next;

        }
        else  // S1[count1] == S2[count2]
        {
            Node* p = t;
            t = t->next;
            pointS = pointS->next;
            remove(p);
        }
    }

    return *this;
}

// Modify *this such that it becomes the Set difference between Set *this and Set S
Set& Set::operator-=(const Set& S) {

    Node* pointS = S.head->next;
    Node* t = head->next;


    while (t != (*this).tail && pointS != S.tail) {
        if (t->value < pointS->value) {
            t = t->next;

        }
        else if (pointS->value < t->value) {
            //Node* p = new Node(pointS->value, t, t->prev);
            //t->prev = t->prev->next = p;
            pointS = pointS->next;

        }
        else  // S1[count1] == S2[count2]
        {
            Node* p = t;
            t = t->next;
            pointS = pointS->next;
            remove(p);
        }
    }

    return *this;
}

// Overloaded stream insertion operator<<
std::ostream& operator<<(std::ostream& os, const Set& b) {
    if (b.is_empty()) {
        os << "Set is empty!";
    } else {
        Set::Node* temp{b.head->next};

        os << "{ ";
        while (temp != b.tail) {
            os << temp->value << " ";
            temp = temp->next;
        }

        os << "}";
    }

    return os;
}

/* ******************************************** *
 * Private Member Functions -- Implementation   *
 * ******************************************** */

//If you add any private member functions to class Set then write the implementation here

/*
    Set R{ };
    Node* pointS = S.head->next;
    Node* p = R.head->next;
    Node* t = head->next;

    // Merge S1 with S2
    while (t != (*this).tail && pointS != S.tail) {
        if (t->value < pointS->value) {
            //std::cout << t->value << std::endl;
            p = new Node(t->value, tail, tail->prev);
            p->next = p->next->prev;
            p->prev = p->next;
            std::cout << p->value << std::endl;
            t = t->next;
            p = p->next;

        }
        else if (pointS->value < t->value) {
            //std::cout << pointS->value << std::endl;
            p = new Node(pointS->value, tail, tail->prev);
            p->next = p->next->prev;
            p->prev = p->next;
            std::cout << p->value << std::endl;
            p = p->next;
            pointS = pointS->next;

        }
        else  // S1[count1] == S2[count2]
        {
            //std::cout << t->value << std::endl;
            p = new Node(t->value, tail, tail->prev);
            p->next = p->next->prev;
            p->prev = p->next;
            std::cout << p->value << std::endl;
            p = p->next;
            t = t->next;
            pointS = pointS->next;

        }
    }

    // copy any remaining values from S1 to S3
    while (t != (*this).tail) {
        //std::cout << t->value << std::endl;
        p = new Node(t->value, tail, tail->prev);
        p->next = p->next->prev;
        p->prev = p->next;
        std::cout << p->value << std::endl;
        t = t->next;
        p = p->next;

    }

    // copy any remaining values from S2 to S3
    while (pointS != S.tail) {
        //std::cout << pointS->value << std::endl;
        p = new Node(pointS->value, tail, tail->prev);
        p->next = p->next->prev;
        p->prev = p->next;
        std::cout << p->value << std::endl;
        p = p->next;
        pointS = pointS->next;

    }

    return R;
*/
