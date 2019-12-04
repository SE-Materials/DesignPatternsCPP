#  Iterator

* Iterator (traversal) is a core functionality of various data structures.
* It is a class that facilitates this traversal.
* * By keeping pointer to an element.
* * Knows how to move to a different element.
* Iterator types
* * Forward (e.g on a list)
* * Bidirectional (e.g on a doubly linked list)
* * Random access (e.g on a vector)


## Iterators in Standard library

### begin, end
### rbegin, rend
### crbegin, crend

## Iterators requirement

### Container member functions

* **beginXxx()** : Points to first element in the container; if empty is equal to `endXxx()` 
* **endXxx()** : Points to element immediately after the last element.
* Facilitates use of standard algorithms
* Allow the use of range-based for loop
` for(auto &x : my_container)`
* Different names for different iterators.


### Iterator operations

* **operator !=** : must return false if two elements point to the same element.
* **operator \*** : (dereferencing) must return reference to (or a copy of) the data the iterator points to 
* **operator ++** : gets the iterator to point to the next element. 
* Additional operators as required (e.g : operator --, arithmetic, etc)

## Binary tree iterator

## Boost iterator facade

```cpp
#include <boost/iterator/iterator_facade.hpp>

struct Node
{
    string value;
    Node* next = nullptr;
    
    explicit Node(const string& value) : value {value}
    {
    }
    
    Node(const string& value, Node* const parent) : value {value}
    {
        parent->next = this;
    }
};

struct ListIterator : boost::iterator_facade<ListIterator, Node, boost::forward_traversal_tag>
{
    Node* current = nullptr;
    
    ListIterator() {}
    
    explicit ListIterator(Node* const current) : current(current)
    {
    }
    
private:
    friend class boost::iterator_core_access;
    
    void increment() { current = current->next; }
    
    bool equal(const ListIterator& other) const
    {
        return other.current == current;
    }
    
    Node& dereference() const
    {
        return *current;
    }
};

// In main

Node alpha {"alpha"};
Node alpha {"beta", &alpha};
Node alpha {"gamma", &beta};

for_each(ListIterator{&alpha}, ListIterator(), 
[](const Node& n){
    cout << n.value << endl;
});

```

## Summary

- An iterator specifies specifies how you can traverse an object.
- Typically needs to support comparison (!=), (++), (*)
- - May support other things.
- can have many iterators (reverse, const etc.)
- - Default one returned in begin()/end()
- Iterators can not be recursive ! 
