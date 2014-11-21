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
#include "GFXManager.h"

GFXManager::GFXManager(Screen* screen) : isClear(true), screen(screen){
	
}

GFXManager::~GFXManager(){
	if(window.isOpen()){
		window.close();
	}
}

int GFXManager::initGFXManager(int settings){
	mode.height = screen->getH();
	mode.width = screen->getW();
	if((FULL_SCREEN | settings) == settings){
		window.create(mode, "S2D!", sf::Style::Fullscreen);
	}else{
		window.create(mode, "S2D!");
	}
	if(window.isOpen()){
		if((VSYNC | settings) == settings){
			window.setVerticalSyncEnabled(true);
		}
		return 0;
	}else{
		return -1;
	}
}

void GFXManager::draw(ObjectManager* objectManager){
	std::map<int, QueuePtr>* objects = objectManager->getObjects();
	//clear screen
	window.clear();
	isClear = true;
	//draw objects in main object map
	for(std::map<int, QueuePtr>::iterator mi = objects->begin(); mi != objects->end(); mi++){
		QueuePtr temp = mi->second;
		while(temp != NULL){
			//only draw the object if it is drawable and is on the screen
			if(temp->object->isDrawable() && temp->object->isOnScreen()){
				//update the camera if there is one
				if(temp->object->hasCameraAttached()){
					screen->updateCamera();
					window.setView(screen->getCamera());
				}
				if(temp->object->hasGLSLShader()){
					window.draw(*temp->object->getDrawable(), temp->object->getShader());
				}else{
					window.draw(*temp->object->getDrawable());
				}
			}
			temp = temp->next;
		}
	}

	objects = objectManager->getTopObjects();
	//draw objects from secondary object queue
	for(std::map<int, QueuePtr>::iterator mi = objects->begin(); mi != objects->end(); mi++){
		QueuePtr temp = mi->second;
		while(temp != NULL){
			//only draw the object if it is drawable and is on the screen
			if(temp->object->isDrawable() && temp->object->isOnScreen()){
				//update the camera if there is one
				if(temp->object->hasCameraAttached()){
					screen->updateCamera();
					window.setView(screen->getCamera());
				}
				window.draw(*temp->object->getDrawable());
			}
			temp = temp->next;
		}
	}
}

int GFXManager::display(){
	//only display if window is clear
	if(isClear){
		window.display();
		isClear = false;
		return 1;
	}
	return 0;
}

bool GFXManager::isOpen(){
	return window.isOpen();
}

void GFXManager::close(){
	window.close();
}

sf::RenderWindow& GFXManager::getWindow(){
	return window;
}