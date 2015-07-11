
#ifndef STACKLL_H
#define STACKLL_H

#include "doublyLinkedList.h"

template<typename T>
class StackLL{

    //display
    friend std::ostream& operator<<(std::ostream& os, const StackLL& s){
        os << s.container;
        return os;
    }

    private:
        DoublyLinkedList<T> container;


    public:
        void push(const T& entry);
        const T pop();
        const int size() const;
        bool empty() const;

        //////////////////////////////
        //additional "weird" methods:
        //////////////////////////////

        //remove and return the kth item from the top of the stack.
        T popkth(int k);

        //decimate: remove every 10th item from the stack
        void decimate();

        //add entry to stack, but insert it
        //right after the current ith item from the top
        //(and before the i+1 item).
        void insertAt(const T& entry, int i);
};

template<typename T>
void StackLL<T>::push(const T& entry){
    container.addFront(entry);
}

template<typename T>
const T StackLL<T>::pop(){
    const T temp = container.getFront();
    container.removeFront();
    return temp;
}

template<typename T>
const int StackLL<T>::size() const{
    return container.size();
}

template<typename T>
bool StackLL<T>::empty() const{
    return container.isEmpty();
}

template<typename T>
T StackLL<T>::popkth(int k){
    T temp;
    int counter = 0;
    typename DoublyLinkedList<T>::Iterator itr;
    for(itr = container.begin(); itr != container.end(); itr++){
        if(counter == k){
            temp = itr.peek();
            container.removeAt(itr);
            break;
        }
        ++counter;
    }
    return temp;
}

template<typename T>
void StackLL<T>::decimate(){
    int counter = 1;
    typename DoublyLinkedList<T>::Iterator itr;
    for(itr = container.begin(); itr != container.end(); itr++){
        //every tenth
        if(counter == 10){
            container.removeAt(itr);

            //check if we reached the end of the container
            //removeAt modified itr by shifting it the next pos.
            if(itr == nullptr)
                return;

            //reset counter
            counter = 1;
        }
        ++counter;
    }
}

template<typename T>
void StackLL<T>::insertAt(const T& entry, int i){
    int counter = 0;
    typename DoublyLinkedList<T>::Iterator itr;
    for(itr = container.begin(); itr != container.end(); ++itr){
        if(counter == i){
            container.insertNextTo(itr, entry);
            break;
        }
        ++counter;
    }
}

#endif
