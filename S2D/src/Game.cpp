#include "Game.h"

Game::Game() :	playing(true),
				Screen(),
				GFXManager(this),
				Controls(this->getWindow()){
	controls = this;
	screen = this;
	objectManager = this;
	currentScene = NULL;
}

Game::~Game(){
	if(isOpen()){
		close();
	}
}

void Game::changeScreenSize(int x, int y){
	Screen::setScreenSize(x, y);
	if(isOpen()){
		GFXManager::window.setSize(sf::Vector2u(x, y));
	}
}

void Game::loadScene(Scene* scene, bool force){
	if(currentScene != NULL){
		removeObjects(force);
	}
	currentScene = scene;
	std::vector<Object*>* objectsInScene = currentScene->getObjects();
	for(std::vector<Object*>::iterator it = objectsInScene->begin(); it != objectsInScene->end(); it++){
		addObject(*it);
	}
}

//TODO: flesh out settings more.
int Game::init(int settings){
	//start collision listener
	world.SetContactListener(this);
	return initGFXManager(settings);
}

int Game::play(){

	if(isOpen()){
		//first pass displays objects before accepting input
		updateObjects(frameClock.restart());
		draw(this);
		display();
		//MAIN LOOP
		while(playing){
			//capture input
			if(updateControls() == CLOSE){
				close();
				return CLOSE;
			}
			if(currentScene != NULL){
				//update the current scene
				switch(currentScene->update()){
				case -1:
					//the scene is over and the game is over
					return CLOSE;
				case 0:
					//the scene is still playing
					break;
				case 1:
					//the scene is over but the game is not
					return CONTINUE;
				}
			}
			//update objects
			if(updateObjects(frameClock.restart())){
				//draw drawables to buffer
				draw(this);
				//display on screen
				display();
			}
		}
	}
	return CLOSE;
}