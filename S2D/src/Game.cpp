// Copyright (C) 2014 Doug Madden (dmadden772@gmail.com)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
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