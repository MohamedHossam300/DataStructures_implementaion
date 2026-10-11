#pragma once

#include <iostream>
#include <stdexcept>

template <class T>

class BST {
private:
  struct Node {
    T value;
    Node *Parent = NULL;
    Node *LChild = NULL, *RChild = NULL;
  };

  Node *_root = NULL;

  int _count = 0;

public:
  int size() { return _count; }

  bool is_empty() { return _count == 0; }

  void insert(T x) {

    if (_root == NULL) {
      _root = new Node();

      _root->value = x;
      _count++;
    } else {
      Node *next = _root;

      while (true) {
        if (x > next->value) {
          if (next->RChild == NULL) {
            next->RChild = new Node();
            next->RChild->value = x;
            next->RChild->Parent = next;
            _count++;
            break;
          } else {
            next = next->RChild;
          }
        } else {
          if (next->LChild == NULL) {
            next->LChild = new Node();
            next->LChild->value = x;
            next->LChild->Parent = next;
            _count++;
            break;
          } else {
            next = next->LChild;
          }
        }
      }
    }
  }

  Node *find_min() {

    if (_root != NULL) {
      Node *next = _root;
      while (true) {
        if (next->LChild == NULL)
          return next;
        else
          next = next->LChild;
      }
    } else {
      return NULL;
    }
  }

  Node *find_max() {

    if (_root != NULL) {
      Node *next = _root;
      while (true) {
        if (next->RChild == NULL)
          return next;
        else
          next = next->RChild;
      }
    } else {
      return NULL;
    }
  }

  Node *find(T x) {
    if (_root == NULL) {
      return NULL;
    } else {
      Node *next = _root;

      while (next != NULL) {
        if (x > next->value)
          next = next->RChild;

        else if (x < next->value)
          next = next->LChild;

        else
          return next;
      }

      return NULL;
    }
  }

  void remove(Node *current) {
    if (current == NULL)
      throw std::runtime_error("Value Doesn't Exists");

    if (current != _root) {
      if (current->Parent->RChild == current) {
        if (current->RChild != NULL && current->LChild != NULL) {
          current->Parent->RChild = current->RChild;
          current->RChild->Parent = current->Parent;

          Node *temp = current->RChild;
          while (temp->LChild != NULL)
            temp = temp->LChild;

          temp->LChild = current->LChild;
          current->LChild->Parent = temp;
        } else if (current->LChild != NULL) {
          current->Parent->RChild = current->LChild;
          current->LChild->Parent = current->Parent;
        } else if (current->RChild != NULL) {
          current->Parent->RChild = current->RChild;
          current->RChild->Parent = current->Parent;
        } else
          current->Parent->RChild = current->LChild;

        delete current;
        _count--;
      }

      else if (current->Parent->LChild == current) {
        if (current->RChild != NULL && current->LChild != NULL) {
          current->Parent->LChild = current->RChild;
          current->RChild->Parent = current->Parent;

          Node *temp = current->RChild;
          while (temp->LChild != NULL)
            temp = temp->LChild;

          temp->LChild = current->LChild;
          current->LChild->Parent = temp;
        } else if (current->LChild != NULL) {
          current->Parent->LChild = current->LChild;
          current->LChild->Parent = current->Parent;
        } else if (current->RChild != NULL) {
          current->Parent->LChild = current->RChild;
          current->RChild->Parent = current->Parent;
        } else
          current->Parent->LChild = current->LChild;

        delete current;
        _count--;
      }
    } else {
      if (current->RChild != NULL && current->LChild != NULL) {
        _root = _root->RChild;

        Node *temp = current->RChild;
        while (temp->LChild != NULL)
          temp = temp->LChild;

        temp->LChild = current->LChild;
        current->LChild->Parent = temp;
        _root->Parent = NULL;
      } else if (current->RChild != NULL) {
        _root = _root->RChild;
        _root->Parent = NULL;
      } else if (current->LChild != NULL) {
        _root = _root->LChild;
        _root->Parent = NULL;
      } else
        _root = NULL;

      delete current;
      _count--;
    }
  }

  void remove(T x) {
    Node *current = find(x);

    if (current == NULL)
      throw std::runtime_error("Value Doesn't Exists");

    remove(current);
  }

  Node *successor(Node *current) {
    if (current == NULL)
      return NULL;

    if (current->RChild != NULL) {
      current = current->RChild;

      while (current->LChild != NULL)
        current = current->LChild;

      return current;
    }

    while (current != _root && current->Parent != NULL &&
           current->Parent->RChild == current)
      current = current->Parent;

    if (current == _root) {
      return NULL;
    }

    return current->Parent;
  }

  Node *successor(T x) {
    Node *current = find(x);

    if (current == NULL)
      throw std::runtime_error("Value Doesn't Exists");

    return successor(current);
  }

  Node *desuccessor(Node *current) {
    if (current == NULL)
      return NULL;

    if (current->LChild != NULL) {
      current = current->LChild;

      while (current->RChild != NULL)
        current = current->RChild;

      return current;
    }

    while (current != _root && current->Parent != NULL &&
           current->Parent->LChild == current)
      current = current->Parent;

    if (current == _root) {
      return NULL;
    }

    return current->Parent;
  }

  Node *desuccessor(T x) {
    Node *current = find(x);

    if (current == NULL)
      throw std::runtime_error("Value Doesn't Exists");

    return desuccessor(current);
  }

  T *inorder() {
    T *arr = new T[_count];
    Node *current = find_min();

    int i = 0;
    while (current != NULL) {
      arr[i++] = current->value;
      current = successor(current);
    }

    return arr;
  }

  void clear() {

    Node *current = find_min();

    while (current != NULL) {
      Node *temp = current;
      current = successor(current);
      remove(temp);
    }
  }

  ~BST() { clear(); }
};
