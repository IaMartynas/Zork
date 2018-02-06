/*
 * Map.cpp
 *
 *  Created on: Oct 15, 2017
 *      Author: Martynas
 */

#include "Map.h"
#include <iostream>

Map::Map() {
	// TODO Auto-generated constructor stub

}

Map::~Map() {
	// TODO Auto-generated destructor stub
}

void Map::addRoom(Room *room) {
	rooms.push_back(room);

}

Room* Map::findRoom(Border* border) {
	for (std::vector<Room*>::size_type i = 0; i != rooms.size(); i++) {

		if ((border->getName()) == rooms[i]->getName()) {
			return rooms[i];
		}
	}
	return NULL;

}

Room* Map::findRoom(std::string room){
	for(std::vector<Room*>::size_type i = 0; i!= rooms.size(); i++){
		if(rooms[i]->getName() == room)
			return rooms[i];
	}
	return NULL;
}

Room* Map::getRoom(int i){
	if((std::vector<Room*>::size_type) i != rooms.size()){
		return rooms[i];
	} else{
		return NULL;
	}
}

int Map::numOfRooms(){
	return rooms.size();
}


Container* Map::findContainer(std::string container){
	Container* foundContainer = NULL;
	for(std::vector<Room*>::size_type i = 0; i!= rooms.size(); i++){
		foundContainer = rooms[i]->getContainer(container);
		if(foundContainer != NULL){
			return foundContainer;
		}
	}
	return foundContainer;
}



