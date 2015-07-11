
#include "quadHashTable.h"

int main(){	//part 1:

	QuadHashTable<int> table(10);

	table.insert(4371);
	table.insert(1323);
    table.insert(6173);
	table.insert(4199);
	table.insert(4344);
	table.insert(9679);
	table.insert(1989);

	//table.display();
	cout << endl;

	//part 2:  Implement a method to find if a given number is in the table

	QuadHashTable<int> table2(17); //what are 2 reasons 17 was chosen for this test?

	table2.insert(4371);
	table2.insert(1323);
	table2.insert(6173);
	table2.insert(4199);
	table2.insert(4344);
	table2.insert(6613);
	table2.insert(1224);

	//table2.display();
	cout << endl;

	if( table2.contains( 1224 ) )
		cout << "Correct!" << endl;
	else
		cout << "Wrong!" << endl;

	if( table2.contains( 1700 ) )
		cout << "Wrong!" << endl;
	else
		cout << "Correct!" << endl;

    cout << endl;

	//part 3:
	//-Initialize table size to be a prime number
	//-When table fills to half size (or over), resize
	//  to a larger table of prime size to ensure hashing never fails.
	QuadHashTable<int> table3;

	for(int i=0; i<100; i++)
		table3.insert( rand() );

	//table3.display();

	for(int i=0; i<10000; i++)
		table3.insert( rand() );


	//part 4: Implement void remove(int x).

    table.remove(6173);
	table.remove(4199);
    table.remove(4344);
	table.remove(9679);
	table.remove(1989);
	cout << table.size() << endl;

    if( table.contains( 4371 ) )
		cout << "Correct!" << endl;
	else
		cout << "Wrong!" << endl;

    if( table.contains( 1989 ) )
		cout << "Wrong" << endl;
	else
		cout << "Correct!" << endl;

    table.insert(20);
    table.insert(30);
    table.insert(40);
    table.insert(50);
    table.insert(60);
    cout << endl;

    table.remove(40);
    table.remove(50);
    table.remove(60);
    table.remove(20);
    table.remove(30);

    table.remove(30);
    table.remove(30);
    table.remove(30);
    table.remove(30);
    table.remove(30);
    table.remove(30);
    table.remove(30);
    table.remove(30);
    table.display();

    return 0;
}
