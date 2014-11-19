#ifndef _OBJECT_MANAGER_
#define _OBJECT_MANAGER_

#include "Screen.h"
#include <map>

/*!
 * \struct Node_
 * \brief A single element in a queue.
 * This list is used by the map for cases where there are multiple objects within the same layer.
 * Each node only inView a single Object and a pointer to the next node.
 */
struct Node_{
	/*!
	 * data
	 */
	Object* object;
	
	/*!
	 * pointer to next node
	 */
	struct Node_* next;
};

/*!
 * This is just used make it easier to create a list. It isn't really a queue because you never remove
 * anything from the back of the list but you do add to the front of the list.
 */
typedef struct Node_* QueuePtr;

/*!
 * DOXYGEN_SHOULD_IGNORE_THIS
 */
enum MapType{TOP, BOTTOM, TEMP};

/*!
 * \class ObjectManager
 * \brief Manages all objects in the current scene.
 *
 * This class has pointers to all objects in the current scene and orders them by their
 * layer into a std::map. This map is iterated through each frame to update all objects
 * in the scene.
 */
class ObjectManager{

private:
	/*!
	 * Contains pointers to all normal objects in the scene.
	 */
	std::map<int, QueuePtr> objects;
	
	/*!
	 * Contains pointers to all special objects in the scene.
	 * This should be used for UI and other elements that should always appear on top.
	 * This does not need to be used. You can just set the priority of the UI Objects to a
	 * very large number. It is merely here for convenience so you don't have to.
	 */
	std::map<int, QueuePtr> topObjects;

	/*!
	 * The current number of objects in the scene.
	 */
	int objectCount;
	
	/*!
	 * This is used by GFXManager to determine if it should re draw the scene. If no other objects update
	 * but a new object is added into the game, it will draw the whole scene again.
	 */
	bool newObjectAdded;

	/*!
	 * The amount of time between each step in the box2D world.
	 */
	float32 timeStep;
	
	/*!
	 * The number of frames that box2D will process small  changes in velocity.
	 */
	int32 velocityIterations;
	
	/*!
	 * The number of frames that box2D will process small changes in position.
	 */
	int32 positionIterations;

	/*!
	 * DOXYGEN_SHOULD_IGNORE_THIS
	 */
	void add(Object* object, MapType type, std::map<int, QueuePtr>* tempMap = NULL);

public:
	/*!
	 * The world were all physics simulation occurs.
	 */
	b2World world;
	
	/*!
	 * Constructor
	 * 
	 * Sets the object count to 0 and newObjectAdded to false.
	 * Initializes the physics world with 0 gravity.
	 */
	ObjectManager();
	
	/*!
	 * Destructor
	 *
	 * Deletes all alocated Nodes.
	 */
	~ObjectManager();
	
	/*!
	 * Sets the gravity of the physics world.
	 * \param newGravity The desired gravity.
	 */
	void setGravity(b2Vec2 newGravity);

	/*!
	 * Adds an object to the game.
	 * \param object The object to be added.
	 * \param top This defaults to false. If true, the object will be added to a seperate std::map.
	 */
	void addObject(Object* object, bool top = false);

	/*!
	 * Removes an object from the game.
	 * \return True if the object was removed, otherwise false.
	 * \param object The object to be removed. 
	 */
	bool removeObject(Object* object);

	/*!
	 * NOT IMPLEMENTED YET
	 * Removes all objects from the game except for persistent objects, unless force is true.
	 * \param force Determines if persistent objects are removed from the game.
	 */
	void removeObjects(bool force = false);

	/*!
	 * Updates the objects currently in the game. This iterates each Object in each queue of the map.
	 * \return True if there was at least one drawable Object whose position/rotation changed, otherwise false.
	 * \param frameTime The amount of time it took to update, draw, and display the previous frame.
	 */
	bool updateObjects(sf::Time frameTime);

	/*!
	 * \return The object queue map.
	 */
	std::map<int, QueuePtr>* getObjects();
	
	/*!
	 * \return The topObject queue map.
	 */
	std::map<int, QueuePtr>* getTopObjects();
};

#endif
