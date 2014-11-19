#include "ManagerObject.h"

ManagerObject::ManagerObject(Game* game) : game(game){
	objectType = MANAGER;
	name = "MANAGER";
}

ManagerObject::ManagerObject(Game* game, std::string name) : game(game){
	objectType = MANAGER;
	this->name = name;
}

bool ManagerObject::update(sf::Time frameTime){

	return false;
}