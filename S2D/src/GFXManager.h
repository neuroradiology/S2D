#ifndef _GFX_MANAGER_
#define _GFX_MANAGER_

#include "ObjectManager.h"
#include "Screen.h"
#include <sstream>

enum GFX_SETTINGS{NO_SETTINGS = 0, VSYNC = 1, FULL_SCREEN = 10};

/*!
 * \class GFXManager
 * \brief Manages the window and all draw/display calls.
 */	
class GFXManager{

private:
	/*!
	 * The initial settings of the window
	 */	
	sf::VideoMode mode;
	
	/*!
	 * Whether or not the window is clear.
	 */
	bool isClear;
	
	/*!
	 * This contains size of the window that will be created and the current view of the game world.
	 */
	Screen* screen;

protected:
	/*!
	 * The main window of the game.
	 */
	sf::RenderWindow window;
	
public:	
	/*!
	 * Constructor
	 *
	 * \param screen The screen that the window will be created from.
	 */
	GFXManager(Screen* screen);
	
	/*!
	 * Destructor
	 *
	 * If the window is still open, this will close it.
	 */
	~GFXManager();

	/*!
	 * Starts a graphics manager. This will open the window with the size found in Screen.
	 * Vertical sync is enabled by default.
	 * \return 0 if the window opens successfully. -1 otherwise.
	 */
	int initGFXManager(int settings);
	
	/*!
	 * Draws all the objects in the current scene that are on the screen to a buffer.
	 * \param objectManager The objects in the current scene.
	 */
	void draw(ObjectManager* objectManager);
	
	/*!
	 * Displays the buffer.
	 * \return 1 if the window displays succesfully, 0 otherwise
	 */
	int display();

	/*!
	 * \return true if the window is open, false otherwise
	 */
	bool isOpen();

	/*!
	 * Closes the window.
	 */
	void close();

	/*!
	 * Returns the window. This is used by Controls to collect and handle the input events.
	 * \return The main window.
	 */
	sf::RenderWindow& getWindow();
};

#endif
