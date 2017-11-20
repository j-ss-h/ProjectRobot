#include "Database.h"
//#include "States.h"

#include <iostream>
#include <fstream>// for input file
using namespace std;

int main()
{
	// testing inheritance
	/*/
	Stairs test;
	cout << "symbol: " << test.getSymbol() << endl;
	test.setLocation();
	cout << "location: \n" << test.getLocation() << endl;
	*/

	// testing room template
	/*
	Room test;
	cout << test << endl;
	*/

	//testing room input from file
	/**/
	Room test1("f1r110.txt");
	cout << test1 << endl;
	Room test2("f1r210.txt");
	cout << test2 << endl;
	Room test3("f1r209.txt");
	cout << test3 << endl;
	Room test4("f1r211.txt");
	cout << test4 << endl;
	Room test5("f1r309.txt");
	cout << test5 << endl;
	Room test6("f1r311.txt");
	cout << test6 << endl;
	Room test7("f1r410.txt");
	cout << test7 << endl;
	/**/

	return 0;
}
/*
BUILDING INFO:
The entire building (input) is in a single file with subfolders consisting of floors. Each floor folder contains text files representing
the information gathered when scanning a room.

Room Name Formatting: f/b#r###.txt
	"f/b#" denotes if it is a floor (increasing from 1 while ascending) or a basement (increasing from 1 while descending).
	"r###" denotes room. The first digit represents the "row" of the floor/building using the top-most row as 1. The two following
		digits represent the "column" of the room in the floor using 10 as an arbitrary center.

	EXAMPLE: f1r110.txt; denotes floor 1, room of floor row 1 in arbitrary center of 10.
	EXAMPLE: b1r308.txt; denotes basement 1, room of floor row 3 that is left of arbitrary center by 2 rooms.

Room Contents Formatting:
	"roomID: ***" A string containing the room name, omitting ".txt".
	"dimensions: # #" The dimensions (row, column) of the room in linear feet scaled back by half (value * 2 = actual distance).
	"object door/stairs/window/obstruction/entity # # ?"
		The two digits represent the position of the object within the room (index of row, column).
		The ? is only used for traversable objects (ie: door or stairs) and contains the roomID of the next area.

	EXAMPLE: object door 0 4 f1r109
		a door located at row 0, column 4 in it's room (shifted out to wall when displaying) that leads to
		room f1r109 (see above for room name explanation).
*/
