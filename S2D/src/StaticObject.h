#ifndef _STATIC_OBJECT_
#define _STATIC_OBJECT_

#include "Game.h"

class Game;

/*!
 * \class StaticObject
 * \brief A drawable object. An unmovable physics object.
 *
 * An object that does not move when a force is applied to it or if something collides with it. The position can be set directly though.
 */
class StaticObject : public Object{

private:
	/*!
	 * Stores the texture of this object.
	 */
	sf::Texture texture;

	/*!
	 * The main shape of this object.
	 */
	b2Shape* mainShape;
	
	/*!
	 * The main fixture of this object.
	 */
	b2FixtureDef mainFixtureDef;
	
	/*!
	 * Extra fixtures of this object. If you would like a more complex physics object, you can add extra fixtures to this vector.
	 */
	std::vector<b2FixtureDef> fixtureDefs;

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
	StaticObject(Game* game);

	/*!
	* Constructor
	* \param game The game this object will be added to.
	* \param name A string that can be used to identify this object.
	*/
	StaticObject(Game* game, std::string name);

	/*!
	 * Destructor
	 */
	~StaticObject();

	/*!
	 * This is for loading the texture of the object.
	 * \return True if the image is found and loaded.
	 * \param container The sf::Drawable that will contain this objects texture.
	 * \param filename the file to be loaded.
	 */
	bool loadFromFile(sf::Sprite* container, std::string filename);

	/*!
	 * This is for loading the texture of the object.
	 * \return True if the image is found and loaded.
	 * \param container The sf::Drawable that will contain this objects texture.
	 * \param filename the file to be loaded.
	 */
	bool loadFromFile(sf::CircleShape* container, std::string filename);

	/*!
	 * This is for loading the texture of the object.
	 * \return True if the image is found and loaded.
	 * \param container The sf::Drawable that will contain this objects texture.
	 * \param filename the file to be loaded.
	 */
	bool loadFromFile(sf::ConvexShape* container, std::string filename);

	/*!
	 * NOT IMPLEMENTED YET
	 * Add a fixture to this object. This should only be used before the physics object is initialized.
	 * After the physics object is initialized, you can use 'b2DEntity->CreateFixture(myFixtureDefPtr);'
	 * to add fixtures to the object.
	 * \param fixtureDef The fixture that will be added to the physics body.
	 */
	void addFixture(b2FixtureDef fixtureDef);

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
	 * Attaches the fixtures (the shape of the physics object) to the body.
	 * This is called from ObjectManager when the Object is added.
	 * \param body The body created by ObjectManager
	 */
	void initializeBody(b2Body* body);
	
	/*!
	 * \return True if something moved or rotated on the screen. Since this objet doesn't move, this should always return false.
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