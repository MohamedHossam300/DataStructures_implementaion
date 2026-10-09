#include "DynamicArray.h"
template <class T> class QueueArr {
private:
  DynamicArray<T> da;

public:
  void push(T value) { da.InsertAtBeginning(value); }
  void pop() { da.pop_back(); }

  T GetItem(long long index) { return da.At(index); }

  T front() { return da.At(0); }
  T back() { return da.At(da.Size() - 1); }

  void Reverse() { da.Reverse(); }

  void Clear() { da.Clear(); }

  void print() { da.print(); }
};
