//this is created as a State Machine, to control the behavior of the robot. 
#ifndef STATEMACHINE
#define STATEMACHINE

#include "Building.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>
using namespace std;


class StateMachine : private Building
{
	// new section
private:
	Node *ptr = NULL;
	vector <Node *> wayPoint;
	int wayPointIndex = 0, entityCount=0;
	bool compromisedCheck = false, lockedDoorCheck = false, obstructionCheck=false;
	int ARMED_SAVE = 20, UNARMED_SAVE = 15, LOCKED_DOOR = 10, OBSTRUCTION=5;//SAVE THROW PROBABILITY OUT OF 100

	ofstream log; 
	
	// new section

public:
	/*
	REMINDER:
	1.) Be sure to code in CheckState() for the two new states: COMPROMISED and COMPLETE

	2.) To "scan for entities" is referencing Objects in ptr->room.getObjects() and returns as vector <Object*> 
		The delimiters would be 'E' and 'A'

	3.) To go to the next room use building.findNext( waypointVector, currentRoomPtr)
		it fills the wayPoint with a pointer to the current room for each Door not traversed.
		it returns a boolean value {0/F, 1/T} based on if it could move the pointer to an undiscovered room.
		when it returns 0/F, then you need to set ptr to wayPoint[wayPointIndex] and increment wayPointIndex by 1. 

	4.) Be sure each time a decision is made to add a new line to a text file "log.txt" with a description.
		Example1: Scanned Room "roomID1". Entities present. Covert transversal successful. Appended data. 
		Example2: Scanned Room "roomID2". Entities present. Covert transversal unsuccessful. Retreating...
		Example3: Retreat successful. Returning to Room "roomID2". Covert transversal successful. Appended data.
		***NOTE: You will have to make an individual entry for ROOT, because it is established BEFORE the loop in Deploy()

	5.) You may need to move the probability integers from driver.cpp to evaluate for RETREAT, COMPROMISED, and COMPLETE states. 
		for now, create an integer with value 100. Compare it to the corresponding probability integer to determine probable states.
			Example: randomNumber > ROBOT_FOUND
			***NOTE: You can skip this part and just add a comment near the code where an evaluation would take place. 
	*/
	enum State { NOT_ASSIGNED, IDLE, TRAVERSE, COMPROMISED, COMPLETE };
	State currentState = IDLE; // changed from NOT_ASSIGNED!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	State previousState = NOT_ASSIGNED;
	StateMachine() {
		log.open("log.txt");
	};
	State GetCurrentState() { return currentState; }
	State GetPreviousState() { return previousState; }
	void SetState(State currentState);
	void SwitchToPreviousState(State currentState);
	void CheckState();
	void SetIdle();
	void SetTraverse();
	void SetCompromised();
	void SetComplete();
	void ArmedSaveThrow();
	void UnarmedSaveThrow();
	void LockedDoorSaveThrow();
	void ObstructionSaveThrow();
	void setArmedProbability(int armed);
	void setUnarmedProbability(int unarmed);
	void setLockedDoorProbability(int locked);
	void setObstructionProbability(int obstruction);
	bool findEntity();

	// new addition
	void Deploy();
};

void StateMachine::SetState(State currentState) {
	if (this->currentState != NOT_ASSIGNED) {
		this->previousState = this->currentState;
	}
	this->currentState = currentState;
}

void StateMachine::SwitchToPreviousState(State currentState) {
	if (this->previousState != NOT_ASSIGNED) {
		State temp = currentState;
		this->currentState = this->previousState;
		this->previousState = temp;
	}
}

void StateMachine::CheckState() {
	switch (currentState) {
	case IDLE:
		ArmedSaveThrow();
		UnarmedSaveThrow();
		LockedDoorSaveThrow();
		

		if (!compromisedCheck)
		{
			if (findEntity())//if not compromised and entities were found add actions and entityCount to log
			{
				log << "Scanned Room: " << ptr->room.getRoomID() << endl << "Room contains " << entityCount << endl << "Robot continued traversal\n" << "Appended\n" << endl;
			}
			else//if not compromised and no entities add to log
			{
				log << "Scanned Room: " << ptr->room.getRoomID() << endl << "Room contains no entities" << endl << "Robot continued traversal\n" << "Appended\n" << endl;
			}
			SetTraverse();
		}
		else//if compromised
		{
			if (findEntity())//need this because it also calculates entity count
			{
				log << "Scanned Room: " << ptr->room.getRoomID() << endl << "Room contains " << entityCount << endl << "Robot unable to continued traversal \n" << "Retreating\n" << endl;
			}
			SetCompromised();
		}
		
		
		
		break;
	case TRAVERSE:
		if (findNext(wayPoint, ptr))
		{
			// function has handled movement and waypoint assignment. 
			SetIdle();
		}
		else if (wayPointIndex < wayPoint.size())
		{
			// need to assign ptr based on unused waypoint. 
			ptr = wayPoint[wayPointIndex];
			wayPointIndex++;
			SetIdle();
		}
		else
		{
			log << "***End of the building reached***\n ***Returning to Headquaters.***\n";
			SetComplete();
		}
		break;
	default:

		std::cout << "No state found for this state machine object\n";
		break;
	}
}

