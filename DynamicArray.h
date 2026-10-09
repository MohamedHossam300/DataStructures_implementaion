#pragma once

#include <iostream>
#include <iterator>
#include <memory>
#include <stdexcept>

using namespace std;

template <class T> class DynamicArray {
private:
  long long _capacity;
  long long _size;
  const int npos = -1;
  T *_arr;

public:
  DynamicArray(long long n = 0) {
    if (n < 0)
      throw invalid_argument("Size can't be negative");
    _size = n;
    _capacity = n * 1.3;
    _arr = new T[_capacity];
  }

  long long Size() { return _size; }

  bool isEmpty() { return _size == 0; }

  T &At(long long index) {
    if (index < 0 || index >= Size())
      throw std::out_of_range("This Index is out of range");
    return _arr[index];
  }

  long long Find(T value) {
    for (int i = 0; i < _size; i++)
      if (_arr[i] == value)
        return i;

    return npos;
  }

  void pop_back() {
    if (_size > 0)
      _size--;
  }

  void pop_front() {
    if (_size > 0) {
      for (int i = 0; i < _size - 1; i++) {
        _arr[i] = _arr[i + 1];
      }
      _size--;
    }
  }

  void DeleteItemAt(long long index) {
    if (index < 0 || index >= _size)
      throw std::out_of_range("This index is out of range");
    T *newArr = new T[_capacity];

    for (long long i = 0; i < index; i++)
      newArr[i] = _arr[i];

    for (long long i = index + 1; i < _size; i++)
      newArr[i - 1] = _arr[i];

    delete[] _arr;
    _arr = newArr;
    _size = _size - 1;
  }

  enum enDeletingState { NotFound, Success };
  enDeletingState DeleteItem(T value) {
    long long index = Find(value);
    if (index == npos)
      return enDeletingState::NotFound;

    DeleteItemAt(index);
    return enDeletingState::Success;
  }

  void Resize(long long n) {
    if (n < 0)
      throw invalid_argument("Size can't be negative");

    if (n > _capacity) {
      _capacity = n * 1.3;
      T *newArr = new T[_capacity];
      for (long long i = 0; i < min(_size, n); i++)
        newArr[i] = _arr[i];

      delete[] _arr;
      _size = n;
      _arr = newArr;
    } else {
      _size = n;
    }
  }

  void InsertAt(long long index, T value) {
    if (index >= _size || index < 0)
      throw std::out_of_range("index is out of range");

    Resize(_size + 1);
    for (long long i = _size - 1; i > index; i--)
      _arr[i] = _arr[i - 1];

    _arr[index] = value;
  }

  void InsertAtBeginning(T value) { InsertAt(0, value); }
  void InsertAfter(long long index, T value) { InsertAt(index + 1, value); }
  void InsertBefore(long long index, T value) { InsertAt(index - 1, value); }
  void InsertAtEnd(T value) { InsertAt(_size - 1, value); }

  void Reverse() {
    T *temp_arr = new T[_capacity];
    for (int i = 0; i < _size; i++)
      temp_arr[i] = _arr[_size - 1 - i];

    delete[] _arr;
    _arr = temp_arr;
  }

  void Clear() {
    delete[] _arr;
    _arr = new T[0];
    _size = 0;
    _capacity = 0;
  }

  void operator=(const T arr[]) {
    for (long long i = 0; i < _size; i++)
      At(i) = arr[i];
  }

  void print() {
    for (long long i = 0; i < _size; i++)
      cout << At(i) << ' ';
  }

  ~DynamicArray() { delete[] _arr; }
};
