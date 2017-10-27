#include "Objects.h"
#include <iostream>
#include <vector>
using namespace std;

struct dimensionsRoom
{
	int xSize;// height
	int ySize;// width
	int floor;// z coordinate
};


class Room
{
protected:
	int roomID;
	dimensionsRoom size;
	vector <vector <char> > mapRoom;

public:
	Room()
	{
		size.xSize = 5;
		size.ySize = 5;
		size.floor = 1;
		roomTemplate(size);
	}

	void setSize(dimensionsRoom & item)
	{
		size.xSize = item.xSize;
		size.ySize = item.ySize;
		size.floor = item.floor;
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
		int xNew = item.xSize + 2;
		int yNew = item.ySize + 2;
		vector <vector <char> > empty;
		mapRoom.push_back(empty);
		for (int x = 0; x < xNew; x++)
			// creates initial 2-d vector filled with '.'
		{
			vector <char> temp;
			for (int y = 0; y < yNew; y++)
			{
				temp.push_back('.');
			}
			mapRoom.push_back(temp);
		}
		for (int i = 0; i <= xNew; i *= xNew)
		{
			for (int fill = 0; fill < yNew; fill++)
			{
				mapRoom[fill][i] = '#';
			}
			i++;
		}
		for (int j = 0; j <= yNew; j *= yNew)
		{
			for (int fill = 0; fill < yNew; fill++)
			{
				mapRoom[j][fill] = '#';
			}
			j++;
		}

	}

	friend ostream & operator <<(ostream & out, Room item)
	{
		for (int x = 0; x < item.size.xSize + 2; x++)
		{
			for (int y = 0; y < item.size.ySize + 2; y++)
			{
				out << item.mapRoom[x][y];
			}
			out << endl;
		}
		out << endl;
		return out;
	}
};