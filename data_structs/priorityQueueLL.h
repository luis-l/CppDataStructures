
#ifndef PRIORITYQUEUELL_H
#define PRIORITYQUEUELL_H

#include "doublyLinkedList.h"

template<typename T>
class PriorityQueueLL{

    //display
    friend std::ostream& operator<<(std::ostream& os, const PriorityQueueLL& pq){
        os << pq.container;
        return os;
    }

    private:
        DoublyLinkedList<T> container;

    public:
        void insert(const T& entry);
        void update(const T& entry);

        const T extractMin();
        void display() const;
        const int size() const;
        bool empty() const;

};

template<typename T>
void PriorityQueueLL<T>::insert(const T& entry){

    //empty container
    if(container.isEmpty())
        container.addFront(entry);

    //greater than last
    else if(entry >= container.getBack())
        container.addBack(entry);

    else{
        typename DoublyLinkedList<T>::Iterator itr;
        for(itr = container.begin(); itr != container.end(); ++itr)
            //sorted position found
            if(entry < itr.peek()){
                container.insertPrevTo(itr, entry);
                return;
            }

        //add to the back - entry has the greatest value
        container.addBack(entry);
    }
}

//updates by removing the target and then reinserting it to keep
//priority queue order
template<typename T>
void PriorityQueueLL<T>::update(const T& target){
    //find entry
    typename DoublyLinkedList<T>::Iterator itr;
    for(itr = container.begin(); itr != container.end(); ++itr){
        //found
        if(target == itr.peek()){
            container.removeAt(itr);
            this->insert(target);
            break;
        }
    }
}

template<typename T>
const T PriorityQueueLL<T>::extractMin(){
    T temp = container.getFront();
    container.removeFront();
    return temp;
}

template<typename T>
void PriorityQueueLL<T>::display() const{
    container.display();
}

template<typename T>
const int PriorityQueueLL<T>::size() const{
    return container.size();
}

template<typename T>
bool PriorityQueueLL<T>::empty() const{
    return container.isEmpty();
}

#endif
