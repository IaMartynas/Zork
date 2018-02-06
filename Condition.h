/*
 * Condition.h
 *
 *  Created on: Nov 11, 2017
 *      Author: Martynas
 */

#ifndef CONDITION_H_
#define CONDITION_H_
#include <string>

class Condition {
public:
	Condition(std::string, std::string, std::string);
	Condition(std::string, std::string); //when it doesnt have 'has' atribute, Type status is assigned;
	virtual ~Condition();
	virtual std::string getType();
	virtual std::string getObject();
	virtual std::string getExtra();
private:
	std::string mType;
	std::string mObject;
	std::string mExtra; //status name when type status, owner when type has
};

#endif /* CONDITION_H_ */
