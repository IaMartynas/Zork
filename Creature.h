/*
 * Creature.h
 *
 *  Created on: Oct 18, 2017
 *      Author: Martynas
 */

#ifndef CREATURE_H_
#define CREATURE_H_
#include <vector>
#include "Item.h"
#include <string>
#include "Trigger.h"

class Creature {
public:
	Creature(std::string);
	Creature(std::string,std::string);
	virtual ~Creature();
	virtual void addVulnerability(Item*);
	virtual std::string getName();
	virtual std::string getDescription();
	virtual bool isVulnerable(std::string);
	virtual void addTrigger(Trigger*);
	virtual int numOfTriggers();
	virtual Trigger* getTrigger(int);
	virtual void addAttack(Action*);
	virtual Action* getAction(int);
	virtual int numOfAttacks();
private:
	std::vector<Trigger*> triggers;
	std::string mName;
	std::string mStatus;
	std::string mDescription;
	std::vector<Item*> vulnerabilities;
	std::vector<Action*> attack;


};

#endif /* CREATURE_H_ */
