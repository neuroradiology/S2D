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