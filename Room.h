/*
 * Room.h
 *
 *  Created on: Oct 15, 2017
 *      Author: Martynas
 */

#ifndef ROOM_H_
#define ROOM_H_
#include <string>
#include <vector>
#include "Border.h"
#include "Inventory.h"
#include "Container.h"
#include "Creature.h"
#include "Trigger.h"
class Room {
public:
	//Room(std::string name, std::string description);
	Room(std::string type, std::string name, std::string description);
	virtual std::string getName();
	virtual std::string getDescription();
	virtual std::string getType();
	virtual std::string getStatus();
	virtual void updateStatus(std::string);
	virtual void addCreature(Creature*);
	virtual Creature* getCreature(std::string);
	virtual void addContainer(Container*);
	virtual Container* getContainer(std::string);
	virtual Container* getContainer(int);
	virtual void removeBorder(std::string);
	virtual void removeCreature(std::string);
	virtual void removeContainer(std::string);
	virtual int numOfBorders();
	virtual int numOfContainers();
	virtual void setBorder(Border*);
	virtual Border* getBorder(std::string);
	virtual Border* getBorder(int);
	virtual void getItems();
	virtual void addItem(Item* item);
	virtual void addTrigger(Trigger*);
	virtual Trigger* getTrigger(int);
	virtual Item* giveItem(std::string item);
	virtual int numOfTriggers();
	virtual ~Room();
private:
	std::vector<Border*> borders;
	std::vector<Item*> items;
	std::vector<Container*> containers;
	std::vector<Creature*> creatures;
	std::string mType;
	std::string mName;
	std::string mDescription;
	std::string mStatus;
	std::vector<Trigger*> triggers;
	Inventory mInventory;

};

#endif /* ROOM_H_ */
