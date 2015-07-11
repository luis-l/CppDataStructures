
#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

template<typename T>
class DoublyLinkedList{
    //display
    friend std::ostream& operator<<(std::ostream& os, const DoublyLinkedList& list){
        for(Iterator itr = list.begin(); itr != list.end(); ++itr)
            os << itr.peek() << '\n';
        return os;
    }
    private:
        template<typename>
        class Node{
            public:
                Node() :
                    next(nullptr, prev(nullptr)){}

                Node(const T& data) :
                    data(data), next(nullptr), prev(nullptr){}

                Node(const T& data, Node<T>* next, Node<T>* prev) :
                    data(data), next(next), prev(prev) {}

                T data;
                Node<T>* next;
                Node<T>* prev;
        };

        Node<T>* head;
        Node<T>* tail;
        int numberOfElements;

    public:
        class Iterator{
            private:
                const Node<T>* current;

            public:
                Iterator(){}
                Iterator(const Node<T>* current) :
                    current(current){}

                void operator++(){
                    current = current->next;
                }

                Iterator& operator++(int useless){
                    current = current->next;
                    return *this;
                }

                bool operator!=(const Iterator& other) const{
                    return current != other.current;
                }

                bool operator==(const Iterator& other) const{
                    return current == other.current;
                }

                const T& peek() const{
                    return current->data;
                }

                const Node<T>* getCurrent() const{
                    return current;
                }
        };

        //create an empty list
        DoublyLinkedList();

        ~DoublyLinkedList();

        const int size() const
            {return numberOfElements;}

        void addFront(const T& entry);
        void addBack(const T& entry);
        void removeFront();
        void removeBack();

        //user must check if list is not empty in order to get elements
        const T& getFront() const;
        const T& getBack() const;
        const T& getAt(const Iterator& itr) const;

        void insertNextTo(const T& target, const T& newEntry);
        void insertPrevTo(const T& target, const T& newEntry);
        void insertNextTo(const Iterator& itr, const T& newEntry);
        void insertPrevTo(const Iterator& itr, const T& newEntry);

        void remove(const T& target);

        //has the iterator point to the element next to the one removed - careful with this one
        void removeAt(Iterator& itr);

        void display() const;
        void displayReversed() const;
        void clear();
        bool isEmpty() const;

        const Iterator begin() const
            {return Iterator(head);}

        const Iterator end() const
            {return Iterator(nullptr);}
};

template<typename T>
DoublyLinkedList<T>::DoublyLinkedList() :
    head(nullptr),
    tail(nullptr),
    numberOfElements(0)
{}

template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList(){
    clear();
}

template<typename T>
void DoublyLinkedList<T>::addFront(const T& entry){
    Node<T>* temp = new Node<T>(entry, head, nullptr);

    //empty list
    if(tail == nullptr)
        tail = temp;

    //old head becomes second
    if(head != nullptr)
        head->prev = temp;

    //update new head
    head = temp;

    ++numberOfElements;
}

template<typename T>
void DoublyLinkedList<T>::addBack(const T& entry){
    Node<T>* temp = new Node<T>(entry, nullptr, tail);

    if(head == nullptr)
        head = temp;

    //old tail becomes second to last
    if(tail != nullptr)
        tail->next = temp;

    //set new tail
    tail = temp;

    ++numberOfElements;
}

template<typename T>
void DoublyLinkedList<T>::removeFront(){
    if(head != nullptr){
        Node<T>* temp = head->next;
        delete head;
        head = temp;

        if(head != nullptr)
            head->prev = nullptr;
        //empty list - reset tail
        else
            tail = nullptr;

        --numberOfElements;
    }
}

template<typename T>
void DoublyLinkedList<T>::removeBack(){
    if(tail != nullptr){
        Node<T>* temp = tail->prev;
        delete tail;
        tail = temp;

        if(tail != nullptr)
            tail->next = nullptr;
        else
            head = nullptr;

        --numberOfElements;
    }
}

template<typename T>
const T& DoublyLinkedList<T>::getFront() const {
    return head->data;
}

template<typename T>
const T& DoublyLinkedList<T>::getBack() const {
    return tail->data;
}

template<typename T>
const T& DoublyLinkedList<T>::getAt(const Iterator& itr) const {
    return itr.peek();
}

