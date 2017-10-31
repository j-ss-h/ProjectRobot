//this is the base level object in the project. 
#ifndef OBJECT
#define OBJECT

#include <iostream>
using namespace std;

struct coordinateObject
	// structure to hold the grid coordinates of Object in Room. 
{
	int row = 0;
	int col = 0;
};
// OUTPUT OPERATOR TO TEST COORDINATE!!!!!!!!!!!!!!!!!!!!!!!
ostream & operator <<(ostream & out, coordinateObject value)
{
	out << "row: " << value.row << "\ncol: " << value.col << endl;
	return out;
}
// END OF TEST FUNCTION!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

class Object
	// superclass: contains member variables and the set/get functions for children. 
{
protected:
	coordinateObject location;
	char symbol;

public:
	void setLocation(coordinateObject info)
		// assigns the values of coordinate struct in Object. 
	{
		location.row = info.row;
		location.col = info.col;
	}

	coordinateObject getLocation() const
		// returns coordinate struct of Object.
	{
		return location;
	}

	char getSymbol() const
		// returns symbol of Object. 
	{
		return symbol;
	}

	Object()
		// default constructor. 
	{
		// contents can be erased after testing. 
		location.row = 0;
		location.col = 0;
	}
};

class Door : public Object
{
public:
	Door() : Object()
	{
		symbol = '|';// this should be variable... need L for locked. 
		// next = ID of room on other side of door. 
	}
};

class Stairs : public Object
{
public:
	Stairs() : Object()
	{
		symbol = 'U';// this should be variable... need D for down. 
	}
};

class Window : public Object
{
public:
	Window() : Object()
	{
		symbol = 'W';
	}
};

class Obstruction : public Object
{
public:
	Obstruction() : Object()
	{
		symbol = 'O';
	}
};

class Entity : public Object
{
public:
	Entity() : Object()
	{
		symbol = 'E';// this should be variable... need A for armed.
	}
};
#endif