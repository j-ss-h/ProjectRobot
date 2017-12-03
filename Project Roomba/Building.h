/*
File Name: Building.h
Programming: Deanna Tatum, Jesse A. Hankins, Kyle Meystedt
			 Southeast Missouri State University
			 CS300-01
Date Last Modified: ??/??/????

Description:
Building is a class that... 
	function(): does stuff... 

*/
#ifndef BUILDING
#define BUILDING

#include "Rooms.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Building
{
private:
	class Node
	{
	public:
		Room room;
		vector < Object* > pathways; // contains all of the Doors and Stairs of the building. 
		vector < Node* > pathwayPtrs; /* contains pointers for the destination of each Door and Stairs in pathways vector.
									  Example:
									  the Door stored at pathways[n] will "lead to" the Room referenced by the pointer stored at pathwayPtrs[n].
									  */
		Node() {} // default constructor. not used in final implementation. 

		Node(string roomID) // explicit constructor
		{
			Room *tempR = new Room(roomID);
			room = *tempR;
			vector < Object* > tempV = (*tempR).getObjects();
			for (int x = 0; x < tempV.size(); x++)
				// places all Door and Stair pointers into pathways, and an equal amount of pointers into pathwayPtrs. 
			{
				Node *tempPtr = NULL;
				if ((*tempV[x]).getSymbol() == '|')
				{
					pathways.push_back(tempV[x]);
					pathwayPtrs.push_back(tempPtr);
				}
				else if ((*tempV[x]).getSymbol() == 'L')
				{
					pathways.push_back(tempV[x]);
					pathwayPtrs.push_back(tempPtr);
				}
				else if ((*tempV[x]).getSymbol() == 'U')
				{
					pathways.push_back(tempV[x]);
					pathwayPtrs.push_back(tempPtr);
				}
				else if ((*tempV[x]).getSymbol() == 'D')
				{
					pathways.push_back(tempV[x]);
					pathwayPtrs.push_back(tempPtr);
				}
			}
		}
	};

	Node *root; // data member
	

public:
	Building(); // not used in final implementation. 

	Building(string roomID);

	void add(string roomID);

	void printRoom(string roomID);

	void printFloor(/* not sure... */);

	void printBuilding(); // not coded...
};
#endif