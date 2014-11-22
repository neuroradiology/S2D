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
#include "Screen.h"

Screen::Screen() : screenSizeW(480), screenSizeH(320){
	camera.setCenter(screenSizeW / 2.0f, screenSizeH / 2.0f);
}

Screen::Screen(int w, int h) : screenSizeW(w), screenSizeH(h){
	camera.setCenter(screenSizeW / 2.0f, screenSizeH / 2.0f);
}

void Screen::setScreenSize(int w, int h){
	screenSizeW = w;
	screenSizeH = h;
	camera.setCenter(screenSizeW / 2.0f, screenSizeH / 2.0f);
}

unsigned int Screen::getH(){
	return screenSizeH;
}

unsigned int Screen::getW(){
	return screenSizeW;
}

void Screen::attachCamera(Object* object){
	camera.setCenter(object->getPosition().x, object->getPosition().y);
	camera.setSize((float)screenSizeW, (float)screenSizeH);
	objectWithCamera = object;
	objectWithCamera->attachCamera();
}

void Screen::updateCamera(){
	camera.setCenter(objectWithCamera->getPosition().x, objectWithCamera->getPosition().y);
	camera.setRotation(objectWithCamera->getBody()->GetAngle() * RADTODEG);
}

sf::View Screen::getCamera(){
	return camera;
}

sf::Vector2f Screen::getCameraPosition(){
	return sf::Vector2f(camera.getCenter().x - (screenSizeW / 2.0f), camera.getCenter().y - (screenSizeH / 2.0f));
}

bool Screen::inView(Object* object){
	sf::Vector2f screenSize(1.25f * screenSizeW, 1.25f * screenSizeH);
	sf::Vector2f screenPosition(getCameraPosition().x - ((screenSize.x - screenSizeW) / 2.0f), getCameraPosition().y - ((screenSize.y - screenSizeH) / 2.0f));
	sf::FloatRect screenRect(screenPosition, screenSize);
	sf::FloatRect rect(object->getPosition(), object->getSize());

	return rect.intersects(screenRect);
}

bool Screen::inView(sf::Sprite* sprite){
	//extend the screen to be 25% larger to account for the edges
	sf::Vector2f screenSize(1.25f * screenSizeW, 1.25f * screenSizeH);
	sf::Vector2f screenPosition(getCameraPosition().x - ((screenSize.x - screenSizeW) / 2.0f), getCameraPosition().y - ((screenSize.y - screenSizeH) / 2.0f));
	sf::FloatRect screenRect(screenPosition, screenSize);
	sf::FloatRect spriteRect(sprite->getPosition(), sf::Vector2f((float)sprite->getTexture()->getSize().x, (float)sprite->getTexture()->getSize().y));
	
	return spriteRect.intersects(screenRect);
}

bool Screen::inView(sf::CircleShape* circle){
	//extend the screen to be 25% larger to account for the edges when there is rotation
	sf::Vector2f screenSize(1.25f * screenSizeW, 1.25f * screenSizeH);
	sf::Vector2f screenPosition(getCameraPosition().x - ((screenSize.x - screenSizeW) / 2), getCameraPosition().y - ((screenSize.y - screenSizeH) / 2));
	sf::FloatRect screenRect(screenPosition, screenSize);
	sf::FloatRect circleRect(circle->getPosition(), sf::Vector2f((float)circle->getTextureRect().width, (float)circle->getTextureRect().height));
	
	return circleRect.intersects(screenRect);
}

bool Screen::inView(sf::Text* text){
	//FIXME: fix this
	bool onScreen = true;
	if(text->getPosition().x + (text->getCharacterSize() * text->getString().getSize()) < getCameraPosition().x){
		onScreen = false;
	}
	if(text->getPosition().x > getCameraPosition().x + screenSizeW){
		onScreen = false;
	}
	if(text->getPosition().y + text->getCharacterSize() < getCameraPosition().y){
		onScreen = false;
	}
	if(text->getPosition().y > getCameraPosition().y + screenSizeW){
		onScreen = false;
	}
	return onScreen;
}