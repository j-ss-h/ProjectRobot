/*
File Name: Objects.h
Programming: Deanna Tatum, Jesse A. Hankins, Kyle Meystedt
			 Southeast Missouri State University
			 CS300-01
Date Last Modified: ??/??/????

Description:
coordinateObject is a structure that holds the grid coordinates of an Object's placement in a Room. 

Object is a superclass that contains THE member variables and set/get functions for its descendants.
	Object(): default constructor. 
	setNext(): accepts a string. sets value of next for Doors and Stairs. returns nothing. 
	getNext(): accepts nothing. returns a string of the RoomID of the next room for Doors and Stairs. 
	setLocation(): accepts a coordinateObject. sets the value of location for any Object. returns nothing. 
	getLocation(): accepts nothing. returns a coordinateObject of the value of location for an Object. 
	setSymbol(): accepts a char. assigns the symbol of Object. Used for Doors, Stairs, Obstructions, and Entities. returns nothing. 
	getSymbol(): accepts nothing. returns a char of the symbol of any Object. 
	setShift(): accepts char. assigns the shift of Object. Used for Doors and Windows. returns nothing. 
	getShift(): accepts nothing. returns a char of the shift of an Object. 

Door is a subclass of Object with its own constructor. 
	Door(): default constructor. assigns symbol to '|' which can be changed based on ********CHANCE***************

Stairs is a subclass of Object with its own constructor. 
	Stairs(): default constructor. symbol is assigned when the object is created by Rooms.h

Window is a subclass of Object with its own constructor. 
	Window(): default constructor. assigns symbol to 'W'

Obstruction is a subclass of Object with its own constructor. 
	Obstruction(): default constructor. symbol is assigned based on ********CHANCE***************

Entity is a subclass of Object with its own constructor. 
	Entity(): default constructor. symbol is assigned based on ********CHANCE***************
*/

#ifndef OBJECT
#define OBJECT
#include <iostream>
#include <string>
//#include "Rooms.h"
using namespace std;

struct coordinateObject
	// structure that holds the grid coordinates of an Object's placement in a Room. 
{
	int row = 0;
	int col = 0;
};

class Object
	// Object is a superclass that contains member variables and the set/get functions for its descendants.
{
protected:
	coordinateObject location; // location of Object within Room. 
	char symbol; // char used to denote Object for display purposes. 
	string next; // ID of Room on other side of Door/Stairs. 
	char shift; // char denoting the direction to shift the symbol (door or window) of Object for display purposes.

public:
	Object();
	// default constructor. 

	void setNext(string info);
	// accepts a string. sets value of next for Doors and Stairs. returns nothing. 

	string getNext();
	// accepts nothing. returns a string of the RoomID of the next room for Doors and Stairs. 

	void setLocation(coordinateObject info);
	// accepts a coordinateObject. sets the value of location for any Object. returns nothing. 

	coordinateObject getLocation() const;
	// accepts nothing. returns a coordinateObject of the value of location for an Object. 

	void setSymbol(char value);
	// accepts a char. assigns the symbol of Object. Used for Doors, Stairs, Obstructions, and Entities. returns nothing.

	char getSymbol() const;
	// accepts nothing. returns a char of the symbol of any Object. 

	void setShift(char value);
	// accepts char. assigns the shift of Object. Used for Doors and Windows. returns nothing. 

	char getShift() const;
	// accepts nothing. returns a char of the shift of an Object. 
};

class Door : public Object
{
public:
	Door();
	// default constructor. assigns symbol to '|' which can be changed based on ********CHANCE***************
};

class Stairs : public Object
{
public:
	Stairs();
	// default constructor. symbol is assigned when the object is created by Rooms.h
};

class Window : public Object
{
public:
	Window();
	// default constructor. assigns symbol to 'W'
};

class Obstruction : public Object
{
public:
	Obstruction();
	// default constructor. symbol is assigned based on ********CHANCE***************
};

class Entity : public Object
{
public:
	Entity();
	// default constructor. symbol is assigned based on ********CHANCE***************
};
#endif