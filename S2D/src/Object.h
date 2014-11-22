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
#ifndef _OBJECT_
#define _OBJECT_

#define _USE_MATH_DEFINES
#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

#include "Controls.h"
#include "Box2D/Box2D.h"
#include "SFML/System.hpp"
#include <math.h>
#include <algorithm>

/*!
 * To convert from box2d position and size values to game world values you must multiply by this scale
 * To convert from game world values to box2d values you must divide by this scale
 */
const unsigned int scale = 100;

/*!
 * These are the possible types of an object. If you create your own object, you should add a unique name to this enum.
 */
enum ObjectType{NONE, STATIC, CONTROLLABLE, DYNAMIC, BACKGROUND, MANAGER};

enum Shape{SQUARE, CIRCLE, CONVEX};

/*!
 * Used to assign a unique id to new objects created
 */
static int currentId = 0;

/*!
 * \class Object
 * \brief The base class for all objects.
 */
class Object{

private:
	/*!
	 * Unique id for this object.
	 */
	int id;

protected:
	/*!
	 * User defined name.
	 */
	std::string name;

	/*!
	 * This determines whether the object will be drawn (if it is drawable). It should be updated
	 * every frame in the update function of the object.
	 */
	bool onScreen;

	/*!
	 * If an object is drawable, this must be set to true. This is used by GFXManager to determine if the object can be drawn.
	 */
	bool hasImage;

	/*!
	 * If an object is simulated in the physics world, this should be true.
	 */
	bool hasPhysics;

	/*!
	 * TODO: NOT IMPLEMENTED YET
	 * If an object has a sound, this must be set to true. This will be used by a sound manager to determine if an object has
	 * sound. From this sound manager, you will be able to to set the volume of all sounds or stop all sounds from playing.
	 */
	bool hasSound;

	/*!
	 * TODO: NOT IMPLEMENTED YET
	 * not sure if i even need this to be honest. could be used for interaction with other objects maybe?
	 * Like any object that collides with this object takes that effect.
	 */
	bool hasEffect;

	/*!
	 * If an object is being followed by the camera, this value will be set to true.
	 * if it is not, the camera will not be updated to the correct position when this object
	 * moves.
	 */
	bool hasCamera;

	/*!
	 * If a drawable object has a shader, this value must be set to true. Used by GFXManager to determine if the object should be drawn with
	 * a shader. The shader is a member of the object. I don't think I need this because drawing an object with a null shader has no effect on the object being draw.
	 */
	bool hasShader;

	/*!
	 * TODO: NOT IMPLEMENTED YET
	 * If this is set to true, it will not be removed from ObjectManager if removeAllObjects is called.
	 * This allows the object to persist across scenes without having to add it every time the scene changes.
	 */
	bool persistent;

	/*!
	 * Stores an enumerated value of the object type. Each game object should have a specific type.
	 * This is mainly for easier debugging but can also be used for determining what to do after collisions occur.
	 */
	ObjectType objectType;
	
	/*!
	 * The layer this object will be drawn on.
	 * The object with the largest positive layer will be drawn last so it appears on top of the screen.
	 * The object with the largest negative layer will be drawn first.
	 */
	int layer;

	/*!
	 * TODO: NOT IMPLEMENTED YET
	 * The priority for when this object is updated.
	 * The object with the largest positive priority will update first each frame.
	 * The object with the largest negative priority will update last.
	 */
	int priority;

	/*!
	 * The transformable of this object.
	 */
	sf::Transformable* transformable;

	/*!
	 * The image of this object. Can be any sf::Drawable. If this object is not a physics object, it will be set to NULL.
	 */
	sf::Drawable* drawable;

	/*!
	 * The shape of this object.
	 */
	Shape shape;

	/*!
	 * The size of this object in game world coordinates.
	 */
	sf::Vector2f size;
	
	/*!
	 * Contains the position, type, and a few other details about this objects physics body.
	 */
	b2BodyDef bodyDef;

	/*!
	 * This is the box2D body used for physics simulation. If this object is not a physics object, it will be set to NULL.
	 */
	b2Body* b2DEntity;
	
public:
	/*!
	 * Constructor
	 * Sets all of the bool variables above to false, b2DEntity to NULL and objectType to NONE.
	 * Updates currentId and sets id of this object.
	 */
	Object();

	/*!
	 * \return The id of this object.
	 */
	int getId();

	/*!
	 * \return The name of this object.
	 */
	std::string getName();

	/*!
	 * \return True if this object is drawable.
	 */
	bool isDrawable();

	/*!
	 * \return True if this object thinks it is on screen.
	 * (onScreen must be updated every frame for this to return the correct value)
	 */
	bool isOnScreen();

	/*!
	 * \return True if this object is being followed by the camera.
	 */
	bool hasCameraAttached();

	/*!
	 * \return True if this object has a shader.
	 */
	bool hasGLSLShader();

	/*!
	 * \return True if this object is persistent.
	 */
	bool isPersistent();

	/*!
	 * This is called by Screen when the camera is attached to this object.
	 * Sets hasCamera to true.
	 */
	void attachCamera();

	/*!
	 * \return The ObjectType of this object.
	 */
	ObjectType getType();

	/*!
	 * \return The layer this object is on.
	 */
	int getLayer();

	/*!
	 * \return The drawable of this object.
	 */
	sf::Drawable* getDrawable(); 

	/*!
	 * \return The box2D body of this object. If this object is not a physics object, it will return NULL.
	 */
	b2Body* getBody();

	/*!
	 * \return True if this object moved or changed in a way that requires it to be drawn again.
	 */
	virtual bool update(sf::Time frameTime) = 0;

	/*!
	 * \return The position of this object. If this object is drawable, it will return the center point
	 * of the sprite/sfml drawable. If it is not drawable, it will return the center point of the box2D body.
	 */
	virtual sf::Vector2f getPosition();
	
	/*!
	 * \return The size of the box2d object scaled up to the game world size
	 */
	virtual sf::Vector2f getSize();
	
	/*!
	 * Initializes the box2D body of this object.
	 */
	virtual void initializeBody(b2Body* body);

	/*!
	 * \return The body definition of this objects body.
	 */
	virtual b2BodyDef* getBodyDef();
	
	/*!
	 * If this object is a physics object, this function is called whenever a collision occurs with this object.
	 * \param object The object that collided with this.
	 * \param contact The box2D b2Contact that holds information about the collision.
	 */
	virtual void beginCollision(Object* object, b2Contact* contact);
	
	/*!
	 * If this object has a physics object, this function is called whenever this object stops colliding with another object.
	 * \param object The object that stopped colliding with this.
	 * \param contact The box2D b2Contact that holds information about the end of the collision.
	 */
	virtual void endCollision(Object* object, b2Contact* contact);
	
	/*!
	 * \return If this object is drawable and has a shader, it will return a pointer to the shader. Otherwise it returns NULL.
	 */
	virtual sf::Shader* getShader();

};

#endif
