/*
 * Creature.cpp
 *
 *  Created on: Oct 18, 2017
 *      Author: Martynas
 */

#include "Creature.h"
#include <iostream>

Creature::Creature(std::string name) {
	mName = name;
	// TODO Auto-generated constructor stub

}

Creature::Creature(std::string name,std::string description) {
	mDescription = description;
	mName = name;
	// TODO Auto-generated constructor stub

}


Creature::~Creature() {
	// TODO Auto-generated destructor stub
}

void Creature::addVulnerability(Item* item){
	vulnerabilities.push_back(item);
}

bool Creature::isVulnerable(std::string item){
	for(std::vector<Item*>::size_type i = 0; i != vulnerabilities.size(); i++){

 		if(vulnerabilities[i]->getName() == item) return true;
	}
	if(vulnerabilities.size() == 0) return true;

	return false;
}

std::string Creature::getName(){
	return mName;
}

std::string Creature::getDescription(){
	return mDescription;
}

Trigger* Creature::getTrigger(int i){
	if((std::vector<Trigger*>::size_type) i != triggers.size()){
		return triggers[i];
	} else{
		return NULL;
	}
}

int Creature::numOfTriggers(){
	return triggers.size();
}

void Creature::addTrigger(Trigger* trigger){
	triggers.push_back(trigger);
}
void Creature::addAttack(Action* action){
	attack.push_back(action);
}

Action* Creature::getAction(int i){
	if((std::vector<Action*>::size_type) i != attack.size()){
		return attack[i];
	} else{
		return NULL;
	}

}

int Creature::numOfAttacks(){
	return attack.size();
}



