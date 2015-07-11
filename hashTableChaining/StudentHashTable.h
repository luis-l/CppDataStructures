
#ifndef STUDENT_HASH_H
#define STUDENT_HASH_H

#include "HashTable.h"
#include "Student.h"

class StudentHashTable{

    private:
        HashTable<Student>* container;

    public:
        StudentHashTable(){
            container = new HashTable<Student>();
        }
        StudentHashTable(double low, double high){
            container = new HashTable<Student>(low, high);
        }
        ~StudentHashTable(){
            delete container;
        }

        void insert(const Student& s){
            container->insert(s);
        }

        void remove(unsigned id){
            container->remove(Student(id));
        }

        void updateGPA(unsigned id, double newgpa){
            HashTable<Student>::Element student;
            student = container->get(Student(id));

            //update if student exists
            if(student.valid)
                student.data->gpa = newgpa;
        }

        void display(){
            container->display();
        }
};
#endif