//checks to see if robot has been seen by an armed entity
//returns true if armed entity has seen robot
void StateMachine::ArmedSaveThrow() {
	vector <Object* > tempV = ptr->room.getObjects();
	for (int i = 0; i < tempV.size(); i++)
	{
		if ((*tempV[i]).getSymbol() == 'A')
		{
			if (ARMED_SAVE < rand() % 100)
				compromisedCheck = false;
			else
				compromisedCheck = true;
		}
	}
}

//checks to see if robot has been seen by an unarmed entity
//returns true if an unarmed entity has seen robot
void StateMachine::UnarmedSaveThrow() {
	vector <Object* > tempV = ptr->room.getObjects();
	for (int i = 0; i < tempV.size(); i++)
	{
		if ((*tempV[i]).getSymbol() == 'E')
		{
			if (UNARMED_SAVE < rand() % 100)
				compromisedCheck = false;
			else
				compromisedCheck = true;
		}
	}
}

//checks to see if robot has unlocked a door
//return true if it unlocked the door
void StateMachine::LockedDoorSaveThrow() {
	vector <Object* > tempV = ptr->room.getObjects();
	for (int i = 0; i < tempV.size(); i++)
	{
		if ((*tempV[i]).getSymbol() == 'L')
		{
			if (LOCKED_DOOR < rand() % 100)
				lockedDoorCheck = true;
			else
				lockedDoorCheck = false;
		}
	}
}

//checks to see if their are entities in a room and counts all entities
//returns true if entityCount>0
bool StateMachine::findEntity() {
	entityCount = 0;
	vector <Object* > tempV = ptr->room.getObjects();
	for (int i = 0; i < tempV.size(); i++)
	{
		if (((*tempV[i]).getSymbol() == 'E') || ((*tempV[i]).getSymbol() == 'A'))
			entityCount++;
	}
	if (entityCount > 0)
		return true;
	else
		return false;
}

//returns true if obstruction is a problem
void StateMachine::ObstructionSaveThrow()
{
	vector <Object* > tempV = ptr->room.getObjects();
	for (int i = 0; i < tempV.size(); i++)
	{
		if ((*tempV[i]).getSymbol() == 'O')
		{
			if (OBSTRUCTION < rand() % 100)
				obstructionCheck = false;
			else
				obstructionCheck = true;
		}
	}
}
void StateMachine::SetIdle() {//sets state to IDLE
	SetState(IDLE);
}

void StateMachine::SetTraverse() {//sets state to TRAVERSE
	SetState(TRAVERSE);
}

void StateMachine::SetCompromised() {//sets state to COMPROMISED
	SetState(COMPROMISED);
}

void StateMachine::SetComplete() {//sets state to COMPLETE
	SetState(COMPLETE);
}

void StateMachine::setArmedProbability(int armed)
{
	ARMED_SAVE = armed;
}

void StateMachine::setUnarmedProbability(int unarmed)
{
	UNARMED_SAVE = unarmed;
}

void StateMachine::setLockedDoorProbability(int locked)
{
	LOCKED_DOOR = locked;
}

void StateMachine::setObstructionProbability(int obstruction)
{
	OBSTRUCTION = obstruction;
}
void StateMachine::Deploy()
// this continually runs CheckState() until currentState == COMPLETE or COMPROMISED. 
{
	Building building("f1r110.txt");
	ptr = building.getRoot();
	bool finished = false;
	while (!finished) 
	{
		CheckState();
		if ((this->currentState == COMPLETE) || (this->currentState == COMPROMISED))
			// exit condition
		{
			finished = true;
		}
	}

	if (this->currentState == COMPROMISED)
	{
		cout << "Reconnaissance incomplete. Mission compromised.\n";
	}
	else
	{
		cout << "Reconnaissance completed. Mission successful.\n";
	}
}

#endif