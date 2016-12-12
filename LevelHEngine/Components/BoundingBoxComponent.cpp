#include "BoundingBoxComponent.h"

#include "../ResourceManagement/ResourceManager.h"

BoundingBoxComponent::~BoundingBoxComponent()
{
}

void BoundingBoxComponent::onAwake()
{		
	initialBoxDim = Vec3(0.0f, 0.0f, 0.0f);
	nextPos = Vec3(0.0f, 0.0f, 0.0f);
	boxDim = initialBoxDim;
	id = "boundingBox";
}

void BoundingBoxComponent::onDestroy()
{
}

void BoundingBoxComponent::initaliseBoundingBox(std::string meshID)
{
	initialBoxDim = ResourceManager::getMesh(meshID)->getMaxVert() - ResourceManager::getMesh(meshID)->getMinVert();
	boxDim = initialBoxDim;
}