template<typename T>
void DoublyLinkedList<T>::insertNextTo(const T& target, const T& newEntry){
    Iterator itr;
    for(itr = begin(); itr != end(); ++itr)
        //target found
        if(itr.peek() == target){
            //a new node will be inserted between these two
            Node<T>* newPrev = const_cast<Node<T>*>(itr.getCurrent());
            Node<T>* newNext = newPrev->next;

            Node<T>* temp = new Node<T>(newEntry, newNext, newPrev);
            newPrev->next = temp;

            if(newNext != nullptr)
                newNext->prev = temp;

            //if new Next is null that means that the new insertion is the new tail
            else tail = temp;

            ++numberOfElements;
            return;
        }
}

template<typename T>
void DoublyLinkedList<T>::insertPrevTo(const T& target, const T& newEntry){
    Iterator itr;
    for(itr = begin(); itr != end(); ++itr)
        //target found
        if(itr.peek() == target){
            //a new node will be inserted between these two
            Node<T>* newNext = const_cast<Node<T>*>(itr.getCurrent());
            Node<T>* newPrev = newNext->prev;

            Node<T>* temp = new Node<T>(newEntry, newNext, newPrev);
            newNext->prev = temp;

            if(newPrev != nullptr)
                newPrev->next = temp;

            //if newPrev is null that means that the new insertion is the new head
            else head = temp;

            ++numberOfElements;
            return;
        }
}

//insert directly from the Iterator's current position
template<typename T>
void DoublyLinkedList<T>::insertNextTo(const Iterator& itr, const T& newEntry){

    //a new node will be inserted between these two
    Node<T>* newPrev = const_cast<Node<T>*>(itr.getCurrent());
    Node<T>* newNext = newPrev->next;

    Node<T>* temp = new Node<T>(newEntry, newNext, newPrev);
    newPrev->next = temp;

    if(newNext != nullptr)
        newNext->prev = temp;

    else tail = temp;

    ++numberOfElements;
}

template<typename T>
void DoublyLinkedList<T>::insertPrevTo(const Iterator& itr, const T& newEntry){
    //a new node will be inserted between these two
    Node<T>* newNext = const_cast<Node<T>*>(itr.getCurrent());
    Node<T>* newPrev = newNext->prev;

    Node<T>* temp = new Node<T>(newEntry, newNext, newPrev);
    newNext->prev = temp;

    if(newPrev != nullptr)
        newPrev->next = temp;

    else head = temp;

    ++numberOfElements;
}

template<typename T>
void DoublyLinkedList<T>::remove(const T& target){
    Iterator itr;
    for(itr = begin(); itr != end(); ++itr){
        if(itr.peek() == target){

            Node<T>* current = const_cast<Node<T>*>(itr.getCurrent());

            //first one
            if(current == head)
                removeFront();
            //tail
            else if(current == tail)
                removeBack();
            //middle
            else{
                //hold onto the neighbors
                Node<T>* prev = current->prev;
                Node<T>* next = current->next;

                delete current;
                current = nullptr;

                //relink list
                prev->next = next;
                next->prev = prev;
            }
            --numberOfElements;
            break;
        }
    }
}

template<typename T>
void DoublyLinkedList<T>::removeAt(Iterator& itr){

    Node<T>* current = const_cast<Node<T>*>(itr.getCurrent());

    //shift iterator to next in position
    ++itr;

    //first one
    if(current == head)
        removeFront();
    //tail
    else if(current == tail)
        removeBack();
    //middle
    else{
        //hold onto the neighbors
        Node<T>* prev = current->prev;
        Node<T>* next = current->next;

        delete current;
        current = nullptr;

        //relink list
        prev->next = next;
        next->prev = prev;
    }
    --numberOfElements;
}

template<typename T>
void DoublyLinkedList<T>::display() const{
    Node<T>* current = head;
    while(current != nullptr){
        std::cout << current->data << '\n';
        current = current->next;
    }
}

template<typename T>
void DoublyLinkedList<T>::displayReversed() const{
    Node<T>* current = tail;
    while(current != nullptr){
        std::cout << current->data << '\n';
        current = current->prev;
    }
}

template<typename T>
void DoublyLinkedList<T>::clear(){
    //iterate through entire list
    while(head != nullptr){
        Node<T>* current = head;
        head = current->next;
        delete current;
        current = nullptr;
    }
    numberOfElements = 0;
}

template<typename T>
bool DoublyLinkedList<T>::isEmpty() const{
    return head == nullptr;
}

#endif
