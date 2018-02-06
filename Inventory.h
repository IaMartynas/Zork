/*
 * Inventory.h
 *
 *  Created on: Oct 15, 2017
 *      Author: Martynas
 */


#ifndef INVENTORY_H_
#define INVENTORY_H_

#include <string>
#include <vector>
#include <iostream>

#include "Item.h"

class Inventory {
public:
	Inventory();
	virtual ~Inventory();
	virtual void getItems();
	virtual Item* getItem(std::string);
	virtual Item* findItem(std::string);
	virtual void addItem(Item *item);
	virtual int numberOfItems();
private:
	std::vector<Item*> items;;
};

#endif /* INVENTORY_H_ */
