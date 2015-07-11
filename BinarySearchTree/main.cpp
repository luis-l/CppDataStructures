
#include "BinarySearchTree.h"

int main(){
    srand(time(0));

    BinarySearchTree<int> bst;

    bst.insert(9);

    if(!bst.isEmpty())
        std::cout << bst.displayRootValue() << std::endl << std::endl;

    bst.insert(10);
    bst.insert(5);
    bst.insert(15);
    bst.insert(20);
    bst.insert(40);
    bst.insert(0);

    bst.displayInOrder();

    bst.remove(15);
    bst.remove(20);
    bst.remove(0);
    bst.remove(10);

    bst.insert(100);
    bst.insert(200);
    bst.insert(-100);

    std::cout << std::endl;
    bst.displayInOrder();

    std::cout << std::endl;

    if(!bst.isEmpty()){
        std::cout << "MIN: " << bst.getMin() << std::endl;
        std::cout << "MAX: " << bst.getMax() << std::endl;
    }
    std::cout << "size : " << bst.size() << std::endl;
/*
    std::cout << std::endl;
    bst.clear();

    int limit = 100;
    std::cout << "Inserting " << limit << " random numbers." << std::endl;
    for(int i = 1; i <= limit; ++i)
        bst.insert(rand() % limit);

    bst.insert(70);
    bst.displayInOrder();
    bst.remove(70);
*/
    return 0;
}
