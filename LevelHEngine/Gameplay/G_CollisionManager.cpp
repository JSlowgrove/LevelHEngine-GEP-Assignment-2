#include "G_CollisionManager.h"

G_CollisionManager::G_CollisionManager(EP_Player* player, E_EntityManager* entityManager, float* universalSpeed) 
	: player(player), entityManager(entityManager), universalSpeed(universalSpeed)
{
}

G_CollisionManager::~G_CollisionManager()
{
}

void G_CollisionManager::entityCollisionDetection()
{
}