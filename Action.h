/*
 * Action.h
 *
 *  Created on: Nov 4, 2017
 *      Author: Martynas
 */

#ifndef ACTION_H_
#define ACTION_H_
#include <string>
class Action {
public:
	Action(std::string, std::string);
	virtual ~Action();
	virtual std::string getType();
	virtual std::string getAction();
private:
	std::string mType;
	std::string mAction;
};

#endif /* ACTION_H_ */
