#include "Building.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

Building::Building() {} // not used in final implementation. 

Building::Building(string roomID)
{
	root = new Node(roomID);
}

void Building::add(string roomID)
{
	Node *item = new Node(roomID);
	Node *ptr = root;
	Node *parentPtr = NULL;
	vector < vector < Node* > > tempV; // index 0 is for ptr; index 1 is for parentPtr.
	int tempVindex = 0;

	while ((ptr->room).getRoomID() + ".txt" != roomID) // while not at the new room
	{
		for (int x = 0; x < (*ptr).pathwayPtrs.size(); x++)
		{
			// this block assigns the Door in the new Room to the last Room traversed from. 
			if (parentPtr != NULL)
			{
				if (((*ptr->pathways[x]).getNext() == (*parentPtr).room.getRoomID()) && (ptr->pathwayPtrs[x] == NULL))
				{
					ptr->pathwayPtrs[x] = parentPtr;
				}
			}

			// this block assigns any Doors in the current Room that lead to the new Room. 
			if ((roomID == (*ptr->pathways[x]).getNext() + ".txt") && (ptr->pathwayPtrs[x] == NULL))
			{
				ptr->pathwayPtrs[x] = item;
			}

			// this block creates new pointers to traverse alternate pathways and places them in vector tempV. 
			if ((ptr->pathwayPtrs[x] != NULL) && (ptr->pathwayPtrs[x] != parentPtr))
			{
				vector < Node* > fillV;
				Node *temp = ptr->pathwayPtrs[x];
				Node *tempParent = ptr;// points to the current room. 
				fillV.push_back(temp);
				fillV.push_back(tempParent);
				tempV.push_back(fillV);
			}
		}
	
		if ((ptr->room).getRoomID() + ".txt" != roomID)
		{
			parentPtr = tempV[tempVindex][1];
			ptr = tempV[tempVindex][0];
			tempVindex++;
		}
		while (((ptr->room).getRoomID() == roomID) && (tempVindex < tempV.size()))
		{
			parentPtr = tempV[tempVindex][1];
			ptr = tempV[tempVindex][0];
			tempVindex++;
		}
	}
}

void Building::printRoom(string roomID)
{
	if (root->pathways.size() == 0)
		// if empty case
	{
		cout << "Building is empty...\n";
	}
	else if (roomID == root->room.getRoomID() + ".txt") // appends the roomID with the file format, for comparison purposes. 
		// if at root case
	{
		root->room.displayRoom();
	}
	else
	{
		Node *ptr = root;
		Node *parentPtr = NULL;
		vector < vector < Node* > > tempV; // index 0 is for ptr; index 1 is for parentPtr.
		int tempVindex = 0;
		int counter;
		bool found = false;
		while (found == false)
		{
			counter = 0;
			while ((counter < ptr->pathways.size() - 1) && (roomID != (*ptr->pathways[counter]).getNext() + ".txt"))
			{
				counter++;
			}
			if (roomID == (*ptr->pathways[counter]).getNext() + ".txt")
			{
				ptr->pathwayPtrs[counter]->room.displayRoom();
				found = true; // exit case. 
			}
			else
			{
				// this block creates new pointers to traverse alternate pathways and places them in vector tempV. 
				for (int x = 0; x < (*ptr).pathwayPtrs.size(); x++)
				{
					if ((ptr->pathwayPtrs[x] != NULL) && (ptr->pathwayPtrs[x] != parentPtr))
					{
						vector < Node* > fillV;
						Node *temp = ptr->pathwayPtrs[x];
						Node *tempParent = ptr;// points to the current room. 
						fillV.push_back(temp);
						fillV.push_back(tempParent);
						tempV.push_back(fillV);
					}
				}

				if ((ptr->room).getRoomID() + ".txt" != roomID)
				{
					parentPtr = tempV[tempVindex][1];
					ptr = tempV[tempVindex][0];
					tempVindex++;
				}
				while (((ptr->room).getRoomID() == roomID) && (tempVindex < tempV.size()))
				{
					parentPtr = tempV[tempVindex][1];
					ptr = tempV[tempVindex][0];
					tempVindex++;
				}
			}
		}
	}
}

void Building::printFloor(/* not sure... */)
{
	/*
	This will need to be redone. It was implemented as a way to test if the pointers were linking correctly.
	
	int counter = 0;
	if (pathways.size() == 0)
		// if empty case
	{
		cout << "Building is empty...\n";
	}
	else
	{
		while (counter < pathwayPtrs.size())
		{
			if (pathwayPtrs[counter] != NULL)
			{
				(*pathwayPtrs[counter]).displayRoom();
			}
			counter++;
		}
	}
	*/
}

void Building::printBuilding()
{
	/* not sure... */
}