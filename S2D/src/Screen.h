#ifndef _SCREEN_
#define _SCREEN_

#include "SFML/Graphics.hpp"
#include "Object.h"

/*!
 * \class Screen
 * \brief Stores the screen size and the current view of the game world.
 */
class Screen{
private:
	/*!
	 * The width, in pixels, the game window will be when it is created.
	 */
	unsigned int screenSizeW;
	
	/*!
	 * The height, in pixels, the game window will be when it is created.
	 */
	unsigned int screenSizeH;
	
	/*!
	 * The view of the game world that will be drawn and displayed.
	 */
	sf::View camera;
	
	/*!
	 * This is the object that currently has the camera attached to it. If that camera is not attached to any object,
	 * this is NULL.
	 */
	Object* objectWithCamera;

public:
	
	/*!
	 * Constructor
	 * Sets the screen width and height to 800 and 600, sets the camera size to the screen size,
	 * and sets the center of the camera to the center of the screen.
	 */
	Screen();
	
	/*!
	 * Constructor
	 * Sets the width and height of the screen to w and h.
	 * \param w the desired width of the window.
	 * \param h the desired height of the window.
	 */
	Screen(int w, int h);

	/*!
	 * \brief Sets the desired size of the window. This does not change the screen size after the window is created.
	 * \param w the desired width of the window.
	 * \param h the desired height of the window.
	 */
	void setScreenSize(int w, int h);

	/*!
	 * \return The current width of the screen.
	 */
	unsigned int getW();

	/*!
	 * \return The current height of the screen.
	 */
	unsigned int getH();

	/*!
	 * Makes the camera follow a specific object.
	 * \param object The object the camera will follow.
	 */
	void attachCamera(Object* object);

	/*!
	 * Updates the cameras position to match the position of the object it is following.
	 */
	void updateCamera();

	/*!
	 * \return A pointer to the current view.
	 */
	sf::View getCamera();

	/*!
	 * \return The position of the camera (top left coordinate).
	 */
	sf::Vector2f getCameraPosition();
	
	/*!
	 * \return True if the object is within the cameras view.
	 * \param object The object we are checking.
	 *
	 * Warning. Not tested.
	 */
	bool inView(Object* object);

	/*!
	 * \return True if the sprite is within the cameras view. False otherwise.
	 * \param sprite The sprite we are checking.
	 */
	bool inView(sf::Sprite* sprite);

	/*!
	 * \return True if the circle is within the cameras view. False otherwise.
	 * \param circle The circle we are checking.
	 */
	bool inView(sf::CircleShape* circle);

	/*!
	 * \return True if the text is within the cameras view. False otherwise.
	 * \param text The text we are checking.
	 */
	bool inView(sf::Text* text);
};

#endif