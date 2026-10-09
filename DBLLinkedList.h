#pragma once

#include <iostream>
#include <stdexcept>

using namespace std;

template <class T> class DBLLinkedList {
public:
  struct Node {
    T value;
    Node *next, *prev;
  };

private:
  long long _size = 0;
  Node *_Head = NULL;

  void _swapPrevAndNext(Node *node) {
    Node *temp = node->next;
    node->next = node->prev;
    node->prev = temp;
  }

public:
  Node *Head() { return _Head; }
  long long Size() { return _size; }
  bool isEmpty() { return _size == 0; }

  enum enOperationState { NULLError, Success };

  // Insert
  void InsertAtBeginning(T value) {
    Node *newNode = new Node;

    newNode->value = value;
    newNode->prev = NULL;

    if (_Head == NULL)
      newNode->next = NULL;
    else {
      newNode->next = _Head;
      _Head->prev = newNode;
    }
    _Head = newNode;
    _size++;
  }

  enOperationState InsertAfter(Node *node, T value) {
    if (node == NULL)
      return enOperationState::NULLError;
    else {
      Node *newNode = new Node;
      newNode->value = value;

      newNode->next = node->next;
      if (node->next != NULL)
        node->next->prev = newNode;
      node->next = newNode;

      newNode->prev = node;
      _size++;
      return enOperationState::Success;
    }
  }

  enOperationState InsertAfter(long long index, T value) {
    return InsertAfter(At(index), value);
  }

  void InsertAtEnd(T value) {
    Node *newNode = new Node;

    newNode->value = value;
    newNode->next = NULL;

    if (_Head == NULL) {
      _Head = newNode;
      newNode->prev = NULL;
      _size++;
      return;
    }

    Node *CurrentNode = _Head;

    while (CurrentNode->next != NULL)
      CurrentNode = CurrentNode->next;

    CurrentNode->next = newNode;
    newNode->prev = CurrentNode;
    _size++;
  }

  // Delete
  enOperationState Delete(Node *node) {
    if (node == NULL)
      return enOperationState::NULLError;

    if (_Head == node) {
      _Head = node->next;
      if (node->next != NULL)
        node->next->prev = NULL;
      delete node;

      _size--;
      return Success;
    }

    node->prev->next = node->next;
    if (node->next != NULL)
      node->next->prev = node->prev;

    delete node;
    _size--;
    return enOperationState::Success;
  }

  enOperationState Delete(long long index) { return Delete(At(index)); }

  enOperationState DeleteAtBeginnig() {

    if (_Head == NULL)
      return enOperationState::NULLError;

    Node *CurrentNode = _Head;
    _Head = _Head->next;

    if (_Head != NULL)
      _Head->prev = NULL;

    delete CurrentNode;

    _size--;
    return enOperationState::Success;
  }

  enOperationState DeleteAtEnd() {
    if (_Head == NULL)
      return enOperationState::NULLError;

    Node *CurrentNode = _Head;
    while (CurrentNode->next != NULL)
      CurrentNode = CurrentNode->next;

    if (CurrentNode != _Head)
      CurrentNode->prev->next = NULL;
    else
      _Head = NULL;

    delete CurrentNode;
    _size--;
    return enOperationState::Success;
  }

  // Find
  Node *Find(T value) {
    if (_Head != NULL) {
      Node *CurrentNode = _Head;

      while (CurrentNode != NULL && CurrentNode->value != value)
        CurrentNode = CurrentNode->next;

      if (CurrentNode != NULL && CurrentNode->value == value)
        return CurrentNode;
    }

    return NULL;
  }

  Node *At(long long index) {
    if (index < 0 || index >= _size)
      throw std::out_of_range("Index out of range");

    Node *CurrentNode = _Head;
    long long counter = 0;
    while (CurrentNode->next != nullptr && counter != index) {
      CurrentNode = CurrentNode->next;
      counter++;
    }

    return CurrentNode;
  }

  T &GetItem(long long index) { return At(index)->value; }
  T &UpdateItem(long long index, T value) { return At(index)->value = value; }

  void Reverse() {
    if (_Head != NULL) {
      while (_Head->next != NULL) {
        _swapPrevAndNext(_Head);
        _Head = _Head->prev;
      }

      _swapPrevAndNext(_Head);
    }
  }

  void Clear() {
    if (_Head != NULL) {
      Node *CurrentNode = _Head;

      while (CurrentNode->next != NULL) {
        CurrentNode = CurrentNode->next;
        delete CurrentNode->prev;
      }
      delete CurrentNode;

      _Head = NULL;
      _size = 0;
    }
  }

  void Print() {
    Node *CurrentNode = _Head;
    while (CurrentNode != NULL) {
      cout << CurrentNode->value << ' ';
      CurrentNode = CurrentNode->next;
    }
    cout << '\n';
  }

  ~DBLLinkedList() { Clear(); }
};
