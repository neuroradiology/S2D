#ifndef _GAME_
#define _GAME_

#include <sstream>

#include "Controls.h"
#include "Screen.h"
#include "GFXManager.h"
#include "CollisionListener.h"
#include "Scene.h"

class Scene;
class Object;

/*!
* \class Game
* \brief The main class of the engine. Contains the main loop.
*
* This is the main class of the engine where objects are added to the ObjectManager and the
* current Scene is updated each frame. The main loop updates the Control class,
* each Object in the Scene, and draws/displays everything that is on the Screen.
*/
class Game : public Screen, private GFXManager, public Controls, public ObjectManager, private CollisionListener{
private:

	/*!
	 * The clock used for updating certain objects. It is restarted each frame.
	 */
	sf::Clock frameClock;

	/*!
	 * If the game is currently running.
	 */
	bool playing;

	/*!
	 * The current scene of the game.
	 */
	Scene* currentScene;

public:

	/*!
	 * Contstructor
	 * 
	 * Creates the Screen, GFXManager, Controls, and ObjectManager.
	 */
	Game();

	/*!
	 * Destructor
	 */
	~Game();
	
	/*!
	 * DOXYGEN_SHOULD_SKIP_THIS
	 */
	Controls* controls;

	/*!
	 * DOXYGEN_SHOULD_SKIP_THIS
	 */
	Screen* screen;

	/*!
	 * DOXYGEN_SHOULD_SKIP_THIS
	 */
	ObjectManager* objectManager;

	/*!
	 * Changes the size of the screen. This can be called at any time. If the window is full screen, this will effectively change the resolution.
	 */
	void changeScreenSize(int x, int y);

	/*!
	 * Sets the current scene. Removes all Objects from ObjectManager and adds the new objects to Objectmanager
	 * \param scene The scene we are going to switch to.
	 * \param force Removes persistent objects.
	 */
	void loadScene(Scene* scene, bool force = false);
	
	/*!
	 * Initializes a game. Creates the window and starts the collision listener.
	 * \return 0 if the window opens successfully. -1 otherwise.
	 */
	int init(int settings = NO_SETTINGS);
	
	/*!
	 * Runs the game using the current scene. This is where the main loop of the game is.
	 * \return An enumerated value. Either CLOSE or CONTINUE.
	 */
	int play();
};
#endif