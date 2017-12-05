//this is created as a State Machine, to control the behavior of the robot. 
#ifndef STATEMACHINE
#define STATEMACHINE

#include "Building.h"
#include <iostream>
using namespace std;

class StateMachine : private Building
{
	// new section
private:
	Node *ptr = NULL;
	vector <Node *> wayPoint;
	int wayPointIndex = 0;
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
	enum State { NOT_ASSIGNED, IDLE, TRAVERSE, RETREATING, COMPROMISED, COMPLETE };
	State currentState = IDLE; // changed from NOT_ASSIGNED!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	State previousState = NOT_ASSIGNED;
	StateMachine() = default;
	State GetCurrentState() { return currentState; }
	State GetPreviousState() { return previousState; }
	void SetState(State currentState);
	void SwitchToPreviousState(State currentState);
	void CheckState();
	void SetIdle();
	void SetTraverse();
	void SetRetreating();
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
		if (/*In same room as entity*/) SetRetreating();
		else if (/*Not in same room and scan complete*/) SetTraverse();
		break;
	case TRAVERSE:
		if (/*In same room as entity*/) SetRetreating();
		else if (/*Next room has not been scanned*/) SetIdle();
		break;
	case RETREATING:
		if (/*No longer in the same room as entity and traversal not complete*/) SetIdle();
		break;
	default:
		std::cout << "No state found for this state machine object\n";
		break;
	}
}

void StateMachine::SetIdle() {//Scan next room for entities before entering
	SetState(IDLE);

}

void StateMachine::SetTraverse() {//Finds next room to scan
	SetState(TRAVERSE);

}

void StateMachine::SetRetreating() {//Gets out of dodge to return map
	SetState(RETREATING);

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