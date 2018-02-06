/*
 * Border.cpp
 *
 *  Created on: Oct 15, 2017
 *      Author: Martynas
 */

#include "Border.h"

Border::Border(std::string direction, std::string name) {
	mDirection = direction;
	mName = name;
	// TODO Auto-generated constructor stub

}

Border::~Border() {
	// TODO Auto-generated destructor stub
}

std::string Border::getName() {
	return mName;
}

std::string Border::getDirection() {
	return mDirection;
}
