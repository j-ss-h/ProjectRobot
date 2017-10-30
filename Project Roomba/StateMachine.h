#include <iostream>
using namespace std;
#ifndef STATEMACHINE
#define STATEMACHINE

class StateMachine {
	public:
		enum State { NOT_ASSIGNED,IDLE TRAVERSE, RETREATING};
		State currentState = NOT_ASSIGNED;
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

void CheckState() {
	switch(currentState){
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

void SetIdle(){//Scan next room for entities before entering
	SetState(IDLE);

}

void SetTraverse(){//Finds next room to scan
	SetState(TRAVERSE);

}

void SetRetreating(){//Gets out of dodge to return map
	SetState(RETREATING);

}

#endif
