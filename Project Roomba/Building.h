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
protected:
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

	// these functions are to facilitate traversal:
	Node *getRoot()
	{
		return root;
	}

	bool findNext(vector <Node *> & tempV, Node* & ptr)
		//ptr points to current Node; tempV is the waypoint vector of States.h
	{
		bool paths = false; 
		Node *parentPtr = ptr;
		for (int x = 0; x < ptr->pathwayPtrs.size(); x++)
		{
			if ((ptr != parentPtr) && (parentPtr->pathwayPtrs[x] == NULL))
				// moves ptr to the first unexplored room. 
			{
				Node* temp = parentPtr;
				tempV.push_back(temp);
				//tempV.push_back(parentPtr->pathwayPtrs[x]);
			}
			else if (parentPtr->pathwayPtrs[x] == NULL)
				// stores other unexplored pathways in tempV. 
			{
				paths = true;
				add((*parentPtr->pathways[x]).getNext() + ".txt");
				ptr = parentPtr->pathwayPtrs[x];
			}
		}
		return paths; // true if unexplored pathways found; otherwise false. 
	}
};
#endif