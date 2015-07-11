
#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <iostream>
#include <stdlib.h>

template<typename T>
class BinarySearchTree{
    private:
        class Vertex{
            public:
                Vertex();
                Vertex(const T& data);
                Vertex(const T& data, Vertex* left, Vertex* right);
                Vertex* right;
                Vertex* left;
                T data;
        };
        Vertex* root;
        int numberOfElements;

        ///Helper Functions///
        void insert(const T& entry, Vertex*& current);
        void remove(const T& target, Vertex*& current);
        void clear(Vertex*& current);
        void displayInOrder(const Vertex* current);
        void displayPreOrder(const Vertex* current);
        void displayPostOrder(const Vertex* current);

        const Vertex* getMin(const Vertex* current) const;
        const Vertex* getMax(const Vertex* current) const;

    public:
        BinarySearchTree();
        ~BinarySearchTree();

        void insert(const T& entry);
        void remove(const T& target);

        const T& getMin() const;
        const T& getMax() const;

        void displayInOrder();
        void displayPreOrder();
        void displayPostOrder();
        const T& displayRootValue();

        int size();
        bool isEmpty();
        void clear();
};

template<typename T>
BinarySearchTree<T>::Vertex::Vertex() :
    right(nullptr), left(nullptr)
{}

template<typename T>
BinarySearchTree<T>::Vertex::Vertex(const T& data) :
    right(nullptr), left(nullptr), data(data)
{}

template<typename T>
BinarySearchTree<T>::Vertex::Vertex(const T& data, Vertex* left, Vertex* right) :
    right(right), left(left), data(data)
{}

template<typename T>
BinarySearchTree<T>::BinarySearchTree() :
    root(nullptr), numberOfElements(0)
{}

template<typename T>
BinarySearchTree<T>::~BinarySearchTree(){
    clear();
}

template<typename T>
void BinarySearchTree<T>::insert(const T& entry){
    insert(entry, root);
}

template<typename T>
void BinarySearchTree<T>::remove(const T& target){
    remove(target, root);
}

template<typename T>
const T& BinarySearchTree<T>::getMin() const{
    return getMin(root)->data;
}

template<typename T>
const T& BinarySearchTree<T>::getMax() const{
    return getMax(root)->data;
}

//left-parent-right
template<typename T>
void BinarySearchTree<T>::displayInOrder(){
    displayInOrder(root);
}

//parent-left-right
template<typename T>
void BinarySearchTree<T>::displayPreOrder(){
    displayPreOrder(root);
}

//left right parent
template<typename T>
void BinarySearchTree<T>::displayPostOrder(){
    displayPostOrder(root);
}

template<typename T>
const T& BinarySearchTree<T>::displayRootValue(){
    return root->data;
}

template<typename T>
int BinarySearchTree<T>::size(){
    return numberOfElements;
}

template<typename T>
bool BinarySearchTree<T>::isEmpty(){
    return root == nullptr;
}

template<typename T>
void BinarySearchTree<T>::clear(){
    clear(root);
}

///Helper Functions///
template<typename T>
void BinarySearchTree<T>::insert(const T& entry, Vertex*& current){
    //empty slot found
    if(current == nullptr){
        current = new Vertex(entry);
        ++numberOfElements;
    }

    //larger values go to right of tree
    else if(entry > current->data)
        insert(entry, current->right);

    //smaller values go to the left
    else
        insert(entry, current->left);
}

template<typename T>
void BinarySearchTree<T>::remove(const T& target, Vertex*& current){
    //search for the target
    if(current != nullptr){
        //found
        if(target == current->data){
            --numberOfElements;
            //full node case
            if(current->left && current->right){
                int r = rand() % 2;
                //replace data with maximum vertex data in left substree
                if(r == 0){
                    Vertex* max = const_cast<Vertex*>(getMax(current->left));
                    current->data = max->data;
                    delete max;
                    max = nullptr;
                }
                //replace data with minimum vertex data in right substree
                else{
                    Vertex* min = const_cast<Vertex*>(getMin(current->right));
                    current->data = min->data;
                    delete min;
                    min = nullptr;
                }
            }
            //left child exists - create link from current's parent to current's child
            else if(current->left){
                Vertex* child = current->left;
                delete current;
                current = child;
            }
            //right child exists - create link from current's parent to current's child
            else if(current->right){
                Vertex* child = current->right;
                delete current;
                current = child;
            }

            //leaf
            else{
                delete current;
                current = nullptr;
            }
        }
        //search left
        else if(target > current->data)
            remove(target, current->right);

        //search right
        else
            remove(target, current->left);
    }
}

//return the left most vertex
template<typename T>
const typename BinarySearchTree<T>::Vertex* BinarySearchTree<T>::getMin(const Vertex* current) const{
    if(current == nullptr)
        return current;
    while(current->left != nullptr)
        current = current->left;
    return current;
}

//return the right most vertex
template<typename T>
const typename BinarySearchTree<T>::Vertex* BinarySearchTree<T>::getMax(const Vertex* current) const{
    if(current == nullptr)
        return current;
    while(current->right != nullptr)
        current = current->right;
    return current;
}

template<typename T>
void BinarySearchTree<T>::displayInOrder(const Vertex* current){
    if(current != nullptr){
        //print left subtree
        displayInOrder(current->left);
        //print parent
        std::cout << current->data << std::endl;
        //print right subtree
        displayInOrder(current->right);
    }
}

template<typename T>
void BinarySearchTree<T>::displayPreOrder(const Vertex* current){
    if(current != nullptr){
        std::cout << current->data << std::endl;
        displayInOrder(current->left);
        displayInOrder(current->right);
    }
}

template<typename T>
void BinarySearchTree<T>::displayPostOrder(const Vertex* current){
    if(current != nullptr){
        displayInOrder(current->left);
        displayInOrder(current->right);
        std::cout << current->data << std::endl;
    }
}

template<typename T>
void BinarySearchTree<T>::clear(Vertex*& current){
    if(current != nullptr){
        //go to children
        clear(current->right);
        clear(current->left);

        //delete parent
        delete current;
        current = nullptr;
    }
}

#endif
