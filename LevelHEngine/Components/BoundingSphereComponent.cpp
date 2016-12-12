#include "BoundingSphereComponent.h"

#include "../ResourceManagement/ResourceManager.h"

BoundingSphereComponent::~BoundingSphereComponent()
{
}

void BoundingSphereComponent::onAwake()
{
	initialSphereRad = 0.0f;
	nextPos = Vec3(0.0f, 0.0f, 0.0f);  
	sphereRad = initialSphereRad;
	id = "boundingSphere";
}

void BoundingSphereComponent::onDestroy()
{
}

void BoundingSphereComponent::initaliseBoundingSphere(std::string meshID)
{
	initialSphereRad = ResourceManager::getMesh(meshID)->getMaxVert().x - ResourceManager::getMesh(meshID)->getMinVert().x;
	initialSphereRad *= 0.5f;
	sphereRad = initialSphereRad;
}