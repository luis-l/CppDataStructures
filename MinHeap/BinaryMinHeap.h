
#ifndef BINARYMINHEAP_H
#define BINARYMINHEAP_H

#include <iostream>
#include <cassert>
#include <vector>
using std::vector;
using std::cout;
using std::endl;

template<typename T>
class BinaryMinHeap{

    private:
        //container to hold all elements
        vector<T> container;

        //obtains parent/child indexes relative to current index
        int getParentIndex(int currentIndex);
        int getRightChildIndex(int currentIndex);
        int getLeftChildIndex(int currentIndex);

        void swap(T& a, T& b);

        void pushUp();
        void pushDown(int currentIndex, int end);

    public:
        BinaryMinHeap();
        ~BinaryMinHeap();

        void insert(const T& entry);
        T extractMin();

        void updateValue(const T& target);

        int size();
        bool isEmpty();

        void clear();
        void displayLevelOrder();
};

template<typename T>
BinaryMinHeap<T>::BinaryMinHeap(){}

template<typename T>
BinaryMinHeap<T>::~BinaryMinHeap(){}

template<typename T>
void BinaryMinHeap<T>::insert(const T& entry){
    //insert at the end first
    container.push_back(entry);
    pushUp();
}

template <typename T>
T BinaryMinHeap<T>::extractMin(){
    //save min
    T min = container.front();

    int end = container.size() - 1;
    int currentIndex = 0;


    //swap first element with last- and remove last after swap
    swap(container.at(currentIndex), container.at(end));
    container.pop_back();
    end--;

    pushDown(currentIndex, end);

    return min;
}

//Updates an element from the min heap and shifts it accordingly through the heap to
//keep order constraint
template<typename T>
void BinaryMinHeap<T>::updateValue(const T& target){
}

template<typename T>
void BinaryMinHeap<T>::pushDown(int currentIndex, int end){
    while(1){
        int leftIndex = getLeftChildIndex(currentIndex);
        int rightIndex = getRightChildIndex(currentIndex);

        //full node
        if(leftIndex <= end && rightIndex <= end){
            T left = container.at(leftIndex);
            T right = container.at(rightIndex);
            T current = container.at(currentIndex);

            //no violation
            if(current < right && current < left)
                break;

            //find smaller one
            int smaller = (left < right) ? leftIndex : rightIndex;

            //swap with smaller
            swap(container.at(currentIndex), container.at(smaller));
            currentIndex = smaller;

        }
        //only left exist
        else if(leftIndex <= end){
            T left = container.at(leftIndex);
            T current = container.at(currentIndex);

            //no violation
            if(current < left)
                break;

            swap(container.at(currentIndex), container.at(leftIndex));
            currentIndex = leftIndex;
        }
        //no children - we are done
        else break;
    }
}

template<typename T>
void BinaryMinHeap<T>::pushUp(){
    /*check for order constraint- push the entry upwards
        until it its parent is smaller and its children are greater*/
    int currentIndex = container.size() - 1;
    int parentIndex = getParentIndex(currentIndex);

    //keep pushing up until order contraint is satisfied
    while(container.at(currentIndex) < container.at(parentIndex)){
        swap(container.at(currentIndex), container.at(parentIndex));

        currentIndex = parentIndex;
        parentIndex = getParentIndex(currentIndex);
    }
}

template<typename T>
int BinaryMinHeap<T>::size(){
    return container.size();
}

template<typename T>
bool BinaryMinHeap<T>::isEmpty(){
    return container.empty();
}


template<typename T>
void BinaryMinHeap<T>::clear(){
    container.clear();
}

template<typename T>
int BinaryMinHeap<T>::getParentIndex(int currentIndex){
    assert(currentIndex >= 0 && currentIndex < container.size());
    return (currentIndex - 1) / 2;
}

template<typename T>
int BinaryMinHeap<T>::getRightChildIndex(int currentIndex){
    return 2*currentIndex + 2;
}

template<typename T>
int BinaryMinHeap<T>::getLeftChildIndex(int currentIndex){
    return 2*currentIndex + 1;
}

template<typename T>
void BinaryMinHeap<T>::swap(T& a, T& b){
    T temp(a);
    a = b;
    b = temp;
}

template<typename T>
void BinaryMinHeap<T>::displayLevelOrder(){
    for(T e: container)
        cout << e << endl;
}

#endif
