//this is the base level object in the project. 

#include "Objects.h";
#include <iostream>
using namespace std;

void Object::setNext(string info)
	// assigns the value of next for doors and stairs. 
{
	next = info;
}

void Object::setLocation(coordinateObject info)
	// assigns the values of coordinate struct in Object. 
{
	location.row = info.row;
	location.col = info.col;
}

coordinateObject Object::getLocation() const
	// returns coordinate struct of Object.
{
	return location;
}

void Object::setSymbol(char value)
	// assigns the symbol of Object. Used for dors and stairs. 
{
	symbol = value;
}

char Object::getSymbol() const
	// returns symbol of Object. 
{
	return symbol;
}

Object::Object()
	// default constructor. 
{
	// contents can be erased after testing. 
	location.row = 0;
	location.col = 0;
}

Door::Door() : Object()
{
	symbol = '|';// this should be variable... need L for locked. 
}

Stairs::Stairs() : Object() {}
	// symbol is assigned when the object is created by Rooms.h

Window::Window() : Object()
{
	symbol = 'W';
}

Obstruction::Obstruction() : Object()
{
	symbol = 'O';
}

Entity::Entity() : Object()
{
	symbol = 'E';// this should be variable... need A for armed.
}