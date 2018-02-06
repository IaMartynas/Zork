/*
 * Map.h
 *
 *  Created on: Oct 15, 2017
 *      Author: Martynas
 */

#ifndef MAP_H_
#define MAP_H_
#include "Room.h"
#include "Border.h"
#include <vector>
class Map {
public:
	Map();
	virtual ~Map();
	virtual void addRoom(Room *room);
	virtual Room* findRoom(Border* border);
	virtual Room* findRoom(std::string);
	virtual Container* findContainer(std::string);
	virtual Room* getRoom(int);
	virtual int numOfRooms();
private:
	std::vector<Room*> rooms;

};

#endif /* MAP_H_ */
