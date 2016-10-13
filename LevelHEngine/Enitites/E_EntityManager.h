#pragma once

#include <vector>
#include <unordered_map>
#include "../Core/C_Audio.h"
#include "../Core/C_Timer.h"
#include "../ParticleSystem/PS_ParticleEffect.h"
#include "Player/EP_Player.h"

/**
@brief A class that manages all of the entities in the game with the exception of the player.
@author Jamie Slowgrove
*/
class E_EntityManager
{
public:
	/**
	@brief Constructs the Entity Manager.
	@param dimensions The screen dimensions.
	@param player A pointer to the player.
	@param renderer A pointer to the renderer.
	@param universalSpeed A pointer for the universal speed of the game.
	*/
	E_EntityManager(C_Vec2 dimensions, EP_Player* player, SDL_Renderer* renderer, float* universalSpeed);

	/**
	@brief Destructs the Entity Manager.
	*/
	~E_EntityManager();

	/**
	@brief A function to update the Entities.
	@param dt The delta time.
	*/
	void update(float dt);

	/**
	@brief A function to draw the Entities to the screen.
	*/
	void draw();

	/**
	@brief Gets the pointer to the wanted texture.
	@param iD The ID of the texture to return.
	@returns The pointer to the wanted texture.
	*/
	C_Texture* getTexture(std::string iD);

	/**
	@brief Gets the dimensions of the wanted entity.
	@param iD The ID of the dimensions to return.
	@returns The dimensions of the wanted entity.
	*/
	C_Vec2 getEntityDimensions(std::string iD);

private:
	///The screen dimensions
	C_Vec2 screenDimensions;
	///A pointer to the renderer.
	SDL_Renderer* renderer;
	///A pointer to the Player.
	EP_Player* player;
	///An unordered map of the sprite textures.
	std::unordered_map<std::string, C_Texture*> textures;
	///An unordered map of the entity dimensions.
	std::unordered_map<std::string, C_Vec2> entityDimensions;
	///A pointer for the universal speed of the game.
	float* universalSpeed;

	///An unordered map of min tint colours for use with the particle effects.
	std::unordered_map<std::string, SDL_Colour> minColourTints;
	///An unordered map of max tint colours for use with the particle effects.
	std::unordered_map<std::string, SDL_Colour> maxColourTints;
	///The vector array of particle effects for use with entity death.
	std::vector<PS_ParticleEffect*> deathEffects;

	/**
	@brief A function that deletes all of the entities flagged as dead.
	*/
	void removeDeadEntites();

	/**
	@brief A function that creates the particle effects for if the entities are killed.
	@param entityPos The position of the entity.
	@param entityVelocity The Velocity of the entity.
	@param deadEntityDimensions The dimensions of the Entity.
	@param entityType The name of the type of entity that is killed.
	*/
	void createDeathEffects(C_Vec2 entityPos, C_Vec2 entityVelocity, C_Vec2 deadEntityDimensions,
		std::string entityType);

	/**
	@brief A function that deletes all of the entities flagged as dead.
	*/
	void removeCompletedEffects();
};