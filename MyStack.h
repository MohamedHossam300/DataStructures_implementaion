#pragma once

#include "DBLLinkedList.h"
#include <iostream>
#include <stdexcept>

using namespace std;

template <class T> class MyStack {
private:
  DBLLinkedList<T> DBL;

public:
  void push(T value) { DBL.InsertAtBeginning(value); }

  void pop() { DBL.DeleteAtBeginnig(); }

  T Top() {
    if (Size() == 0)
      throw std::out_of_range("The Stack is Empty");
    return DBL.Head()->value;
  }

  void Reverse() { DBL.Reverse(); }

  long long Size() { return DBL.Size(); }

  void print() { DBL.print(); }
};
