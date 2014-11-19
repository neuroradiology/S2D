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