/*
 * Player.h
 *
 *  Created on: Oct 15, 2017
 *      Author: Martynas
 */


#ifndef PLAYER_H_
#define PLAYER_H_

#include "Map.h"
#include "Inventory.h"
#include <iostream>
#include "Action.h"


class Player {
public:
	Player(Room *room);
	virtual ~Player();
	virtual void Walk(std::string, Map);
	virtual void getInventory();
	virtual Item* getItemFromInventory(std::string item);
	virtual void addItem(Item* item);
	virtual void takeItem(std::string item);
	virtual void dropItem(std::string item);
	virtual void readItem(std::string item);
	virtual void openContainer(std::string container);
	virtual Item* removeItem(std::string);
	virtual Room* getCurrentRoom();
private:
	virtual void setRoom(Room* room);
	Room* mRoom;
	Inventory mInventory;

};

#endif /* PLAYER_H_ */
