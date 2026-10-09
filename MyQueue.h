#pragma once

#include "DBLLinkedList.h"
#include <iostream>

template <class T> class MyQueue {
private:
  DBLLinkedList<T> DBL;

public:
  void InsertAfter(long long index, T value) {
    DBL.InsertAfter((long long)index, value);
  }

  void Push(T value) { DBL.InsertAtBeginning(value); }

  void pop() { DBL.DeleteAtEnd(); }

  void reverse() { DBL.Reverse(); }

  void Clear() { DBL.Clear(); }

  T Front() {
    if (Size() == 0)
      throw std::out_of_range("The Queyue is Empty");
    return DBL.At(Size() - 1);
  }
  T Back() {
    if (Size() == 0)
      throw std::out_of_range("The Queyue is Empty");
    return DBL.Head->value;
  }

  T &At(long long index) { return DBL.At(index)->value; }

  void UpdateItem(long long index, T value) { At(index) = value; }

  long long Size() { return DBL.Size(); }

  void Print() { DBL.Print(); }
};
