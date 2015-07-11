/*
    A Generic Hash Table that uses
    AVL trees for chaining.

    Hash Table always has a prime capacity to avoid
    clustering of items from purposeful assualts.
*/

#ifndef HASH_TABLE
#define HASH_TABLE

#include "../AVL/AVL.h"
#include <iostream>
#include <cmath>

using std::cout;
using std::endl;

//container type, element type
template<typename T>
class HashTable{
    private:
        int capacity;
        int minCapacity = 11;
        int numberOfElements = 0;
        double low, high;

        AVL<T>* container;

        unsigned hash(const T& value){
            return value % capacity;
        }

        double loadFactor(){
            return static_cast<double>(numberOfElements) / capacity;
        }

        void rehash(const T& entry){
            int pos = hash(entry);

            //insert at bucket
            container[pos].insert(entry);
        }

        void resize(int newCap){

            cout <<  capacity <<", RESIZE: " << newCap << endl;
            //hold referene to old container
            AVL<T>* temp = container;
            int oldCap = capacity;

            container = new AVL<T>[newCap];
            capacity = newCap;

            //go through each bucket
            for(int bucket = 0; bucket < oldCap; bucket++){
                //iterate through all items in a bucket
                typename AVL<T>::Iterator itr;
                itr = temp[bucket].begin();

                while(itr.hasNext())
                    //rehash into new container
                    rehash(itr.next());
            }
            delete[] temp;
        }

        int nextPrimeCap(int reference){
            int p = reference;
            while(!isPrime(p))
                p++;
            return p;
        }

        //n will never be 2
        bool isPrime(int n){
            for(int i = 2; i < sqrt(n); i++)
                if(n % i == 0)
                    return false;
            return true;
        }

    public:
        //Simplifies accessing individual elements outside the hash table.
        //This can be used to check if an obtained element is valid
        //so it can accessed/modified.
        class Element{
            public:
                Element(){
                    valid = false;
                }
                Element(T* data, bool valid){
                    this->data = data;
                    this->valid = valid;
                }
                T* data;
                bool valid;
        };

        HashTable(){
            low = 0.1;
            high = 2.0;
            capacity = minCapacity;
            container = new AVL<T>[capacity];
        }

        HashTable(double low, double high){
            this->low = low;
            this->high = high;
            capacity = minCapacity;
            container = new AVL<T>[capacity];
        }

        ~HashTable(){
            if(container)
                delete[] container;
        }

        void insert(const T& entry){
            numberOfElements++;
            int pos = hash(entry);

            //if it doesn't exist in the table then insert
            if(!get(entry).valid){
                //insert at bucket
                container[pos].insert(entry);

                //resize if need
                if(numberOfElements > minCapacity && loadFactor() > high)
                    resize(nextPrimeCap(capacity*2));
            }
        }

        void remove(const T& target){
            //remove if target is found
            if(get(target).valid){
                numberOfElements--;
                int pos = hash(target);

                //remove from bucket
                container[pos].remove(target);

                //resize if need
                if(numberOfElements > minCapacity && loadFactor() < low)
                    resize(nextPrimeCap(capacity/2));
            }
        }

        //Find an element.
        const Element get(const T& target){
            int pos = hash(target);
            bool found = container[pos].find(target);
            if(found){
                T* data = const_cast<T*>(&container[pos].getFoundData());
                return Element(data, true);
            }
            //invalid Element
            return Element();
        }

        void display(){
            //display each bucket
            for(int i = 0; i < capacity; i++){
                cout << "Bucket " << i << endl;
                container[i].display();
                cout << endl;
            }
        }
};

#endif
