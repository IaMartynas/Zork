/*
 * Inventory.cpp
 *
 *  Created on: Oct 15, 2017
 *      Author: Martynas
 */

#include "Inventory.h"

Inventory::Inventory() {
	// TODO Auto-generated constructor stub

}

Inventory::~Inventory() {
	// TODO Auto-generated destructor stub
}

void Inventory::getItems() {
	for (std::vector<Item>::size_type i = 0; i != items.size(); i++) {
		if (i == items.size() - 1) { //last element
			std::cout << items[i]->getName() << std::endl;
		} else {
			std::cout << items[i]->getName() << ", ";
		}
	}

}

int Inventory::numberOfItems(){
	return items.size();
}

void Inventory::addItem(Item* item) {
	items.push_back(item);

}

Item* Inventory::findItem(std::string item) { //finds item and returns reference to it
	for (std::vector<Item*>::size_type i = 0; i != items.size(); i++) {
		if (items[i]->getName() == item) {
			return items[i];
		}
	}
	return NULL;
}


Item* Inventory::getItem(std::string item) {
	Item* temp;
	for (std::vector<Item>::size_type i = 0; i != items.size(); i++) {
		if (items[i]->getName() == item) {
			temp = items[i];
			items.erase(items.begin() +i);
			return temp;
		}
	}
	return NULL;
}

