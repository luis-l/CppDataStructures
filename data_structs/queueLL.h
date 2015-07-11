
#ifndef QUEUELL_H
#define QUEUELL_H

#include "doublyLinkedList.h"

template<typename T>
class QueueLL{

    //display
    friend std::ostream& operator<<(std::ostream& os, const QueueLL& q){
        os << q.container;
        return os;
    }

    private:
        DoublyLinkedList<T> container;

    public:
        void enqueue(const T& entry);
        const T dequeue();
        const int size() const;
        bool empty() const;
};

template<typename T>
void QueueLL<T>::enqueue(const T& entry){
    container.addBack(entry);
}

template<typename T>
const T QueueLL<T>::dequeue(){
    const T temp = container.getFront();
    container.removeFront();
    return temp;
}

template<typename T>
const int QueueLL<T>::size() const{
    return container.size();
}

template<typename T>
bool QueueLL<T>::empty() const{
    return container.isEmpty();
}

#endif
