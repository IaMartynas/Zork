/*
 * Container.h
 *
 *  Created on: Oct 16, 2017
 *      Author: Martynas
 */

#ifndef CONTAINER_H_
#define CONTAINER_H_

#include "Inventory.h"
#include "Trigger.h"
#include <vector>

class Container: public Inventory {
public:
	Container(std::string);
	Container(std::string, std::string);
	virtual std::string getName();
	virtual ~Container();
	virtual std::string getStatus();
	virtual void updateStatus(std::string);
	virtual void addTrigger(Trigger*);
	virtual void addAccepted(Item*);
	virtual int numOfAccepted();
	virtual bool isAccepted(Item*);
	virtual Trigger* getTrigger(int);
	virtual int numOfTriggers();
	virtual void setStatus(std::string);
private:
	std::vector<Trigger*> mTriggers;
	std::vector<Item*> accept;
	std::string mName;
	std::string mStatus;
};

#endif /* CONTAINER_H_ */
