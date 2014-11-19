#ifndef _MANAGER_OBJECT_
#define _MANAGER_OBJECT_

#include "Game.h"

class Game;

/*!
 * \class ManagerObject
 * \brief Not a drawable object. Not a physics object.
 *
 * An object that can not move and does not have an image.
 */
class ManagerObject : public Object{

protected:
	/*!
	 * The game this object will be added to.
	 */
	Game* game;

public:
	/*!
	 * Constructor
	 * \param game The game this object will be added to.
	 */
	ManagerObject(Game* game);
	
	/*!
	 * Constructor
	 * \param game The game this object will be added to.
	 * \param name A string that can be used to identify this object.
	 */
	ManagerObject(Game* game, std::string name);

	/*!
	 * \return False.
	 * \param frameTime The amount of time the last frame took.
	 */
	bool update(sf::Time frameTime);
};

#endif