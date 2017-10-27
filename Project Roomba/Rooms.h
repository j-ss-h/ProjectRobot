#include "Objects.h"
#include <iostream>
#include <vector>
using namespace std;

struct dimensionsRoom
{
	int xSize;// height
	int ySize;// width
};


class Room
{
protected:
	int roomID;
	dimensionsRoom size;
	vector <vector <char> > mapRoom;// map of room WITHOUT exterior walls. 
	vector <Object> objRoom;// container for all objects within Room. 

public:
	Room()
	{
		size.xSize = 5;
		size.ySize = 5;
		roomTemplate(size);
	}

	void setSize(dimensionsRoom & item)
	{
		size.xSize = item.xSize;
		size.ySize = item.ySize;
	}

	dimensionsRoom getSize() const // possibly useful for fullMap
	{
		return size;
	}

	vector <vector <char> > getRoom() const
	{
		return mapRoom;
	}

	void roomTemplate(dimensionsRoom & item)
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

	}

	friend ostream & operator <<(ostream & out, Room item)
	{
		for (int i = 0; i < item.size.xSize + 2; i++)
		{
			out << "# ";
		}
		out << endl;
		
		for (int x = 0; x < item.size.xSize; x++)
		{
			out << "# ";
			for (int y = 0; y < item.size.ySize; y++)
			{
				out << item.mapRoom[x][y] << " ";
			}
			out << "#" << endl;
		}
		for (int i = 0; i < item.size.xSize + 2; i++)
		{
			out << "# ";
		}
		out << endl;
		
		return out;
	}
};