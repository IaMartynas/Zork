/*
 * Container.cpp
 *
 *  Created on: Oct 16, 2017
 *      Author: Martynas
 */

#include "Container.h"

Container::Container(std::string name) {
	mName = name;
	mStatus = "";
	// TODO Auto-generated constructor stub

}


Container::~Container() {
	// TODO Auto-generated destructor stub
}

std::string Container::getName(){
	return mName;

}

void Container::addAccepted(Item* item){
	accept.push_back(item);
}

void Container::setStatus(std::string status){
	mStatus = status;
}

int Container::numOfAccepted(){
	return accept.size();
}

std::string Container::getStatus(){
	return mStatus;
}

void Container::updateStatus(std::string newStatus){
	mStatus = newStatus;
}

bool Container::isAccepted(Item* item){
		bool accepted = false;
		for(std::vector<Item*>::size_type i = 0; i != accept.size(); i++){
			if(accept[i] == item){
				accepted = true;
			}

		}

		return accepted;

}

Trigger* Container::getTrigger(int i) {
	if ((std::vector<Trigger*>::size_type) i != mTriggers.size()) {
		return mTriggers[i];
	} else {
		return NULL;
	}
}

void Container::addTrigger(Trigger* trigger){
	mTriggers.push_back(trigger);
}

int Container::numOfTriggers(){
	return mTriggers.size();
}
