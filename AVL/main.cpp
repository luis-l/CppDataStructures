
#include "AVL.h"
#include "BinarySearchTree.h"

int main(){
    srand(time(0));
    AVL<int> avl;

    avl.insert(4);
    avl.insert(2);
    avl.insert(6);
    avl.insert(3);
    avl.insert(0);
    avl.insert(5);
    avl.insert(1);
    avl.insert(7);
    avl.insert(-1);
    avl.insert(8);

    avl.displayLevelOrder();

    return 0;
}

