#include "Rooms.h";
using namespace std;
#include <iostream>
#include <fstream>
#include <string>

Room::Room()// may not be in final implementation
{
	size.xSize = 5;// used to test
	size.ySize = 5;// used to test
	objRoom;
	setRoom(size);
}

Room::Room(string file)// explicit constructor
{
	fstream fin;
	fin.open(file);
	if (fin.is_open())
	{
		cout << "File opened successfully!\n";// only needed during testing
		int targetInfo;
		dimensionsRoom tempI;
		string input, tempS;

		/* this block assigns roomID */
		getline(fin, input);
		for (targetInfo = 0; input[targetInfo] != ':'; targetInfo++) {} // loops until ':' reached
		targetInfo += 2;
		for (; targetInfo < input.size(); targetInfo++) 
			// loops until end of line
		{
			tempS += input[targetInfo];
		}
		roomID = tempS;// assigns room ID

		/* this block assigns Room dimensions */
		getline(fin, input);
		for (targetInfo = 0; input[targetInfo] != ':'; targetInfo++) {} // loops until ':' reached
		targetInfo += 2;
		for (; !isspace(input[targetInfo]); targetInfo++) 
			// loops until a space is found
		{
			tempI.xSize = (tempI.xSize * 10) + ((int)input[targetInfo] - 48); // reduces ASCII value to integer after typecasting
		}
		targetInfo++;
		for (; targetInfo < input.size(); targetInfo++) 
			// loops until end of line
		{
			tempI.ySize = (tempI.ySize * 10) + ((int)input[targetInfo] - 48); // reduces ASCII value to integer after typecasting
		}
		setSize(tempI); // assigns dimensions of Room

		/* this block assigns Objects information */
		while (!fin.eof())
		{
			coordinateObject tempC;
			tempS = "";

			/* this block finds the object name */
			getline(fin, input);
			for (targetInfo = 0; !isspace(input[targetInfo]); targetInfo++) {} // loops until a space is found
			targetInfo += 1;
			for (; input[targetInfo] != ':'; targetInfo++)  
				// loops until ':' reached
			{
				tempS += input[targetInfo];
			}

			/* this block assigns the coordinates of the object */
			targetInfo += 2;
			for (; !isspace(input[targetInfo]); targetInfo++) 
				// loops until a space is found
			{
				tempC.row = (tempC.row * 10) + ((int)input[targetInfo] - 48); // reduces ASCII value to digit after typecasting
			}
			targetInfo++;
			for (; targetInfo < input.size() && !isspace(input[targetInfo]); targetInfo++) 
				// loops until end of line or space is found (for door/stairs).
			{
				tempC.col = (tempC.col * 10) + ((int)input[targetInfo] - 48); // reduces ASCII value to digit after typecasting
			}

			/* this block creates the object and pushes it back into vector objRoom */
			if (tempS == "door")
			{
				targetInfo += 1;
				tempS = "";
				for (; !isspace(input[targetInfo]); targetInfo++)
				{
					tempS += input[targetInfo];
				}
				Door *door = new Door;
				(*door).setLocation(tempC);
				(*door).setNext(tempS);
				targetInfo += 1;
				(*door).setShift(input[targetInfo]);
				objRoom.push_back(door);
			}
			else if (tempS == "window")
			{
				Window *window = new Window;
				(*window).setLocation(tempC);
				targetInfo += 1;
				(*window).setShift(input[targetInfo]);
				objRoom.push_back(window);
			}
			else if (tempS == "stairs")
			{
				targetInfo += 1;
				tempS = "";
				for (; targetInfo < input.size(); targetInfo++) 
					// loops until end of line. 
				{
					tempS += input[targetInfo];
				}

				Stairs *stairs = new Stairs;
				(*stairs).setLocation(tempC);
				(*stairs).setNext(tempS);

				// this block assigns symbol for stairs
				if (roomID[0] == tempS[0]) // comparing ASCII values to see if both are floors or basements
				{
					if (roomID[1] < tempS[1])
					{
						(*stairs).setSymbol('U');
					}
					else (*stairs).setSymbol('D');
				}
				else if (roomID[0] < tempS[0]) // comparing ASCII values for basement vs floor
				{
					(*stairs).setSymbol('U');
				}
				else (*stairs).setSymbol('D');

				objRoom.push_back(stairs);
			}
			else if (tempS == "obstruction")
			{
				Obstruction *obstruction = new Obstruction;
				(*obstruction).setLocation(tempC);
				objRoom.push_back(obstruction);
				// process chance of threat
			}
			else if (tempS == "entity")
			{
				Entity *entity = new Entity;
				(*entity).setLocation(tempC);
				objRoom.push_back(entity);
				// process chance of armed
			}
		}
		setRoom(size);
	}
	else cout << "Input file error!\n";

	fin.close();
}

