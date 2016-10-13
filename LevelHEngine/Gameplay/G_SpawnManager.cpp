#include "G_SpawnManager.h"

G_SpawnManager::G_SpawnManager(C_Vec2 screenDimensions, EP_Player* player, E_EntityManager* entityManager, float* universalSpeed)
	: screenDimensions(screenDimensions), player(player), entityManager(entityManager), spawnTimer(1.0f), waveTimer(5.0f), 
	universalSpeed(universalSpeed), waveTime(1.0f)
{
}

G_SpawnManager::~G_SpawnManager()
{
}

void G_SpawnManager::update(float dt)
{
	//update the wave timer
	waveTimer.upadateTimer(dt);
	//check if the wave timer has ended
	if (waveTimer.checkTimer())
	{
		//decrease the time by 5 unless at min time
		if (waveTime > 0.5f)
		{
			waveTime -= 0.05f;
		}
		waveTimer.resetTimer();
	}
	
	//set the length of the timer length depending on the universal speed and wave time
	spawnTimer.setTimerLength(waveTime / *universalSpeed);
	//Update the spawn timer
	spawnTimer.upadateTimer(dt);
	//check if a new wave of entities should be spawned
	if (spawnTimer.checkTimer())
	{
		spawnEntityWave();
		spawnTimer.resetTimer();
	}
}

void G_SpawnManager::spawnEntityWave()
{
	//Get a number between 0 and 3 for max 4 number of things to spawn
	int numberToSpawn = (rand() % 4);

	//Divide the screen height into the number of things to spawn
	float zoneHeight = screenDimensions.y / numberToSpawn;

	for (int i = 0; i <= numberToSpawn; i++)
	{
		//Get the number for the entity to spawn
		int entityToSpawn = pickEntity();

		//initialise the new spawn position
		float spawnY = 0.0f;

		//work out the minimum spawn y position within its heights zone
		float minimumY = i * zoneHeight;

		//work out the maximum spawn y position within its heights zone
		float maximumY = ((i + 1) * zoneHeight) - 1;
		maximumY -= entityManager->getEntityDimensions(getEntityID(entityToSpawn)).y;

		//make a random y spawn within the min and max height
		spawnY = (float)(rand() % (int)(maximumY - minimumY)) + minimumY;

		//spawn the entity
		spawnEntity(spawnY, entityToSpawn);
	}

}

int G_SpawnManager::pickEntity()
{
	//generate a new number between 1 and 200
	int spawnNumber = (rand() % 200) + 1;

	if (spawnNumber <= 60) //30% chance
	{
		//entity is a type 0
		return 0;
	}
	else if (spawnNumber >= 61 && spawnNumber <= 100) //20% chance
	{
		//entity is a type 1
		return 1;
	}
	else if (spawnNumber >= 101 && spawnNumber <= 140) // 20% chance
	{
		//entity is a type 2
		return 2;
	}
	else if (spawnNumber >= 141 && spawnNumber <= 170) // 15% chance
	{
		//entity is a type 3
		return 3;
	}
	else if (spawnNumber >= 171 && spawnNumber <= 186) // 17% chance
	{
		//entity is a type 4
		return 4;
	}
	else if (spawnNumber >= 187 && spawnNumber <= 190) // 2% chance
	{
		//entity is a type 5
		return 5;
	}
	else if (spawnNumber >= 191 && spawnNumber <= 194) // 2% chance
	{
		//entity is a type 6
		return 6;
	}
	else if (spawnNumber >= 195 && spawnNumber <= 197) // 1.5% chance
	{
		//entity is a type 7
		return 7;
	}
	else if (spawnNumber >= 198 && spawnNumber <= 199) // 1% chance
	{
		//entity is a type 8
		return 8;
	}
	else if (spawnNumber == 200) // 0.5% chance
	{
		//entity is a type 9
		return 9;
	}

	//something has gone wrong
	return -1;
}

std::string G_SpawnManager::getEntityID(int entityType)
{
	//Get the entity ID
	switch (entityType)
	{
	case 0: //Type 0
		return "EE_TYPE0";
		break;
	case 1: //Type 1
		return "EE_TYPE1";
		break;
	case 2: //Type 2
		return "EE_TYPE2";
		break;
	case 3: //Type 3
		return "EE_TYPE3";
		break;
	case 4: //Type 4
		return "EE_TYPE4";
		break;
	case 5: //Type 5
		return "EE_TYPE5";
		break;
	case 6: //Type 6
		return "EE_TYPE6";
		break;
	case 7: //Type 7
		return "EE_TYPE7";
		break;
	case 8: //Type 8
		return "EE_TYPE8";
		break;
	case 9: //Type 9
		return "EE_TYPE9";
		break;
	}
	return "ERROR - Wrong EntityType";
}

void G_SpawnManager::spawnEntity(float spawnY, int entityToSpawn)
{
	//Spawn the new entity
	switch (entityToSpawn)
	{
	case 0: //type 0
		//Spawn a type 0
		break;
	case 1: //type 0
		//Spawn a type 1
		break;
	case 2: //type 2
		//Spawn a type 2
		break;
	case 3: //type 3
		//Spawn a type 3
		break;
	case 4: //type 4
		//Spawn a type 4
		break;
	case 5: //type 5
		//Spawn a type 5
		break;
	case 6: //type 6
		//Spawn a type 6
		break;
	case 7: //type 7
		//Spawn a type 7
		break;
	case 8: //type 8
		//Spawn a type 8
		break;
	case 9: //type 9
		//Spawn a type 9
		break;
	}
}