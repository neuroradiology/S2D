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