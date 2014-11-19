#ifndef _COLLISION_LISTENER_
#define _COLLISION_LISTENER_

#include "Object.h"

/*!
 * \class CollisionListener
 * \brief Monitors collisions and calls the objects that collide
 */
class CollisionListener : public b2ContactListener{

	/*!
	 * Called when this object collides with something or something collides with it.
	 * \param contact The contact created by Box2D that stores information about the collision between two fixtures.
	 */
	void BeginContact(b2Contact* contact);

	/*!
	 * Called when this object stops colliding with something.
	 * \param contact The contact created by Box2D that stores information about the collision between two fixtures.
	 */
	void EndContact(b2Contact* contact);

};

#endif