/*
 * Condition.cpp
 *
 *  Created on: Nov 11, 2017
 *      Author: Martynas
 */

#include "Condition.h"

Condition::Condition(std::string type, std::string object, std::string extra) {
	mType = type;
	mObject = object;
	mExtra = extra;
	// TODO Auto-generated constructor stub

}

Condition::Condition(std::string object, std::string extra) {
	mType = "status";
	mObject = object;
	mExtra = extra;
	// TODO Auto-generated constructor stub

}
Condition::~Condition() {
	// TODO Auto-generated destructor stub
}

std::string Condition::getType(){
	return mType;
}

std::string Condition::getObject(){
	return mObject;
}

std::string Condition::getExtra(){
	return mExtra;
}
