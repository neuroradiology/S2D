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
#ifndef _SCENE_
#define _SCENE_

#include <vector>
#include "Game.h"

//forward declaration to get around circular dependency
class Game;

/*!
 * \class Scene
 * \brief The base class for a scene.
 */
class Scene{
protected:
	/*!
	 * The objects in this scene.
	 */
	std::vector<Object*> objects;

	/*!
	 * The game this scene wil be added to. The Controls, Screen, and ObjectManager can be accessed through this.
	 */
	Game* game;

public:
	/*!
	 * Constructor
	 * \param game The game this scene will be added to.
	 */
	Scene(Game* game);

	/*!
	 * Adds an object to this Scene. This should be avoided unless you really want to define all the objects in main.
	 * \param object The object to be added to the scene.
	 */
	virtual void add(Object* object);

	/*!
	 * Updates this scene. This is for checking handling events in the scene. This should contain a condition that will end the scene.
	 * \return -1 if the scene is over, otherwise return 0.
	 */
	virtual int update() = 0;

	/*!
	 * \return The Object vector of this scene.
	 */
	std::vector<Object*>* getObjects();
};

#endif