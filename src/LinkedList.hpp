#pragma once
#include <ctype.h>

template<typename T> // Because typedefs suck for this.
class LinkedList {
public:
  using ElementType = T;
  LinkedList();
  ~LinkedList();

  const T& get(unsigned index);

  void insert(T newEle, unsigned index);
  void insertSorted(T newEle);

  void erase(unsigned index);

  void sort();

private:
  struct Node {
    T data;
    Node* next;
  };

  Node* first;

};
