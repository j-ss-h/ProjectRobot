//This will be created using binary tree, that stores maps. 
#ifndef DATABASE
#define DATABASE

#include "Maps.h"
#include <iostream>
using namespace std;
class DataBase
{
protected:
	class Floor
	{
	public:
		// needs map variable
		Floor *down, *up;
		Floor() // default constructor
		{
			down = nullptr;
			up = nullptr;
		}
		// REMOVE COMMENTING AFTER MAP VARIABLE DEFINED!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		//Floor(/*map variable name*/) // explicit constructor
		/*{
			// assignment of map variable;
			down = nullptr;
			up = nullptr;
		} 
		*/
	};
	Floor *root; // data member

public:
	DataBase()// creates an empty DataBase
	{
		root = nullptr;
	}

	bool Empty() const// check if DataBase is empty
	{
		return root == nullptr;
	}

	//Insert: adds a new floor to DataBase
	//Search: May not be needed...
	//Erase all: calls all erase functions. Prints to screen "Mission compromised. DataBase erased."
	//Display: interface for displaying a floor(in Maps.h), or an individual room(in Rooms.h). 
};
#endif