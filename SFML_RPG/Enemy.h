/**\file Enemy.h*/
#pragma once
#include "Entity.h"
#include "EnemySpawner.h"

/*!\class Enemy
\brief an abstract class for enemies
*/
class Enemy : public Entity
{
private:

protected:
	//Variables
	EnemySpawner& enemySpawner; //!< position or tile where enemy spawns from
	unsigned gainExp; //!< amount of exp gained
	sf::Clock damageTimer; //!< how long enemy takes damage
	sf::Int32 damageTimerMax; //!< max time enemy takes damage

	//Initializer Functions
	virtual void initVariables() = 0; //!< init private variables
	virtual void initAnimations() = 0; //!< init animations
public:
	Enemy(EnemySpawner& enemy_spawner); //!< Enemy class Constructor 
	virtual ~Enemy(); //!< Enemy class Destrutor

	//Accessors
	const unsigned& getGainExp() const; //!< return exp gained
	EnemySpawner& getEnemySpawner(); //!< return enemySpawner
	const bool getDamageTimerDone() const; //!< return when the damage timer is done

	//Modifiers
	void resetDamageTimer(); //!< restart damage timer

	//Functions
	virtual void generateAttributes(const unsigned level); //!< generate attributes for the enemy
	virtual void loseHP(const int hp); //!< enemy loses hp when attacked
	virtual const bool isDead() const; //!< check if enemy hp is less than 0

	virtual const AttributeComponent* getAttributeComponent() const; //!< return attribut comp

	virtual void updateAnimation(const float& dt) = 0; //!< update animation for enemy

	virtual void update(const float & dt, sf::Vector2f& mouse_pos_view) = 0; //!< update enemy
	virtual void render(sf::RenderTarget & target, sf::Shader* shader = NULL, const sf::Vector2f light_position = sf::Vector2f(), const bool show_hitbox = false) = 0; //!< render enemy
};

