/*
 * Item.cpp
 *
 *  Created on: Oct 15, 2017
 *      Author: Martynas
 */

#include "Item.h"

#include <string>
#include <vector>

Item::Item(std::string name, std::string text) {
	mName = name;
	mText = text;
	mStatus = "";
	// TODO Auto-generated constructor stub

}

Item::Item(std::string name) {
	mName = name;
	mText = "";
	mStatus = "";
	// TODO Auto-generated constructor stub

}

Item::~Item() {
	// TODO Auto-generated destructor stub
}

std::string Item::getName() {
	return mName;
}

std::string Item::getText(){
	return mText;
}

void Item::addAction(Action* action){
	actions.push_back(action);
}

Action* Item::returnAction(int i){
	if((std::vector<Action*>::size_type) i != actions.size()){
		return actions[i];
	} else{
		return NULL;
	}
}
std::string Item::getStatus(){
	return mStatus;
}

void Item::updateStatus(std::string newStatus){
	mStatus = newStatus;
}
