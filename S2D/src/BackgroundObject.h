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
#ifndef _BACKGROUND_OBJECT_
#define _BACKGROUND_OBJECT_

#include "Game.h"

class Game;

/*!
 * \class BackgroundObject
 * \brief A drawable object. Not a physics object.
 *
 * This can be used to create images in the background such as a landscape or buildings behind the foreground that are not collidable.
 */
class BackgroundObject : public Object{

private:
	/*!
	 * Stores the texture of this object.
	 */
	sf::Texture texture;

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
	BackgroundObject(Game* game);

	/*!
	* Constructor
	* \param game The game this object will be added to.
	* \param name A string that can be used to identify this object.
	*/
	BackgroundObject(Game* game, std::string name);

	/*!
	 * Loads the texture of the object.
	 * \return True if the image is found and loaded.
	 * \param container The sf::Drawable that will contain this objects texture.
	 * \param filename The file to be loaded.
	 */
	bool loadFromFile(sf::Sprite* container, std::string filename);

	/*!
	 * Loads the texture of the object.
	 * \return True if the image is found and loaded.
	 * \param container The sf::Drawable that will contain this objects texture.
	 * \param filename The file to be loaded.
	 */
	bool loadFromFile(sf::CircleShape* container, std::string filename);

	/*!
	 * Loads the texture of the object.
	 * \return True if the image is found and loaded.
	 * \param container The sf::Drawable that will contain this objects texture.
	 * \param filename The file to be loaded.
	 */
	bool loadFromFile(sf::ConvexShape* container, std::string filename);

	/*!
	 * Sets the position of the object in the game world.
	 * \param x The desired x position
	 * \param y The desired y position
	 * \param layer The layer the object should be drawn on
	 */
	void setPosition(float x, float y, int layer = 0);

	/*!
	* Sets the size of the object. Only works after an image has been loaded. This will stretch or shrink the image to fit the object.
	* \param size The desired size.
	*/
	void setSize(sf::Vector2f size);

	/*!
	 * \return True if this object moved or rotated in the current frame.
	 * \param frameTime The amount of time the last frame took.
	 */
	bool update(sf::Time frameTime);

	/*!
	 * \return The center of the drawable.
	 */
	sf::Vector2f getPosition();

	/*!
	 * \return The size of the objects minimum bounding box.
	 */
	sf::Vector2f getSize();
};

#endif