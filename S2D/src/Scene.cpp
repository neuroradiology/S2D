#include "Scene.h"

Scene::Scene(Game* game) : game(game){

}

void Scene::add(Object* object){
	objects.push_back(object);
}

std::vector<Object*>* Scene::getObjects(){
	return &objects;
}