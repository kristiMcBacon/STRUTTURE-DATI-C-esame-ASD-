#include <iostream>
#include "pnBST.h"
using namespace std;
int main()
{
    //bst <chiave-valore>
    pnBST<int, int> bst;
    //bst.ins_root(0,0);
    bst.insert(21, 21);
    bst.insert(20, 20);
    bst.insert(30, 15);
    bst.insert(5, 5);
    bst.insert(4, 4);
    bst.insert(2, 2);
    bst.insert(22, 22);
    
    bst.modify(30, 99);
    cout << "\nleggi label: " << bst.read_label(bst.search(20)) << endl;
    
    cout << "\n";
    bst.inorder(bst.get_root());
    
    cout << "\nRadice-->"<<bst.read_label(bst.get_root());;
    cout << "\nMinimum    ->"<<bst.read_label(bst.minimum());
    cout << "\nMaximum    ->"<<bst.read_label(bst.maximum());

    cout << "\npredecessor->"<<bst.read_label(bst.predecessor(bst.minimum()));
    cout << "\nsuccessor  ->"<<bst.read_label(bst.successor(bst.minimum()));
    return 0;
}