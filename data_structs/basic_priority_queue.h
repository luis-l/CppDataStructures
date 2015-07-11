
/*
    Priority Queue that used the vector as
    a container
*/

#ifndef BASIC_PQ
#define BASIC_PQ

#include <vector>
#include <iostream>

using std::vector;

template <typename T>
class basic_priority_queue{

    private:
        vector<T> container;

    public:

        void insert(const T& entry){
            //empty container
            if(container.empty())
                container.push_back(entry);

            //greater than last
            else if(entry >= container.back())
                container.push_back(entry);

            else{
                typename vector<T>::iterator i;
                for(i = container.begin(); i != container.end(); i++){
                    if(entry < *i){
                        container.insert(i, entry);
                        return;
                    }
                }
                //add to the back - entry has the greatest value
                container.push_back(entry);
            }
        }

        void update(const T& target){
            //find entry
            typename vector<T>::iterator i;
            for(i = container.begin(); i != container.end(); ++i){
                //found
                if(target == *i){
                    container.erase(i);
                    this->insert(target);
                    break;
                }
            }
        }

        const T& extractMin(){
            return container.front();
        }

        //removes min
        void pop(){
            container.erase(container.begin());
        }

        bool empty(){
            return container.empty();
        }

        void display(){
            typename vector<T>::iterator i;
            for(i = container.begin(); i != container.end(); ++i)
                std::cout << *i << std::endl;
        }

        // POINTER VARIANTS
        void insert(const T*& entry){
            //empty container
            if(container.empty())
                container.push_back(entry);

            //greater than last
            else if(entry >= container.back())
                container.push_back(entry);

            else{
                typename vector<T>::iterator i;
                for(i = container.begin(); i != container.end(); i++){
                    if(*entry < **i){
                        container.insert(i, entry);
                        return;
                    }
                }
                //add to the back - entry has the greatest value
                container.push_back(entry);
            }
        }

    void update(const T*& target){
        //find entry
        typename vector<T>::iterator i;
        for(i = container.begin(); i != container.end(); ++i){
            //found
            if(*target == **i) {
                container.erase(i);
                this->insert(target);
                break;
            }
        }
    }
};


#endif
