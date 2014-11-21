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
#include "Object.h"

Object::Object(){
	currentId++;
	id = currentId;
	onScreen	= false;
	hasImage	= false;
	hasPhysics	= false;
	hasSound	= false;
	hasEffect	= false;
	hasCamera	= false;
	hasShader	= false;
	persistent	= false;
	drawable	= NULL;
	b2DEntity	= NULL;
	objectType	= NONE;
}

int Object::getId(){
	return id;
}

std::string Object::getName(){
	return name;
}

bool Object::isDrawable(){
	return hasImage;
}

bool Object::isOnScreen(){
	return onScreen;
}

bool Object::hasCameraAttached(){
	return hasCamera;
}

bool Object::hasGLSLShader(){
	return hasShader;
}

bool Object::isPersistent(){
	return persistent;
}

void Object::attachCamera(){
	hasCamera = true;
}

ObjectType Object::getType(){
	return objectType;
}

int Object::getLayer(){
	return layer;
}

b2Body* Object::getBody(){
	return b2DEntity;
}

sf::Vector2f Object::getPosition(){
	return sf::Vector2f(0.0f, 0.0f);
}

sf::Vector2f Object::getSize(){
	return sf::Vector2f(0.0f, 0.0f);
}

void Object::initializeBody(b2Body* body){
	b2DEntity = body;
}

sf::Drawable* Object::getDrawable(){
	return drawable;
}

b2BodyDef* Object::getBodyDef(){
	if(hasPhysics){
		return &bodyDef;
	}
	return NULL;
}

void Object::beginCollision(Object* object, b2Contact* contact){

}

void Object::endCollision(Object* object, b2Contact* contact){

}

sf::Shader* Object::getShader(){
	return NULL;
}