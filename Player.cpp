/*
 * Player.cpp
 *
 *  Created on: Oct 15, 2017
 *      Author: Martynas
 */

#include "Player.h"
#include <iostream>

Player::Player(Room *room) :
		mRoom(room) {
	*mRoom = *room;
	mInventory = Inventory();
	//health = 0;
	// TODO Auto-generated constructor stub

}

Player::~Player() {
	// TODO Auto-generated destructor stub
}

void Player::Walk(std::string direction, Map map) {
	Border* border = mRoom->getBorder(direction);
	if (border == NULL) {
		std::cout << "Can\'t go that way." << std::endl;
	} else {
		Room* newRoom = map.findRoom(border);
		if (newRoom != NULL) {
			setRoom(newRoom);
			std::cout << newRoom->getDescription() << std::endl;
		} else {
			std::cout << "Error in loading the room" << std::endl;
		}

	}
}

void Player::setRoom(Room* newRoom) {
	mRoom = newRoom;
}

void Player::getInventory() {
	if (mInventory.numberOfItems() != 0) {
		std::cout << "Inventory: " << std::endl;
		mInventory.getItems();
	} else {
		std::cout << "Inventory: empty" << std::endl;
	}

}

void Player::addItem(Item* item) {
	mInventory.addItem(item);
}
void Player::takeItem(std::string item) {
	Item* newItem = mRoom->giveItem(item);
	if (newItem == NULL) { //if not on the ground
		std::cout << "No such object found." << std::endl;
	} else {
		std::cout << "Item " << newItem->getName() << " added to inventory."
				<< std::endl;
		mInventory.addItem(newItem);
	}

}


void Player::dropItem(std::string item) {
	Item* droppedItem = mInventory.getItem(item);
	if (droppedItem == NULL) {
		std::cout << "No such object found." << std::endl;
	} else {
		std::cout << droppedItem->getName() << " dropped." << std::endl;
		mRoom->addItem(droppedItem);

	}

}

Item* Player::removeItem(std::string item){
	return mInventory.getItem(item);
}

void Player::readItem(std::string item) {
	Item* itemToBeRead = mInventory.findItem(item);

	if (itemToBeRead == NULL) {
		std::cout << "No such object found." << std::endl;
	} else {
		if (itemToBeRead->getText() != "") {
			std::cout << itemToBeRead->getText() << std::endl;
		} else {
			std::cout << "Nothing written." << std::endl;
		}

	}

}

void Player::openContainer(std::string container) {
	Container* foundContainer = mRoom->getContainer(container);
	if (foundContainer == NULL) {
		std::cout << "No such container found." << std::endl;
	} else {
		foundContainer->setStatus("open");
		if (foundContainer->numberOfItems() != 0) {
			std::cout << foundContainer->getName() << " contains ";
			foundContainer->getItems();
		} else {
			std::cout << foundContainer->getName() << " is empty." << std::endl;
		}
	}

}

Item* Player::getItemFromInventory(std::string item) {
	return mInventory.findItem(item);
}

Room * Player::getCurrentRoom()
{
	return mRoom;
}

