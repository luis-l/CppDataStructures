
#include "BinaryMinHeap.h"

int main(){

    BinaryMinHeap<int> pq;

    pq.insert(10);
    pq.insert(12);
    pq.insert(1);
    pq.insert(14);
    pq.insert(6);
    pq.insert(5);
    pq.insert(8);
    pq.insert(15);
    pq.insert(3);
    pq.insert(9);
    pq.insert(7);
    pq.insert(4);
    pq.insert(11);
    pq.insert(13);

    pq.displayLevelOrder();

    cout << endl;
    while(!pq.isEmpty())
        cout << pq.extractMin() << endl;


    return 0;
}
