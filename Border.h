/*
 * Border.h
 *
 *  Created on: Oct 15, 2017
 *      Author: Martynas
 */

#ifndef BORDER_H_
#define BORDER_H_
#include <string>
class Border {
public:
	Border(std::string, std::string);
	virtual std::string getName();
	virtual std::string getDirection();
	virtual ~Border();
private:
	std::string mDirection;
	std::string mName;

};

#endif /* BORDER_H_ */
