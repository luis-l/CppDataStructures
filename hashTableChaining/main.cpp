
/*
    Luis Lopez
    CSCI 3333
    Oct 6 2014

    Hash Table with Chaining
*/

#include "StudentHashTable.h"

#include <iostream>

using std::cout;
using std::endl;

int main(){
    StudentHashTable table;

    for(int i = 0; i < 100; i++){
        Student s(i*10, rand()%100);
        table.insert(s);
    }
    table.updateGPA(-1, 400);
    table.updateGPA(290, 900);
    table.remove(290); // bucket 96 should be empty

    table.display();
    return 0;
}
