#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>
#include <iterator>
#include "rapidxml.hpp"
#include "Inventory.h"
#include "Map.h"
#include "Room.h"
#include "Container.h"
#include "Border.h"
#include "Trigger.h"
#include "Creature.h"
#include "Player.h"

using namespace rapidxml;
int command(std::string, Player*, Map, std::map<std::string, Item*>,
		std::map<std::string, Creature*>);
int main(void) {
	std::string in;
	bool debug = false;
	//TODO: debug = true to enable text
	if (debug)
		std::cout << "Parsing input file..." << std::endl;
	xml_document<> doc;
	xml_node<> * root_node;

	// Read the xml file into a vector
	std::ifstream theFile("inputs/samples/triggersample.xml");
	std::vector<char> buffer((std::istreambuf_iterator<char>(theFile)),
			std::istreambuf_iterator<char>());
	buffer.push_back('\0');

	doc.parse<0>(&buffer[0]); // Parse the buffer using the xml file parsing library into doc
	root_node = doc.first_node("map");	// Find root node

	std::map<std::string, Item*> items;
	std::map<std::string, Container*> containers;
	std::map<std::string, Creature*> creatures;

	Map map;

	Item * temp_item;
	Action * temp_action;
	Container * temp_container;
	Trigger * temp_trigger;
	Condition * temp_condition;
	Creature * temp_creature;
	Room * temp_room;
	Border * temp_border;

	// Iterate over the items
	if (root_node->first_node("item")) {
		for (xml_node<> * item_node = root_node->first_node("item"); item_node;
				item_node = item_node->next_sibling("item")) {
			if (item_node->first_node("writing")) {
				if (debug)
					std::cout << "temp_item = new Item(\""
							<< item_node->first_node("name")->value()
							<< "\", \""
							<< item_node->first_node("writing")->value()
							<< "\");" << std::endl;
				temp_item = new Item(item_node->first_node("name")->value(),
						item_node->first_node("writing")->value());
			} else {
				if (debug)
					std::cout << "temp_item = new Item(\""
							<< item_node->first_node("name")->value() << "\");"
							<< std::endl;
				temp_item = new Item(item_node->first_node("name")->value());

			}
			if (item_node->first_node("status")) {
				if (debug)
					std::cout << "temp_item->updateStatus(\""
							<< item_node->first_node("status")->value()
							<< "\");" << std::endl;
				temp_item->updateStatus(
						item_node->first_node("status")->value());
			}
			if (item_node->first_node("turnon")) {
				if (item_node->first_node("turnon")->first_node("print"))
					for (xml_node<> * action_node = (item_node->first_node(
							"turnon")->first_node("print")); action_node;
							action_node = action_node->next_sibling("print")) {
						if (debug)
							std::cout
									<< "temp_action = new Action(\"print\", \""
									<< action_node->value() << "\");"
									<< std::endl;
						temp_action = new Action("print", action_node->value());
						if (debug)
							std::cout << "temp_item->addAction(temp_action);"
									<< std::endl;
						temp_item->addAction(temp_action);
					}
				if (item_node->first_node("turnon")->first_node("action"))
					for (xml_node<> * action_node = (item_node->first_node(
							"turnon")->first_node("action")); action_node;
							action_node = action_node->next_sibling("action")) {
						if (debug)
							std::cout
									<< "temp_action = new Action(\"action\", \""
									<< action_node->value() << "\");"
									<< std::endl;
						temp_action = new Action("action",
								action_node->value());
						if (debug)
							std::cout << "temp_item->addAction(temp_action);"
									<< std::endl;
						temp_item->addAction(temp_action);
					}
			}
			if (debug)
				std::cout << "items[" << item_node->first_node("name")->value()
						<< "] = temp_item;" << std::endl;
			items[item_node->first_node("name")->value()] = temp_item;
		}
	}

	// Iterate over the containers
	if (root_node->first_node("container")) {
		for (xml_node<> * container_node = root_node->first_node("container");
				container_node;
				container_node = container_node->next_sibling("container")) {
			if (container_node->first_node("name")) {
				if (debug)
					std::cout << "temp_container = new Container(\""
							<< container_node->first_node("name")->value()
							<< "\", \""
							<< container_node->first_node("accept")->value()
							<< "\");" << std::endl;

				temp_container = new Container(
						container_node->first_node("name")->value());

			}

			if (container_node->first_node("accept"))
				for (xml_node<> * acceptance_node = container_node->first_node(
						"accept"); acceptance_node; acceptance_node =
						acceptance_node->next_sibling("accept")) {
					if (debug)
						std::cout << "temp_container->addAccepted(items["
								<< acceptance_node->value() << "]);"
								<< std::endl;
					temp_container->addAccepted(
							items[acceptance_node->value()]);
				}

			if (container_node->first_node("status")) {
				if (debug)
					std::cout << "temp_container->updateStatus(\""
							<< container_node->first_node("status")->value()
							<< "\");" << std::endl;
				temp_container->updateStatus(
						container_node->first_node("status")->value());
			}
			if (container_node->first_node("item"))
				for (xml_node<> * item_node = (container_node->first_node(
						"item")); item_node; item_node =
						item_node->next_sibling("item")) {
					if (debug)
						std::cout << "temp_room->addItem(items["
								<< item_node->value() << "]);" << std::endl;
					temp_container->addItem(items[item_node->value()]);
				}

			if (container_node->first_node("trigger")) {
				for (xml_node<> * trigger_node = container_node->first_node(
						"trigger"); trigger_node;
						trigger_node = trigger_node->next_sibling("trigger")) {
					if (trigger_node->first_node("type")) {
						if (trigger_node->first_node("command")) {
							if (debug)
								std::cout << "temp_trigger = new Trigger(\""
										<< trigger_node->first_node("type")->value()
										<< "\", \""
										<< trigger_node->first_node("command")->value()
										<< "\");" << std::endl;
							temp_trigger =
									new Trigger(
											trigger_node->first_node("type")->value(),
											trigger_node->first_node("command")->value());
						} else {
							if (debug)
								std::cout << "temp_trigger = new Trigger(\""
										<< trigger_node->first_node("type")->value()
										<< "\");" << std::endl;
							temp_trigger = new Trigger(
									trigger_node->first_node("type")->value());
						}
					} else {
						if (trigger_node->first_node("command")) {
							if (debug)
								std::cout
										<< "temp_trigger = new Trigger(\"single\", \""
										<< trigger_node->first_node("command")->value()
										<< "\");" << std::endl;
							temp_trigger =
									new Trigger("single",
											trigger_node->first_node("command")->value());
						} else {
							if (debug)
								std::cout
										<< "temp_trigger = new Trigger(\"single\");"
										<< std::endl;
							temp_trigger = new Trigger("single");
						}
					}
					for (xml_node<> * condition_node = trigger_node->first_node(
							"condition"); condition_node; condition_node =
							condition_node->next_sibling("condition")) {
						if (condition_node->first_node("has")) {
							if (debug)
								std::cout << "temp_condition = new Condition(\""
										<< condition_node->first_node("has")->value()
										<< "\", \""
										<< condition_node->first_node("object")->value()
										<< "\", \""
										<< condition_node->first_node("owner")->value()
										<< "\");" << std::endl;
							temp_condition =
									new Condition(
											condition_node->first_node("has")->value(),
											condition_node->first_node("object")->value(),
											condition_node->first_node("owner")->value());
							if (debug)
								std::cout
										<< "temp_trigger->addCondition(temp_condition);"
										<< std::endl;
							temp_trigger->addCondition(temp_condition);
						} else {
							if (debug)
								std::cout << "temp_condition = new Condition(\""
										<< condition_node->first_node("object")->value()
										<< "\", \""
										<< condition_node->first_node("status")->value()
										<< "\");" << std::endl;
							temp_condition =
									new Condition(
											condition_node->first_node("object")->value(),
											condition_node->first_node("status")->value());
							if (debug)
								std::cout
										<< "temp_trigger->addCondition(temp_condition);"
										<< std::endl;
							temp_trigger->addCondition(temp_condition);
						}
					}
					if (trigger_node->first_node("print")) {
						for (xml_node<> * action_node =
								(trigger_node->first_node("print"));
								action_node;
								action_node = action_node->next_sibling(
										"print")) {
							if (debug)
								std::cout
										<< "temp_action = new Action(\"print\", \""
										<< action_node->value() << "\");"
										<< std::endl;
							temp_action = new Action("print",
									action_node->value());
							if (debug)
								std::cout
										<< "temp_trigger->addAction(temp_action);"
										<< std::endl;
							temp_trigger->addAction(temp_action);
						}
					}
					if (trigger_node->first_node("action")) {
						for (xml_node<> * action_node =
								(trigger_node->first_node("action"));
								action_node;
								action_node = action_node->next_sibling(
										"action")) {
							if (debug)
								std::cout
										<< "temp_action = new Action(\"action\", \""
										<< action_node->value() << "\");"
										<< std::endl;
							temp_action = new Action("action",
									action_node->value());
							if (debug)
								std::cout
										<< "temp_trigger->addAction(temp_action);"
										<< std::endl;
							temp_trigger->addAction(temp_action);
						}
					}
					if (debug)
						std::cout << "temp_container->addTrigger(temp_trigger);"
								<< std::endl;
					temp_container->addTrigger(temp_trigger);
				}
			}
			if (debug)
				std::cout << "containers["
						<< container_node->first_node("name")->value()
						<< "] = temp_container;" << std::endl;
			containers[container_node->first_node("name")->value()] =
					temp_container;
		}
	}

	// Iterate over the creatures
	if (root_node->first_node("creature")) {
		for (xml_node<> * creature_node = root_node->first_node("creature");
				creature_node;
				creature_node = creature_node->next_sibling("creature")) {
			if (creature_node->first_node("description")) {
				if (debug)
					std::cout << "temp_creature = new Creature(\""
							<< creature_node->first_node("name")->value()
							<< "\", \""
							<< creature_node->first_node("description")->value()
							<< "\");" << std::endl;
				temp_creature = new Creature(
						creature_node->first_node("name")->value(),
						creature_node->first_node("description")->value());
			} else {
				if (debug)
					std::cout << "temp_creature = new Creature(\""
							<< creature_node->first_node("name")->value()
							<< "\");" << std::endl;
				temp_creature = new Creature(
						creature_node->first_node("name")->value());
			}
			if (creature_node->first_node("vulnerability"))
				for (xml_node<> * vulnerability_node =
						creature_node->first_node("vulnerability");
						vulnerability_node;
						vulnerability_node = vulnerability_node->next_sibling(
								"vulnerability")) {
					if (debug)
						std::cout << "temp_creature->addVulnerability(items["
								<< vulnerability_node->value() << "]);"
								<< std::endl;
					temp_creature->addVulnerability(
							items[vulnerability_node->value()]);
				}

			if (creature_node->first_node("attack")) {
				for (xml_node<> * attack_node = creature_node->first_node(
						"attack"); attack_node;
						attack_node = attack_node->next_sibling("attack")) {
					if (attack_node->first_node("print"))
						for (xml_node<> * action_node =
								(creature_node->first_node("attack")->first_node(
										"print")); action_node; action_node =
								action_node->next_sibling("print")) {
							if (debug)
								std::cout
										<< "temp_action = new Action(\"print\", \""
										<< action_node->value() << "\");"
										<< std::endl;
							temp_action = new Action("print",
									action_node->value());
							if (debug)
								std::cout
										<< "temp_creature->addAttack(temp_action);"
										<< std::endl;
							temp_creature->addAttack(temp_action);
						}
					if (attack_node->first_node("action"))
						for (xml_node<> * action_node =
								(creature_node->first_node("attack")->first_node(
										"action")); action_node; action_node =
								action_node->next_sibling("action")) {
							if (debug)
								std::cout
										<< "temp_action = new Action(\"action\", \""
										<< action_node->value() << "\");"
										<< std::endl;
							temp_action = new Action("action",
									action_node->value());
							if (debug)
								std::cout
										<< "temp_creature->addAttack(temp_action);"
										<< std::endl;
							temp_creature->addAttack(temp_action);
						}
				}
			}

			if (creature_node->first_node("trigger")) {
				for (xml_node<> * trigger_node = creature_node->first_node(
						"trigger"); trigger_node;
						trigger_node = trigger_node->next_sibling("trigger")) {
					if (trigger_node->first_node("type")) {
						if (trigger_node->first_node("command")) {
							if (debug)
								std::cout << "temp_trigger = new Trigger(\""
										<< trigger_node->first_node("type")->value()
										<< "\", \""
										<< trigger_node->first_node("command")->value()
										<< "\");" << std::endl;
							temp_trigger =
									new Trigger(
											trigger_node->first_node("type")->value(),
											trigger_node->first_node("command")->value());
						} else {
							if (debug)
								std::cout << "temp_trigger = new Trigger(\""
										<< trigger_node->first_node("type")->value()
										<< "\");" << std::endl;
							temp_trigger = new Trigger(
									trigger_node->first_node("type")->value());
						}
					} else {
						if (trigger_node->first_node("command")) {
							if (debug)
								std::cout
										<< "temp_trigger = new Trigger(\"single\", \""
										<< trigger_node->first_node("command")->value()
										<< "\");" << std::endl;
							temp_trigger =
									new Trigger("single",
											trigger_node->first_node("command")->value());
						} else {
							if (debug)
								std::cout
										<< "temp_trigger = new Trigger(\"single\");"
										<< std::endl;
							temp_trigger = new Trigger("single");
						}
					}
					for (xml_node<> * condition_node = trigger_node->first_node(
							"condition"); condition_node; condition_node =
							condition_node->next_sibling("condition")) {
						if (condition_node->first_node("has")) {
							if (debug)
								std::cout << "temp_condition = new Condition(\""
										<< condition_node->first_node("has")->value()
										<< "\", \""
										<< condition_node->first_node("object")->value()
										<< "\", \""
										<< condition_node->first_node("owner")->value()
										<< "\");" << std::endl;
							temp_condition =
									new Condition(
											condition_node->first_node("has")->value(),
											condition_node->first_node("object")->value(),
											condition_node->first_node("owner")->value());
							if (debug)
								std::cout
										<< "temp_trigger->addCondition(temp_condition);"
										<< std::endl;
							temp_trigger->addCondition(temp_condition);
						} else {
							if (debug)
								std::cout << "temp_condition = new Condition(\""
										<< condition_node->first_node("object")->value()
										<< "\", \""
										<< condition_node->first_node("status")->value()
										<< "\");" << std::endl;
							temp_condition =
									new Condition(
											condition_node->first_node("object")->value(),
											condition_node->first_node("status")->value());
							if (debug)
								std::cout
										<< "temp_trigger->addCondition(temp_condition);"
										<< std::endl;
							temp_trigger->addCondition(temp_condition);
						}
					}
					if (trigger_node->first_node("print"))
						for (xml_node<> * action_node =
								(trigger_node->first_node("print"));
								action_node;
								action_node = action_node->next_sibling(
										"print")) {
							if (debug)
								std::cout
										<< "temp_action = new Action(\"print\", \""
										<< action_node->value() << "\");"
										<< std::endl;
							temp_action = new Action("print",
									action_node->value());
							if (debug)
								std::cout
										<< "temp_trigger->addAction(temp_action);"
										<< std::endl;
							temp_trigger->addAction(temp_action);
						}
					if (trigger_node->first_node("action"))
						for (xml_node<> * action_node =
								(trigger_node->first_node("action"));
								action_node;
								action_node = action_node->next_sibling(
										"action")) {
							if (debug)
								std::cout
										<< "temp_action = new Action(\"action\", \""
										<< action_node->value() << "\");"
										<< std::endl;
							temp_action = new Action("action",
									action_node->value());
							if (debug)
								std::cout
										<< "temp_trigger->addAction(temp_action);"
										<< std::endl;
							temp_trigger->addAction(temp_action);
						}
					if (debug)
						std::cout << "temp_creature->addTrigger(temp_trigger);"
								<< std::endl;
					temp_creature->addTrigger(temp_trigger);
				}
			}
			if (debug)
				std::cout << "creatures["
						<< creature_node->first_node("name")->value()
						<< "] = temp_creature;" << std::endl;
			creatures[creature_node->first_node("name")->value()] =
					temp_creature;
		}
	}

	// Iterate over the rooms
	for (xml_node<> * room_node = root_node->first_node("room"); room_node;
			room_node = room_node->next_sibling("room")) {
		if (room_node->first_node("type")) {
			if (debug)
				std::cout << "temp_room = new Room(\""
						<< room_node->first_node("type")->value() << "\", \""
						<< room_node->first_node("name")->value() << "\", \""
						<< room_node->first_node("description")->value()
						<< "\");" << std::endl;
			temp_room = new Room(room_node->first_node("type")->value(),
					room_node->first_node("name")->value(),
					room_node->first_node("description")->value());
		} else {
			if (debug)
				std::cout << "temp_room = new Room(\"regular\", \""
						<< room_node->first_node("name")->value() << "\", \""
						<< room_node->first_node("description")->value()
						<< "\");" << std::endl;
			temp_room = new Room("regular",
					room_node->first_node("name")->value(),
					room_node->first_node("description")->value());
		}
		if (room_node->first_node("status")) {
			if (debug)
				std::cout << "temp_room->updateStatus(\""
						<< room_node->first_node("status")->value() << "\");"
						<< std::endl;
			temp_room->updateStatus(room_node->first_node("status")->value());
		}
		if (room_node->first_node("border"))
			for (xml_node<> * border_node = (room_node->first_node("border"));
					border_node;
					border_node = border_node->next_sibling("border")) {
				if (debug)
					std::cout << "temp_border = new Border(\""
							<< border_node->first_node("direction")->value()
							<< "\", \""
							<< border_node->first_node("name")->value()
							<< "\");" << std::endl;
				temp_border = new Border(
						border_node->first_node("direction")->value(),
						border_node->first_node("name")->value());
				if (debug)
					std::cout << "temp_room->setBorder(temp_border);"
							<< std::endl;
				temp_room->setBorder(temp_border);
			}
		if (room_node->first_node("container"))
			for (xml_node<> * container_node = (room_node->first_node(
					"container")); container_node; container_node =
					container_node->next_sibling("container")) {
				if (debug)
					std::cout << "temp_room->addContainer(containers["
							<< container_node->value() << "]);" << std::endl;
				temp_room->addContainer(containers[container_node->value()]);
			}
		if (room_node->first_node("item"))
			for (xml_node<> * item_node = (room_node->first_node("item"));
					item_node; item_node = item_node->next_sibling("item")) {
				if (debug)
					std::cout << "temp_room->addItem(items["
							<< item_node->value() << "]);" << std::endl;
				temp_room->addItem(items[item_node->value()]);
			}
		if (room_node->first_node("creature"))
			for (xml_node<> * creature_node =
					(room_node->first_node("creature")); creature_node;
					creature_node = creature_node->next_sibling("creature")) {
				if (debug)
					std::cout << "temp_room->addCreature(creatures["
							<< creature_node->value() << "]);" << std::endl;
				temp_room->addCreature(creatures[creature_node->value()]);
			}
		if (room_node->first_node("trigger")) {
			for (xml_node<> * trigger_node = room_node->first_node("trigger");
					trigger_node;
					trigger_node = trigger_node->next_sibling("trigger")) {
				if (trigger_node->first_node("type")) {
					if (trigger_node->first_node("command")) {
						if (debug)
							std::cout << "temp_trigger = new Trigger(\""
									<< trigger_node->first_node("type")->value()
									<< "\", \""
									<< trigger_node->first_node("command")->value()
									<< "\");" << std::endl;
						temp_trigger = new Trigger(
								trigger_node->first_node("type")->value(),
								trigger_node->first_node("command")->value());
					} else {
						if (debug)
							std::cout << "temp_trigger = new Trigger(\""
									<< trigger_node->first_node("type")->value()
									<< "\");" << std::endl;
						temp_trigger = new Trigger(
								trigger_node->first_node("type")->value());
					}
				} else {
					if (trigger_node->first_node("command")) {
						if (debug)
							std::cout
									<< "temp_trigger = new Trigger(\"single\", \""
									<< trigger_node->first_node("command")->value()
									<< "\");" << std::endl;
						temp_trigger = new Trigger("single",
								trigger_node->first_node("command")->value());
					} else {
						if (debug)
							std::cout
									<< "temp_trigger = new Trigger(\"single\");"
									<< std::endl;
						temp_trigger = new Trigger("single");
					}
				}
				for (xml_node<> * condition_node = trigger_node->first_node(
						"condition"); condition_node; condition_node =
						condition_node->next_sibling("condition")) {
					if (condition_node->first_node("has")) {
						if (debug)
							std::cout << "temp_condition = new Condition(\""
									<< condition_node->first_node("has")->value()
									<< "\", \""
									<< condition_node->first_node("object")->value()
									<< "\", \""
									<< condition_node->first_node("owner")->value()
									<< "\");" << std::endl;
						temp_condition = new Condition(
								condition_node->first_node("has")->value(),
								condition_node->first_node("object")->value(),
								condition_node->first_node("owner")->value());
						if (debug)
							std::cout
									<< "temp_trigger->addCondition(temp_condition);"
									<< std::endl;
						temp_trigger->addCondition(temp_condition);
					} else {
						if (debug)
							std::cout << "temp_condition = new Condition(\""
									<< condition_node->first_node("object")->value()
									<< "\", \""
									<< condition_node->first_node("status")->value()
									<< "\");" << std::endl;
						temp_condition = new Condition(
								condition_node->first_node("object")->value(),
								condition_node->first_node("status")->value());
						if (debug)
							std::cout
									<< "temp_trigger->addCondition(temp_condition);"
									<< std::endl;
						temp_trigger->addCondition(temp_condition);
					}
				}
				if (room_node->first_node("trigger")->first_node("print"))
					for (xml_node<> * action_node = (trigger_node->first_node(
							"print")); action_node;
							action_node = action_node->next_sibling("print")) {
						if (debug)
							std::cout
									<< "temp_action = new Action(\"print\", \""
									<< action_node->value() << "\");"
									<< std::endl;
						temp_action = new Action("print", action_node->value());
						if (debug)
							std::cout << "temp_trigger->addAction(temp_action);"
									<< std::endl;
						temp_trigger->addAction(temp_action);
					}
				if (trigger_node->first_node("action"))
					for (xml_node<> * action_node = (trigger_node->first_node(
							"action")); action_node;
							action_node = action_node->next_sibling("action")) {
						if (debug)
							std::cout
									<< "temp_action = new Action(\"action\", \""
									<< action_node->value() << "\");"
									<< std::endl;
						temp_action = new Action("action",
								action_node->value());
						if (debug)
							std::cout << "temp_trigger->addAction(temp_action);"
									<< std::endl;
						temp_trigger->addAction(temp_action);
					}
				if (debug)
					std::cout << "temp_room->addTrigger(temp_trigger);"
							<< std::endl;
				temp_room->addTrigger(temp_trigger);
			}
		}
		if (debug)
			std::cout << "map.addRoom(temp_room);" << std::endl;
		map.addRoom(temp_room);
	}
	Player* player = new Player(map.findRoom("Entrance")); //initializing player in 'main' room

	std::cout << player->getCurrentRoom()->getDescription() << std::endl;

	while (true) {
		std::cout << "> ";
		getline(std::cin, in);
		if ((player->getCurrentRoom()->numOfTriggers()) > 0) { // if room has a trigger
			for (int i = 0; i < player->getCurrentRoom()->numOfTriggers();
					i++) { //for each trigger

				if (player->getCurrentRoom()->getTrigger(i)->getCommand()
						== in) { //if command matches command in the triger
					Condition* temp =
							player->getCurrentRoom()->getTrigger(i)->getCondition();
					bool hasType = false;
					if (temp->getType() == "yes" || temp->getType() == "no")
						hasType = true;
					if (hasType) {
						if ((temp->getType() == "no" //false
						&& player->getItemFromInventory( //false
								temp->getObject()) == NULL)
								|| (temp->getType() == "yes"
										&& player->getItemFromInventory(
												temp->getObject()))) {
							Trigger* temp_trig =
									player->getCurrentRoom()->getTrigger(i);
							Action* temp;
							for (int j = 0;
									(temp_trig->returnAction(j)) != NULL; j++) {
								temp = temp_trig->returnAction(j);
								if (temp->getType() == "print") {
									std::cout << temp->getAction() << std::endl;
								} else {
									if (command(temp->getAction(), player, map,
											items, creatures) == 0) {
										return 0; //recursion
									}
								}
							}
						} else {
							if (command(in, player, map, items, creatures)
									== 0) {
								return 0;
							}
						}
					} else { // type isn't "has"
						if (player->getCurrentRoom()->getContainer(
								temp->getObject())->getStatus()
								== temp->getExtra()) {
							Trigger* temp_trig =
									player->getCurrentRoom()->getTrigger(i);
							Action* temp;
							for (int j = 0;
									(temp_trig->returnAction(j)) != NULL; j++) {
								temp = temp_trig->returnAction(j);
								if (temp->getType() == "print") {
									std::cout << temp->getAction() << std::endl;
								} else {
									if (command(temp->getAction(), player, map,
											items, creatures) == 0) {
										return 0; //recursion
									}
								}
							}
							break;
						} //get items in the players room and get its status
						else { //execute normal comands
							if (in != ""
									&& command(in, player, map, items,
											creatures) == 0) {
								return 0;
							}
							break;
						}
					}
				} else if (i == player->getCurrentRoom()->numOfTriggers() - 1) { //make sure we looked through all triggers before proceeding
					if (in != ""
							&& command(in, player, map, items, creatures)
									== 0) {
						return 0;
					}
				}
			}
		} else if (in != ""
				&& command(in, player, map, items, creatures) == 0) {
			return 0;
		}
	}
}

