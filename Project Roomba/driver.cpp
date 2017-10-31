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
	Room test("f1r1.txt");
	cout << test << endl;
	/**/

	return 0;
}
