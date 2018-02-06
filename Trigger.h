/*
 * Trigger.h
 *
 *  Created on: Oct 16, 2017
 *      Author: Martynas
 */

#ifndef TRIGGER_H_
#define TRIGGER_H_
#include "Action.h"
#include "Condition.h"
#include <vector>


class Trigger {
public:
	Trigger(std::string, std::string);
	Trigger(std::string);
	virtual ~Trigger();
	virtual void addCondition(Condition*);
	virtual void addAction(Action*);
	virtual Action* returnAction(int);
	virtual Condition* getCondition();
	virtual std::string getCommand();
	virtual std::string getType();
private:
	std::string mType;
	std::string mCommand;
	Condition* mCondition;
	std::vector<Action*> actions;
};// type single, condition :( has), (has leads to object) , (object leads to owner)
//

#endif /* TRIGGER_H_ */