int command(std::string in, Player* player, Map map,
		std::map<std::string, Item*> items,
		std::map<std::string, Creature*> creatures) {
	std::vector<std::string> input;
	std::istringstream iss(in);
	copy(std::istream_iterator<std::string>(iss),
			std::istream_iterator<std::string>(), back_inserter(input));
	try {
		if (input.at(0) == "n")
			player->Walk("north", map);
		else if (input.at(0) == "e")
			player->Walk("east", map);
		else if (input.at(0) == "s")
			player->Walk("south", map);
		else if (input.at(0) == "w")
			player->Walk("west", map);
		else if (input.at(0) == "i")
			player->getInventory();
		else if (input.at(0) == "take")
			player->takeItem(input.at(1));
		else if (input.at(0) == "drop")
			player->dropItem(input.at(1));
		else if (input.at(0) == "read")
			player->readItem(input.at(1));
		else if (input.at(0) == "open" && input.at(1) == "exit") {
			if (player->getCurrentRoom()->getType() == "exit") {
				std::cout << "Game Over" << std::endl;
				return 0;
			} else {
				std::cout << "Room is not an exit." << std::endl;
			}
		} else if (input.at(0) == "open")
			player->openContainer(input.at(1));
		else if (input.at(0) == "put" && input.at(2) == "in") {
			Item* placedItem = player->getItemFromInventory(input.at(1));
			if (placedItem == NULL) {
				std::cout << "No such object found." << std::endl;
			} else {
				Container* foundContainer =
						player->getCurrentRoom()->getContainer(input.at(3));
				if (foundContainer == NULL) {
					std::cout << "No such container found." << std::endl;
				} else {
					if (foundContainer->numOfAccepted() == 0) {
						foundContainer->addItem(placedItem);
						player->removeItem(input.at(1));
						std::cout << "Item " << placedItem->getName()
								<< " added to " << foundContainer->getName()
								<< "." << std::endl;
					} else {
						if (foundContainer->isAccepted(placedItem)) { //accepted item

							for (int i = 0; i < foundContainer->numOfTriggers();
									i++) {

								Trigger* temp_trig = foundContainer->getTrigger(
										i);
								Action* temp;
								for (int j = 0;
										(temp_trig->returnAction(j)) != NULL;
										j++) {
									temp = temp_trig->returnAction(j);
									if (temp->getType() == "print") {
										std::cout << temp->getAction()
												<< std::endl;
									} else {
										if (command(temp->getAction(), player,
												map, items, creatures) == 0) {
											return 0;				//recursion
										}
									}
								}
							}
							foundContainer->addItem(placedItem);
							player->removeItem(input.at(1));
						} else { //not accepted item
							std::cout << placedItem->getName()
									<< " is not accepted by the "
									<< foundContainer->getName() << "."
									<< std::endl;
						}
					}
				}
			}
		}

		else if (input.at(0) == "attack" && input.at(2) == "with") { //check all conditions
			Item* weapon = player->getItemFromInventory(input.at(3));
			if (weapon == NULL) {
				std::cout << "No such object found." << std::endl;
			} else {
				Creature* victim = player->getCurrentRoom()->getCreature(
						input.at(1));

				if (victim == NULL) {
					std::cout << "No such creature exists." << std::endl;
					return 1;
				} else {
					if (victim->isVulnerable(weapon->getName())) { //might not have triggers?
						if ((victim->numOfTriggers()) > 0) { // if victim has triggers
							for (int i = 0; i < victim->numOfTriggers(); i++) { //for each trigger
								if (victim->getTrigger(i)->getCommand() == in
										|| victim->getTrigger(i)->getCommand()
												== "") { //if command matches command in the triger
									Condition* temp =
											victim->getTrigger(i)->getCondition();
									bool hasType = false;
									if (temp->getType() == "yes"
											|| temp->getType() == "no")
										hasType = true;
									if (hasType) {
										if ((temp->getType() == "no"
												&& player->getItemFromInventory(
														temp->getObject())
														== NULL)
												|| (temp->getType() == "yes"
														&& player->getItemFromInventory(
																temp->getObject()))) {
											Trigger* temp_trig =
													victim->getTrigger(i);
											Action* temp;
											for (int j = 0;
													(temp_trig->returnAction(j))
															!= NULL; j++) {
												temp = temp_trig->returnAction(
														j);
												if (temp->getType()
														== "print") {
													std::cout
															<< temp->getAction()
															<< std::endl;
												} else {
													if (temp->getAction()
															!= in) {
														if (command(
																temp->getAction(),
																player, map,
																items,
																creatures)
																== 0) {
															return 0; //recursion
														}
													}
												}
											}
										} else {
											std::cout << "Condition not met"
													<< std::endl;
										}
									} else { // type isn't "has"
										if (player->getItemFromInventory(
												temp->getObject())->getStatus()
												== temp->getExtra()) {
											Trigger* temp_trig =
													victim->getTrigger(i);
											Action* temp;
											for (int j = 0;
													(temp_trig->returnAction(j))
															!= NULL; j++) {
												temp = temp_trig->returnAction(
														j);
												if (temp->getType()
														== "print") {
													std::cout
															<< temp->getAction()
															<< std::endl;
												} else {
													if (temp->getAction()
															!= in) {
														if (command(
																temp->getAction(),
																player, map,
																items,
																creatures)
																== 0) {
															return 0; //recursion
														}
													}
												}
											}
											break;
										} //get items in the players room and get its status
										else { //if it has a necessary item then proceed
											std::cout << "You assault the "
													<< input.at(1)
													<< " with the "
													<< input.at(3) << "."
													<< std::endl;
											break;
										}
									}

								} else if (i == victim->numOfTriggers() - 1) { //maybe doesnt have a command?
									if (in != ""
											&& command(in, player, map, items,
													creatures) == 0) {
										return 0;
									}
								}
							}
						} else { //doesnt have triggers
							if (victim->numOfAttacks() == 0) {
								std::cout << "You assaulted "
										<< victim->getName() << " with "
										<< weapon->getName() << "."
										<< std::endl;
								if (command("Delete " + victim->getName(),
										player, map, items, creatures) == 0) {
									return 0;
								}
							} else { //has some attack elemenets
								Action* temp;
								for (int k = 0; victim->getAction(k) != NULL;
										k++) {

									temp = victim->getAction(k);
									if (temp->getType() == "print") {
										std::cout << temp->getAction()
												<< std::endl;
									} else {
										if (command(temp->getAction(), player,
												map, items, creatures) == 0) {
											return 0; //recursion
										}
									}
								}
								//break;

							}
						}

					} else {
						std::cout << victim->getName()
								<< " is not vulnerable to " << weapon->getName()
								<< "." << std::endl;
					}
				}
			}
		}

		else if (input.at(0) == "turn" && input.at(1) == "on") {
			Item* itemToActivate = player->getItemFromInventory(input.at(2));
			if (itemToActivate == NULL) {
				std::cout << "No such object found." << std::endl;
			} else {
				Action* temp;
				for (int i = 0; (itemToActivate->returnAction(i)) != NULL;
						i++) {
					temp = itemToActivate->returnAction(i);
					if (temp->getType() == "print") {
						std::cout << temp->getAction() << std::endl;
					} else {
						if (command(temp->getAction(), player, map, items,
								creatures) == 0) {
							return 0; //recursion
						}
					}
				}
			}
		}

		else if (input.at(0) == "Add" && input.at(2) == "to") {
			Room* foundRoom = map.findRoom(input.at(3));
			Creature* foundCreature = creatures[input.at(1)];
			Item* foundItem = items[input.at(1)];
			if (foundRoom != NULL) {
				if (foundCreature != NULL) {
					foundRoom->addCreature(foundCreature);
				} else if (foundItem != NULL) {
					foundRoom->addItem(foundItem);
				} else {
					std::cout << "Error not found" << std::endl;
				}
			} else {
				Container* foundContainer = map.findContainer(input.at(3));
				if (foundContainer != NULL && foundItem != NULL) {
					foundContainer->addItem(foundItem);
				} else {
					std::cout << "Error not found" << std::endl;
				}

			}
		} else if (input.at(0) == "Delete") { //look if its name of room, no then look into the room look for container and item in it if no then look for creature

			Item* userItem = player->removeItem(input.at(1));
			if (userItem != NULL) {
				return 1;
			}

			for (int i = 0; i < map.numOfRooms(); i++) {
				Room* foundRoom = map.getRoom(i);
				if (foundRoom->getName() == input.at(1)) { //if the name was a room then remove it from neighbours
					for (int k = 0; k < foundRoom->numOfBorders(); k++) { //look into each border
						Border* border = foundRoom->getBorder(k);
						if (border != NULL) {
							Room* borderRoom = map.findRoom(border);
							borderRoom->removeBorder(foundRoom->getName());
						}
					}
					break;
				} else {
					Item* foundItem = foundRoom->giveItem(input.at(1));

					if (foundItem != NULL) {
						break;

					} else {
						Creature* foundCreature = foundRoom->getCreature(
								input.at(1));
						if (foundCreature != NULL) { //if is a creature
							foundRoom->removeCreature(input.at(1));
							break;
						} else { //then container or item in one of them
							for (int j = 0; j < foundRoom->numOfContainers();
									i++) {
								Container* foundContainer =
										foundRoom->getContainer(j);
								if (foundContainer->getName() == input.at(1)) {
									foundRoom->removeContainer(input.at(1));

									break;
								}
								break;
							}
						}
					}
				}
			}

		} else if (input.at(0) == "Update" && input.at(2) == "to") {
			Item* itemToUpdate = player->getItemFromInventory(input.at(1));
			if (itemToUpdate == NULL) {
				Container* containerToUpdate =
						player->getCurrentRoom()->getContainer(input.at(1));
				if (containerToUpdate == NULL) {
					std::cout << "Object not found" << std::endl;
				} else {
					containerToUpdate->updateStatus(input.at(3));
				}
			} else {
				itemToUpdate->updateStatus(input.at(3));
			}
		} else if (input.at(0) == "Game" && input.at(1) == "Over") {
			std::cout << "Victory!" << std::endl;
			return 0;

		} else

			std::cout << "Sorry what?" << std::endl;
		input.clear();

	} catch (const std::out_of_range& e) {
		std::cout << in << " what?" << std::endl;
		return 1;
	}
	return 1;

}

