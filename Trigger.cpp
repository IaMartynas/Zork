/*
 * Trigger.cpp
 *
 *  Created on: Oct 16, 2017
 *      Author: Martynas
 */

#include "Trigger.h"
#include <string>

Trigger::Trigger(std::string type, std::string command) {
	mType = type;
	mCommand = command;
	mCondition = NULL;
	// TODO Auto-generated constructor stub

}

Trigger::Trigger(std::string type) {
	mType = type;
	mCommand = "";
	mCondition = NULL;
	// TODO Auto-generated constructor stub

}

Trigger::~Trigger() {
	// TODO Auto-generated destructor stub
}
Condition* Trigger::getCondition() {
	return mCondition;

}

void Trigger::addAction(Action* action) {
	actions.push_back(action);
}

Action* Trigger::returnAction(int i) {
	if ((std::vector<Action*>::size_type) i != actions.size()) {
		return actions[i];
	} else {
		return NULL;
	}
}

void Trigger::addCondition(Condition* condition){
	mCondition= condition;
}

std::string Trigger::getCommand(){
	return mCommand;
}

std::string Trigger::getType(){
	return mType;
}
