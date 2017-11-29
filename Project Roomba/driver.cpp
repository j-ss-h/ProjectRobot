#include "Database.h"
//#include "States.h"

#include <iostream>
#include <fstream>// for input file
using namespace std;

/* 
These are the probabilities for each negatively impacting category for the robot. 
The user can modify these through the menu. 
*/
int ENTITY_ARMED = 0, OBSTRUCTION_THREAT = 0, DOOR_LOCKED = 0, ROBOT_FOUND = 0, ROBOT_COMPROMISED = 0;
void menu();
void probability();

int main()
{
	// menu options. NOT CURRENTLY IN USE. Enter 0 to bypass. 
	cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n"
		 << "!!!!!Menu is not currently in use. Enter 0 to bypass.!!!!!\n"
		 << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n"; // TEMPORARY
	menu();

	//testing room display function

	Room test1("f1r110.txt");
	test1.displayRoom();
	
	return 0;
}

void menu()
{
	int choice = 1;
	bool prob = false;
	bool deployed = false;
	while (choice != 0)
	{
		cout << "***STARTING MENU***\n"
			<< "1.) Set probabilities\n"
			<< "2.) Deploy Robot (run program)\n"
			<< "3.) View Mission Log\n"
			<< "4.) Review Reconnaissance Info\n"
			<< "0.) Exit\n"
			<< "Selection: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
			if (prob == false)
			{
				probability();
				prob = true;
			}
			else cout << "Probabilities have been set. Exit and restart to set new values...\n";
			break;
		case 2:
			if (prob == true)
			{
				cout << "Not yet implemented...\n"; // PLACEHOLDER!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				deployed = true;
			}
			else cout << "Probabilities have not been set...\n";
			break;
		case 3:
			if (deployed == true)
			{
				cout << "Not yet implemented...\n"; // PLACEHOLDER!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			}
			else cout << "Robot has not been deployed...\n";
			break;
		case 4:
			if (deployed == true)
			{
				cout << "Not yet implemented...\n"; // PLACEHOLDER!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			}
			else cout << "Robot has not been deployed...\n";
			break;
		case 0:
			cout << "Exiting program...\n";
			break;
		default:
			cout << "Invalid entry...\n";
			break;
		}
		puts("");
	}
}

void probability()
{
	int prob = 1;
	while (prob != 0)
	{
		cout << "\n***PROBABILITY MENU***\n"
			<< "1.) Entity armed\n"
			<< "2.) Obstruction threat\n"
			<< "3.) Doors locked\n"
			<< "4.) Robot found\n"
			<< "5.) Robot compromised after found\n"
			<< "0.) Save changes (unchanged values default to 0)\n"
			<< "Selection: ";
		cin >> prob;
		switch (prob)
		{
		case 1:
			cout << "Enter the probability of entities being armed (1-100): ";
			cin >> prob;
			if (prob > 0 && prob < 101)
			{
				ENTITY_ARMED = prob;
			}
			else
			{
				prob = 1;
				cout << "Invalid entry...\nPlease enter a value between 1 and 100.\n";
			}
			break;
		case 2:
			cout << "Enter the probability of obstructions being a threat (1-100): ";
			cin >> prob;
			if (prob > 0 && prob < 101)
			{
				OBSTRUCTION_THREAT = prob;
			}
			else
			{
				prob = 1;
				cout << "Invalid entry...\nPlease enter a value between 1 and 100.\n";
			}
			break;
		case 3:
			cout << "Enter the probability of doors being locked (1-100): ";
			cin >> prob;
			if (prob > 0 && prob < 101)
			{
				DOOR_LOCKED = prob;
			}
			else
			{
				prob = 1;
				cout << "Invalid entry...\nPlease enter a value between 1 and 100.\n";
			}
			break;
		case 4:
			cout << "Enter the probability of being found by entities (1-100): ";
			cin >> prob;
			if (prob > 0 && prob < 101)
			{
				ROBOT_FOUND = prob;
			}
			else
			{
				prob = 1;
				cout << "Invalid entry...\nPlease enter a value between 1 and 100.\n";
			}
			break;
		case 5:
			cout << "Enter the probability of being compromised after being found (1-100): ";
			cin >> prob;
			if (prob > 0 && prob < 101)
			{
				ROBOT_COMPROMISED = prob;
			}
			else
			{
				prob = 1;
				cout << "Invalid entry...\nPlease enter a value between 1 and 100.\n";
			}
			break;
		case 0:
			cout << "Returning to previous menu...\n";
			break;
		default:
			cout << "Invalid entry...\n";
			break;
		}
	}
}