void Room::setSize(dimensionsRoom & item)
{
	size.xSize = item.xSize;
	size.ySize = item.ySize;
}

dimensionsRoom Room::getSize() const // possibly useful for fullMap
{
	return size;
}

void Room::setRoom(dimensionsRoom & item)
{
	for (int x = 0; x < item.xSize; x++)
		// creates initial 2-d vector filled with '.'
	{
		vector <char> temp;
		for (int y = 0; y < item.ySize; y++)
		{
			temp.push_back('.');
		}
		mapRoom.push_back(temp);
	}
	for (int x = 0; x < objRoom.size(); x++)
	{
		coordinateObject temp = (*objRoom[x]).getLocation();
		mapRoom[temp.row][temp.col] = (*objRoom[x]).getSymbol();
	}
}

vector <vector <char> > Room::getRoom() const
{
	return mapRoom;
}

void Room::displayRoom() const
{
	vector < vector < char > > room;
	vector < char > temp;
	char shift;
	int row, col;

	// this block creates the 2-dimensional vector. 
	for (int y = 0; y < size.ySize + 2; y++)
		// assigns the top wall
	{
		temp.push_back('#');
	}
	room.push_back(temp);
	for (int x = 0; x < size.xSize; x++)
	{
		temp[0] = '#'; // assigns left wall
		for (int y = 1; y < size.ySize + 1; y++)
			// assigns space between walls
		{
			temp[y] = mapRoom[x][y - 1];
		}
		temp[size.ySize + 1] = '#'; // assigns right wall
		room.push_back(temp);
	}
	for (int y = 0; y < size.ySize + 2; y++)
		// assigns bottom wall
	{
		temp[y] = '#';
	}
	room.push_back(temp);

	// this block performs symbol shifts for Doors and Windows
	for (int x = 0; x < objRoom.size(); x++)
	{
		shift = (*objRoom[x]).getShift();
		row = ((*objRoom[x]).getLocation()).row;
		col = ((*objRoom[x]).getLocation()).col;
		if (shift == 'u') // shift up
		{
			room[row][col + 1] = room[row + 1][col + 1];
			room[row + 1][col + 1] = '.';
		}
		else if(shift == 'd') // shift down
		{
			room[row + 2][col + 1] = room[row + 1][col + 1];
			room[row + 1][col + 1] = '.';
		}
		else if(shift == 'l') // shift left
		{
			room[row + 1][col] = room[row + 1][col + 1];
			room[row + 1][col + 1] = '.';
		}
		else if(shift == 'r') // shift right
		{
			room[row+ 1][col + 2] = room[row + 1][col + 1];
			room[row + 1][col + 1] = '.';
		}
	}

	// this block outputs the 2-dimensional vector to screen. 
	for (int x = 0; x < size.xSize + 2; x++)
	{
		for (int y = 0; y < size.ySize + 2; y++)
		{
			cout << room[x][y] << " ";
		}
		cout << endl;
	}
	cout << endl << endl;
}