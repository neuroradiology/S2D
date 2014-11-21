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