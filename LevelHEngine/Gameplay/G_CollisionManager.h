#pragma once

#include <vector>
#include "../Enitites/E_EntityManager.h"
#include "../Enitites/Player/EP_Player.h"

/**
@brief Contains the data and functions for the CollisionManager.
@author Jamie Slowgrove
*/
class G_CollisionManager
{
public:
	/**
	@brief Constructs the CollisionManager.
	@param player A pointer to the Player.
	@param entityManager A pointer to the EntityManager.
	@param universalSpeed A pointer for the universal speed of the game.
	*/
	G_CollisionManager(EP_Player* player, E_EntityManager* entityManager, float* universalSpeed);

	/**
	@brief Destructs the G_CollisionManager.
	*/
	~G_CollisionManager();

	/**
	@brief A function that handles all of the collision detection between the player and the entities.
	*/
	void entityCollisionDetection();

private:
	///A pointer to the Player.
	EP_Player* player;
	///A pointer to the EntityManager.
	E_EntityManager* entityManager;
	///A pointer for the universal speed of the game.
	float* universalSpeed;
};