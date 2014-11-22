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
#include "DynamicObject.h"

DynamicObject::DynamicObject(Game* game) : game(game){
	//set the type of object
	bodyDef.type = b2_dynamicBody;
	hasPhysics = true;
	objectType = DYNAMIC;
	name = "DYNAMIC";
	size = sf::Vector2f(0.0f, 0.0f);
}

DynamicObject::DynamicObject(Game* game, std::string name) : game(game){
	//set the type of object
	bodyDef.type = b2_dynamicBody;
	hasPhysics = true;
	objectType = DYNAMIC;
	this->name = name;
	size = sf::Vector2f(0.0f, 0.0f);
}

DynamicObject::~DynamicObject(){
	if(mainShape != NULL){
		delete(mainShape);
	}
}

bool DynamicObject::loadFromFile(sf::Sprite* container, std::string filename){
	if(!texture.loadFromFile(filename)){
		return false;
	}
	size = sf::Vector2f((float)texture.getSize().x, (float)texture.getSize().y);
	container->setTexture(texture);
	hasImage = true;
	container->setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
	drawable = container;
	transformable = container;
	shape = SQUARE;
	mainShape = new b2PolygonShape;
	((b2PolygonShape*)mainShape)->SetAsBox((texture.getSize().x / 2.0f) / scale, (texture.getSize().y / 2.0f) / scale);
	mainFixtureDef.shape = mainShape;

	return true;
}

bool DynamicObject::loadFromFile(sf::CircleShape* container, std::string filename){
	if(!texture.loadFromFile(filename)){
		return false;
	}
	size = sf::Vector2f((float)texture.getSize().x, (float)texture.getSize().y);
	container->setTexture(&texture);
	hasImage = true;
	container->setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
	shape = CIRCLE;
	mainShape = new b2CircleShape;
	((b2CircleShape*)mainShape)->m_radius = texture.getSize().x > texture.getSize().y ? (texture.getSize().x / 2.0f) / scale : (texture.getSize().y / 2.0f) / scale;
	mainFixtureDef.shape = mainShape;

	return true;
}

bool DynamicObject::loadFromFile(sf::ConvexShape* container, std::string filename){
	if(!texture.loadFromFile(filename)){
		return false;
	}
	size = sf::Vector2f((float)texture.getSize().x, (float)texture.getSize().y);
	container->setTexture(&texture);
	hasImage = true;
	container->setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
	shape = CONVEX;
	mainShape = new b2PolygonShape;
	int vertexCount = container->getPointCount();
	b2Vec2* vertices = new b2Vec2[vertexCount];
	for(int i = 0; i < vertexCount; i++){
		vertices[i].x = container->getPoint(i).x;
		vertices[i].y = container->getPoint(i).y;
	}
	((b2PolygonShape*)mainShape)->Set(vertices, vertexCount);
	delete vertices;

	return true;
}

void DynamicObject::setPosition(float x, float y, int layer){
	transformable->setPosition(x, y);
	if(b2DEntity != NULL){
		b2DEntity->SetTransform(b2Vec2(x / scale, y / scale), b2DEntity->GetAngle());
	}else{
		bodyDef.position = b2Vec2(x / scale, y / scale);
	}
	this->layer = layer;
}

void DynamicObject::setSize(sf::Vector2f size){
	if(hasImage){
		sf::Vector2u textureSize = texture.getSize();
		sf::Vector2f scaledSize(size.x / textureSize.x, size.y / textureSize.y);
		transformable->setScale(scaledSize);
		this->size = size;

		switch(shape){
		case SQUARE:
			((b2PolygonShape*)mainShape)->SetAsBox((size.x / 2.0f) / scale, (size.y / 2.0f) / scale);
			break;
		case CIRCLE:
			((b2CircleShape*)mainShape)->m_radius = size.x > size.y ? (size.x / 2.0f) / scale : (size.y / 2.0f) / scale;
			break;
		case CONVEX:
			//TODO: fingure out a good way to change the size of a convex object in box2d
			break;
		}
	}
}

void DynamicObject::initializeBody(b2Body* body){
	b2DEntity = body;
	b2DEntity->SetUserData((void*)((Object*)this));
	b2DEntity->CreateFixture(&mainFixtureDef);
	if(!fixtureDefs.empty()){
		for(std::vector<b2FixtureDef>::iterator it; it != fixtureDefs.end(); it++){
			b2DEntity->CreateFixture(&(*it));
		}
	}
}

bool DynamicObject::update(sf::Time frameTime){
	
	return false;
}

sf::Vector2f DynamicObject::getPosition(){
	return transformable->getPosition();
}

sf::Vector2f DynamicObject::getSize(){
	return size;
}