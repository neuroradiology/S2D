#include "BackgroundObject.h"

BackgroundObject::BackgroundObject(Game* game) : game(game){
	objectType = BACKGROUND;
	name = "BACKGROUND";
	size = sf::Vector2f(0.0f, 0.0f);
}

BackgroundObject::BackgroundObject(Game* game, std::string name) : game(game){
	objectType = BACKGROUND;
	name = name;
	size = sf::Vector2f(0.0f, 0.0f);
}

bool BackgroundObject::loadFromFile(sf::Sprite* container, std::string filename){
	if(!texture.loadFromFile(filename)){
		return false;
	}
	size = sf::Vector2f((float)texture.getSize().x, (float)texture.getSize().y);
	container->setTexture(texture);
	hasImage = true;
	container->setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
	drawable = container;
	transformable = container;
	return true;
}

bool BackgroundObject::loadFromFile(sf::CircleShape* container, std::string filename){
	if(!texture.loadFromFile(filename)){
		return false;
	}
	size = sf::Vector2f((float)texture.getSize().x, (float)texture.getSize().y);
	container->setTexture(&texture);
	hasImage = true;
	container->setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
	return true;
}

bool BackgroundObject::loadFromFile(sf::ConvexShape* container, std::string filename){
	if(!texture.loadFromFile(filename)){
		return false;
	}
	size = sf::Vector2f((float)texture.getSize().x, (float)texture.getSize().y);
	container->setTexture(&texture);
	hasImage = true;
	container->setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
	return true;
}

void BackgroundObject::setPosition(float x, float y, int layer){
	transformable->setPosition(x, y);
	this->layer = layer;
}

void BackgroundObject::setSize(sf::Vector2f size){
	if(hasImage){
		sf::Vector2u textureSize = texture.getSize();
		sf::Vector2f scaledSize(size.x / textureSize.x, size.y / textureSize.y);
		transformable->setScale(scaledSize);
		this->size = size;
	}
}

bool BackgroundObject::update(sf::Time frameTime){
	
	return false;
}

sf::Vector2f BackgroundObject::getPosition(){
	return transformable->getPosition();
}

sf::Vector2f BackgroundObject::getSize(){
	return size;
}