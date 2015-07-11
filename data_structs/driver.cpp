/*
	Luis Lopez
	CSCI 3333
	
	Homework #2: Linkedlist, stack, queue, priority queue
	
	The stack, queue, priority queue use an internal doubly linked list.
*/

#include <iostream>
#include "stackLL.h"
#include "queueLL.h"
#include "priorityQueueLL.h"

#include <cstdlib>

using namespace std;

int main()
{
    srand(time(0));

	/////////////Test code for stack ///////////////
	StackLL<int> stk;

	stk.push(5);
	stk.push(13);
	stk.push(7);
	stk.push(3);
	stk.push(2);
	stk.push(11);

	cout << "Popping: " << stk.pop() << endl;
	cout << "Popping: " << stk.pop() << endl;

	stk.push(17);
	stk.push(19);
	stk.push(23);

	while( ! stk.empty() )
	{
		cout << "Popping: " << stk.pop() << endl;
	}
    cout << endl;

	// output order: 11,2,23,19,17,3,7,13,5

	///////////////////////////////////////

	//////////Test code for queue ///////////

	QueueLL<int> Q;

	Q.enqueue(1);
	Q.enqueue(2);
	Q.enqueue(3);
	cout << "Dequeuing: " << Q.dequeue() << endl;
	cout << "Dequeuing: " << Q.dequeue() << endl;
	Q.enqueue(4);
	Q.enqueue(5);

	while( ! Q.empty() )
	{
		cout << "Dequeuing: " << Q.dequeue() << endl;
	}
	cout << endl;

	/////////////////////////////////////////

	//////////Test code for priority queue/////

	PriorityQueueLL<int> pQueue;

	const int SIZE = 20;

	//insert a bunch of random numbers
	for(int i=0; i<SIZE; i++)
	{
		pQueue.insert( rand() % 100 );
	}

	//pull them back out..
	while( ! pQueue.empty() )
	{
		cout << pQueue.extractMin() << endl;
	}

	///////////////////////////////////////////
	return 0;
}
