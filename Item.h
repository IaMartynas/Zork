/*
 * Item.h
 *
 *  Created on: Oct 15, 2017
 *      Author: Martynas
 */

#ifndef ITEM_H_
#define ITEM_H_
#include <string>
#include <vector>
#include "Action.h"

class Item {
public:
	Item(std::string, std::string);
	Item(std::string);
	virtual ~Item();
	virtual std::string getName();
	virtual std::string getText();
	virtual void addAction(Action*);
	virtual Action* returnAction(int);
	virtual std::string getStatus();
	virtual void updateStatus(std::string);
private:
	std::string mName;
	std::string mText;
	std::string mStatus;
	std::vector<Action*> actions;
};

#endif /* ITEM_H_ */
