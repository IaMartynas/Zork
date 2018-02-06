/*
 * Room.cpp
 *
 *  Created on: Oct 15, 2017
 *      Author: Martynas
 */

#include "Room.h"
#include <iostream>

/*Room::Room(std::string name, std::string description) {
 mType = "";
 mName = name;
 mDescription = description;
 //borders.reserve(4); // reserving each slot for each direction

 }*/

Room::Room(std::string type, std::string name, std::string description) :
		mType(type), mName(name), mDescription(description) {

	mName = name;
	mDescription = description;
	mType = type;
	mStatus = "";
	mInventory = Inventory();

}

Room::~Room() {

}

std::string Room::getDescription() {
	if (mType.empty())
		return " ";
	else
		return mDescription;
}

std::string Room::getType() {
	if (mType.empty())
		return " ";
	else
		return mType;
}

std::string Room::getName() {
	return mName;
}

void Room::setBorder(Border* border) {
	borders.push_back(border); //pushes new border into the vector

}

void Room::removeBorder(std::string room) {
	for (std::vector<Border*>::size_type i = 0; i != borders.size(); i++)
		if (borders[i]->getName() == room) {
			borders.erase(borders.begin() + i);
			break;
		}

}

void Room::removeContainer(std::string container) {
	for (std::vector<Container*>::size_type i = 0; i != containers.size(); i++)
		if (containers[i]->getName() == container) {
			containers.erase(containers.begin() + i);
			break;
		}

}

void Room::removeCreature(std::string creature) {
	for (std::vector<Creature*>::size_type i = 0; i != creatures.size(); i++) {
		if (creatures[i]->getName() == creature) {
			creatures.erase(creatures.begin() + i);
			break;
		}
	}

}

int Room::numOfBorders() {
	return borders.size();
}

void Room::addContainer(Container* container) {
	containers.push_back(container); //pushes new border into the vector

}

Container* Room::getContainer(std::string container) {
	for (std::vector<Container*>::size_type i = 0; i != containers.size();
			i++) {
		if (container == containers[i]->getName()) {
			return containers[i];
		}
	}
	return NULL;
}

void Room::addCreature(Creature* creature) {
	creatures.push_back(creature); //pushes new creature into the vector

}

Creature* Room::getCreature(std::string creature) {
	for (std::vector<Creature*>::size_type i = 0; i != creatures.size(); i++) {

		if (creature == creatures[i]->getName()) {
			return creatures[i];

		}
	}
	return NULL;
}

Border* Room::getBorder(std::string direction) {
	for (std::vector<Border*>::size_type i = 0; i != borders.size(); i++) {

		if (direction == borders[i]->getDirection()) {
			return borders[i];

		}
	}
	return NULL;
}

void Room::getItems() {
	mInventory.getItems();

}

void Room::addItem(Item* item) {
	mInventory.addItem(item);

}

Item* Room::giveItem(std::string item) {

	Item* newItem = mInventory.getItem(item);
	if (newItem == NULL) { //its not on the ground, look through containers
		for (std::vector<Container*>::size_type i = 0; i != containers.size();
				i++) {
			if (containers[i]->getStatus() == "open") {
				newItem = containers[i]->getItem(item);
				if (newItem != NULL) {
					return newItem;
				}

			}
		}
	}
	return newItem;
}

Container* Room::getContainer(int i) {
	if ((std::vector<Container*>::size_type) i != containers.size()) {
		return containers[i];
	} else {
		return NULL;
	}
}

int Room::numOfContainers() {
	return containers.size();
}

Trigger* Room::getTrigger(int i) {
	if ((std::vector<Trigger*>::size_type) i != triggers.size()) {
		return triggers[i];
	} else {
		return NULL;
	}
}

Border* Room::getBorder(int i) {
	if ((std::vector<Border*>::size_type) i != borders.size()) {
		return borders[i];
	} else {
		return NULL;
	}
}

int Room::numOfTriggers() {
	return triggers.size();
}

void Room::addTrigger(Trigger* trigger) {
	triggers.push_back(trigger);

}
std::string Room::getStatus() {
	return mStatus;
}

void Room::updateStatus(std::string newStatus) {
	mStatus = newStatus;
}
