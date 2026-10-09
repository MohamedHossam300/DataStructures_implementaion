#include "BST.h"

using namespace std;

int main() {
  BST<int> bst;

  bst.insert(3);
  bst.insert(5);
  bst.insert(4);
  bst.insert(1);
  bst.insert(10);
  bst.insert(7);
  bst.insert(100);

  cout << bst.successor(bst.find_min())->value << endl;

  bst.remove(100);

  int *arr = bst.inorder();

  for (int i = 0; i < bst.size(); i++)
    cout << arr[i] << ' ';

  cout << endl;

  cout << bst.size() << endl;
  cout << bst.find_max()->value << endl;
  cout << bst.find_min()->value << endl;
  cout << bst.find(90) << endl;
}
