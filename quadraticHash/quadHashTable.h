
#ifndef QUAD_HASH
#define QUAD_HASH

#include <iostream>
#include <cmath>

using std::cout;
using std::endl;

template<typename T>
class QuadHashTable{

    private:
        class Bucket{
            public:
                T value;
                bool occupied = false;
                bool deleted = false;
        };

        Bucket* container;
        int capacity;
        int numberOfElements = 0;

        int nextPrimeCap(int reference){
            int p = reference;
            while(!isPrime(p))
                p++;
            return p;
        }

        //n will never be 2
        bool isPrime(int n){
            for(int i = 2; i <= sqrt(n); i++)
                if(n % i == 0)
                    return false;
            return true;
        }

        //used only by resize()
        void rehash(Bucket& b){
            int hash = b.value % capacity;
            int pos = hash;
            int i = 0;

            //find unoccupied bucket
            while(container[pos].occupied){
                i++;
                pos = (hash + i*i) % capacity;
            }
            //fillup bucket
            container[pos] = b;
        }

        void resize(int newCap){
            //have reference to old container
            Bucket* temp = container;
            int oldCap = capacity;

            //setup new container
            capacity = newCap;
            container = new Bucket[capacity];

            //rehash values into new container
            for(int i = 0; i < oldCap; i++)
                if(temp[i].occupied){
                    rehash(temp[i]);          //reuse insert with the updated container
                }

            //delete old copies
            delete temp;
        }

    public:
        QuadHashTable(){
            capacity = 13;
            container = new Bucket[capacity];
        }
        QuadHashTable(int cap){
            capacity = (cap < 13) ? 17 : nextPrimeCap(cap);
            container = new Bucket[capacity];
        }
        ~QuadHashTable(){
            delete[] container;
            container = nullptr;
        }

        void insert(const T& entry){
            numberOfElements++;
            int hash = entry % capacity;
            int pos = hash;
            int i = 0;

            //find unoccupied bucket or one that is deleted
            while(container[pos].occupied && !container[pos].deleted){
                i++;
                pos = (hash + i*i) % capacity;
            }
            //fillup bucket - reset deleted status
            container[pos].value = entry;
            container[pos].occupied = true;
            container[pos].deleted = false;

            //expand capacity if needed
            if(numberOfElements >= capacity/2){
                int newCap = nextPrimeCap(capacity*2);
                resize(newCap);
            }
        }

        //return the index position of target in the hash table
        int find(const T& target){
            int hash = target % capacity;
            int pos = hash;
            int i = 0;

            //search until there is an empty bucket
            while(container[pos].occupied){
                //found
                if(!container[pos].deleted && container[pos].value == target)
                    return pos;
                i++;
                pos = (hash + i*i) % capacity;
            }
            //empty bucket found, target does not exist
            return -1;
        }

        bool contains(const T& target){
            return find(target) != -1;
        }

        void remove(const T& target){
            int pos = find(target);

            //mark as deleted if found
            if(pos != -1){
                numberOfElements--;

                //deleted buckets are still occupied by "dead" values
                container[pos].deleted = true;

                //shrink if needed
                if(numberOfElements <= capacity/8){
                    int newCap = nextPrimeCap(capacity/2);
                    resize(newCap);
                }
            }
        }

        int size(){
            return numberOfElements;
        }

        //reset hash table
        void clear(){
            delete[] container;
            capacity = 13;
            numberOfElements = 0;
            container = new Bucket[capacity];
        }

        void display(){
            for(int i = 0; i < capacity; i++){
                cout << i << ": ";
                if(container[i].occupied && !container[i].deleted)
                    cout << container[i].value;
                cout << endl;
            }
        }
};

#endif
