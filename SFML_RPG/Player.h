/**\file Player.h*/
#pragma once
#include "Entity.h"
#include "Items.h"
#include "Inventory.h"

/*!\class Player
\brief the player class which the user controls 
*/
class Player : public Entity
{
private:
	//variables
	Inventory* inventory; //!<player inventory object

	bool initAttack; //!< initialise when the player is attacking
	bool attacking; //!< for when the player is attacking
	Sword* sword; //!< player sword weapon

	sf::Clock damageTimer; //!< how long it takes the player to take damage
	sf::Int32 damageTimerMax; //!< max time for player to take damage
	
	//Initializer functions
	void initVariables(); //!< init private variables
	void initComponents(); //!< init components
	void initAnimations(); //!< init animations
	void initInventory(); //!< init inventory

public:
	Player(float x, float y, sf::Texture& texture_sheet); //!< player constructor
	virtual ~Player(); //!< player destructor

	//Accessors
	AttributeComponent* getAttributeComponent(); //!< get the attribute comp for the player
	Weapon* getWeapon(); //!< get player weapom

	const bool& getInitAttack() const; //!< get initAttack boolean variable
	const bool getDamageTimer(); //!< get elapsed time when taking damage

	//Modifiers
	void setInitAttack(const bool initAttack); //!< set initAttack

	//Functions
	void loseHP(const int hp); //!< player loses hp
	void gainHP(const int hp); //!< player gains hp
	const bool isAlive() const; //!< check if player is alive
	void loseEXP(const int exp); //!< player loses exp
	void gainEXP(const int exp); //!< player gains exp

	void updateAnimations(const float dt); //!<update animations
	virtual void update(const float& dt, sf::Vector2f& mouse_pos_view); //!< update player

	void render(sf::RenderTarget& target, sf::Shader* shader = NULL, const sf::Vector2f light_position = sf::Vector2f(), const bool show_hitbox = false); //!< render player
};

