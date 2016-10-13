#include "E_EntityManager.h"

E_EntityManager::E_EntityManager(C_Vec2 dimensions, EP_Player* player, SDL_Renderer* renderer, float* universalSpeed) 
	: screenDimensions(dimensions), player(player), renderer(renderer),	universalSpeed(universalSpeed)
{	
	//Initialise the textures
	//textures["EE_EXAMPLE"] = new C_Texture("Assets/Images/EXAMPLE.png", renderer);

	//Initialise the min and max tint colours for the particle effects
	//minColourTints["EE_EXAMPLE"] = { (Uint8)155, (Uint8)100, (Uint8)0 };
	//maxColourTints["EE_EXAMPLE"] = { (Uint8)255, (Uint8)200, (Uint8)20 };

	//Initialise dimensions
	//entityDimensions["EE_EXAMPLE"] = C_Vec2(dimensions * 0.06f);	
}

E_EntityManager::~E_EntityManager()
{
	//Delete particle effects
	for (auto deathEffect : deathEffects)
	{
		delete deathEffect;
	}
	
	//Delete textures
	for (auto i = textures.begin(); i != textures.end(); ++i)
	{
		delete i->second;
	}
}

void E_EntityManager::update(float dt)
{
	//remove entities flagged as dead.
	removeDeadEntites();

	//remove completed particle effects
	removeCompletedEffects();
	
	//Update particle effects
	for (auto deathEffect : deathEffects)
	{
		deathEffect->update(dt);
	}
}

void E_EntityManager::draw()
{
	//Draw the particle effects
	for (auto deathEffect : deathEffects)
	{
		deathEffect->draw(renderer);
	}
}

void E_EntityManager::removeDeadEntites()
{
}

void E_EntityManager::createDeathEffects(C_Vec2 entityPos, C_Vec2 entityVelocity, C_Vec2 deadEntityDimensions,
	std::string entityType)
{
	//push back a death effect for the entity.
	deathEffects.push_back(new PS_ParticleEffect(textures["PS_DeathParticle"],
		entityPos + (deadEntityDimensions * 0.5f), true, 50.0f, 25.0f, 0.1f, minColourTints[entityType], 
		maxColourTints[entityType]));
}

void E_EntityManager::removeCompletedEffects()
{
	for (unsigned int i = 0; i < deathEffects.size(); i++)
	{
		if (deathEffects[i]->getLifeSpan()->checkTimer())
		{
			if (deathEffects[i]->getDead())
			{
				//delete pointer
				delete deathEffects[i];
				//erase from array
				deathEffects.erase(deathEffects.begin() + i);
			}
			else
			{
				//deactivate death effect
				deathEffects[i]->setEmitting(false);
				//reset the lifespan of the effect
				deathEffects[i]->getLifeSpan()->setTimerLength(2.0f);
				//set the effect to dead.
				deathEffects[i]->setDead(true);
			}
			
		}
	}
}

C_Texture* E_EntityManager::getTexture(std::string iD)
{
	return textures[iD];
}

C_Vec2 E_EntityManager::getEntityDimensions(std::string iD)
{
	return entityDimensions[iD];
}