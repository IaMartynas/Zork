/*
 * Action.cpp
 *
 *  Created on: Nov 4, 2017
 *      Author: Martynas
 */

#include "Action.h"

Action::Action(std::string type, std::string action) {
	mType = type;
	mAction = action;
	// TODO Auto-generated constructor stub

}

Action::~Action() {
	// TODO Auto-generated destructor stub
}

std::string Action::getAction(){
	return mAction;
}

std::string Action::getType(){
	return mType;
}

