#include "ObjectManager.h"

ObjectManager::ObjectManager() : world(b2Vec2(0.0f, 0.0f)){

	newObjectAdded = false;
	objectCount = 0;

	timeStep = 1.0f / 60.0f;
	velocityIterations = 9;
	positionIterations = 8;

}

ObjectManager::~ObjectManager(){
	//delete objects
	for(std::map<int, QueuePtr>::iterator mi = objects.begin(); mi != objects.end(); mi++){
		QueuePtr temp;
		QueuePtr head;
		head = mi->second;
		while(head != NULL){
			temp = head;
			head = head->next;
			delete(temp);
		}
	}

	//delete topObjects
	for(std::map<int, QueuePtr>::iterator mi = topObjects.begin(); mi != topObjects.end(); mi++){
		QueuePtr temp;
		QueuePtr head;
		head = mi->second;
		while(head != NULL){
			temp = head;
			head = head->next;
			delete(temp);
		}
	}
}

void ObjectManager::setGravity(b2Vec2 newGravity){
	world.SetGravity(newGravity);
}

void ObjectManager::add(Object* object, MapType type, std::map<int, QueuePtr>* tempMap){
	QueuePtr temp;
	if(type == BOTTOM){
		if(!objects.count(object->getLayer())){
			//no elements with this specific layer
			//just insert it into the map
			temp = new struct Node_;
			temp->object = object;
			temp->next = NULL;
			objects[object->getLayer()] = temp;
		}else{
			//1 or more elements with this layer already in the map
			//add it to the list at that index
			temp = objects.find(object->getLayer())->second;
			while(temp->next != NULL){
				temp = temp->next;
			}
			temp->next = new struct Node_;
			temp->next->object = object;
			temp->next->next = NULL;
		}
	}else if(type == TOP){
		if(!topObjects.count(object->getLayer())){
			//no elements with this specific layer
			//just insert it into the map
			temp = new struct Node_;
			temp->object = object;
			temp->next = NULL;
			topObjects[object->getLayer()] = temp;
		}else{
			//1 or more elements with this layer already in the map
			//add it to the list at that index
			//temp = topObjects.find(object->getLayer())->second;
			temp = topObjects[object->getLayer()];
			while(temp->next != NULL){
				temp = temp->next;
			}
			temp->next = new struct Node_;
			temp->next->object = object;
			temp->next->next = NULL;
		}
	}else if(type == TEMP){
		if(!tempMap->count(object->getLayer())){
			//no elements with this specific layer
			//just insert it into the map
			temp = new struct Node_;
			temp->object = object;
			temp->next = NULL;
			(*tempMap)[object->getLayer()] = temp;
		}else{
			//1 or more elements with this layer already in the map
			//add it to the list at that index
			//temp = topObjects.find(object->getLayer())->second;
			temp = tempMap->at(object->getLayer());
			while(temp->next != NULL){
				temp = temp->next;
			}
			temp->next = new struct Node_;
			temp->next->object = object;
			temp->next->next = NULL;
		}
	}
}

void ObjectManager::addObject(Object* object, bool alwaysOnTop){
	if(!alwaysOnTop){
		add(object, BOTTOM);
		newObjectAdded = true;
		objectCount++;
	}else{
		add(object, TOP);
		newObjectAdded = true;
		objectCount++;
	}
	if(object->getBodyDef() != NULL){
		object->initializeBody(world.CreateBody(object->getBodyDef()));
	}
}



bool ObjectManager::removeObject(Object* object){
	//remove box2d body from world
	world.DestroyBody(object->getBody());

	//remove object from draw and update map
	std::map<int, QueuePtr>::iterator mi = objects.find(object->getLayer());
	QueuePtr temp = mi->second;

	if(temp == NULL){
		return false;
	}else if(temp->next == NULL){
		objects.erase(object->getLayer());
		return true;
	}else{
		QueuePtr prev = temp;
		while(temp != NULL){
			if(object->getId() == temp->object->getId()){
				if(temp->next == NULL){
					//node is at the end of the list
					delete(temp);
				}else if(prev == temp){
					//node is at the front of the list
					mi->second = temp->next;
					delete(temp);
				}else{
					//node is in the middle of the list
					prev->next = temp->next;
					delete(temp);
				}
				return true;
			}
			prev = temp;
			temp = temp->next;
		}
	}
	return false;
}

void ObjectManager::removeObjects(bool force){
	//find persistent objects and add them to a vector
	std::vector<Object*> persistentObjects;
	for(std::map<int, QueuePtr>::iterator mi = objects.begin(); mi != objects.end(); mi++){
		QueuePtr temp;
		QueuePtr garbageTemp;
		temp = mi->second;
		while(temp != NULL){
			if(temp->object->isPersistent()){
				persistentObjects.push_back(temp->object);
			}
			garbageTemp = temp;
			temp = temp->next;
			delete(garbageTemp);
		}
	}

	std::vector<Object*> persistentTopObjects;
	for(std::map<int, QueuePtr>::iterator mi = topObjects.begin(); mi != topObjects.end(); mi++){
		QueuePtr temp;
		QueuePtr garbageTemp;
		temp = mi->second;
		while(temp != NULL){
			if(temp->object->isPersistent()){
				persistentTopObjects.push_back(temp->object);
			}
			garbageTemp = temp;
			temp = temp->next;
			delete(garbageTemp);
		}
	}

	//add persistent objects back into the map
	if(!force){
		for(std::vector<Object*>::iterator vi = persistentObjects.begin(); vi != persistentObjects.end(); vi++){
			addObject(*vi);
		}

		for(std::vector<Object*>::iterator vi = persistentTopObjects.begin(); vi != persistentTopObjects.end(); vi++){
			addObject(*vi, true);
		}
	}
}

bool ObjectManager::updateObjects(sf::Time frameTime){
	bool didSomethingUpdate = false;
	bool update = false;

	sf::Clock time;
	time.restart();
	//update box2d world
	world.Step(timeStep, velocityIterations, positionIterations);
	//printf("update world:\t%f\n", time.getElapsedTime().asSeconds() * 1000);
	time.restart();
	//update objects
	for(std::map<int, QueuePtr>::iterator mi = objects.begin(); mi != objects.end(); mi++){
		QueuePtr temp;
		temp = mi->second;
		while(temp != NULL){
			didSomethingUpdate = temp->object->update(frameTime);
			temp = temp->next;
		}
	}
	//printf("update bottom objects:\t%f\n", time.getElapsedTime().asSeconds() * 1000);
	time.restart();
	for(std::map<int, QueuePtr>::iterator mi = topObjects.begin(); mi != topObjects.end(); mi++){
		QueuePtr temp;
		temp = mi->second;
		while(temp != NULL){
			didSomethingUpdate = temp->object->update(frameTime);
			temp = temp->next;
		}
	}
	//printf("update top objects:\t%f\n", time.getElapsedTime().asSeconds() * 1000);
	if(newObjectAdded){
		newObjectAdded = false;
		return true;
	}
	return didSomethingUpdate;
}

std::map<int, QueuePtr>* ObjectManager::getObjects(){
	return &objects;
}

std::map<int, QueuePtr>* ObjectManager::getTopObjects(){
	return &topObjects;
}