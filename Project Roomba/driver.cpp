#include "Database.h"
#include "States.h"

#include <iostream>
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
	Room test;
	cout << "test\n";
	cout << test << endl;

	return 0;
}
