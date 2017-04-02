#include "Flocking.h"

#include <cmath>
#include <time.h>
#include "../ResourceManagement/ResourceManager.h"
#include "../Core/Application.h"
#include "../Components/TransformComponent.h"
#include "../Maths/Convert.h"

Flocking::Flocking(int inNumberOfBoids, std::string inSpriteID, int inXBoundary, int inYBoundary, float inMaxVel)
{
	//initialize random seed
	srand((unsigned int)time(NULL));

	//initialise a the number of Boid objects
	for (int i = 0; i < inNumberOfBoids; i++)
	{
		//creates a Boid at a random position on the screen
		boids.push_back(new Boid(inSpriteID, Vec2(0.0f, 0.0f), inMaxVel,
			Vec2((float)(rand() % inXBoundary), (float)(rand() % inYBoundary))));
	}

	//initialise the boundaries
	xBoundary = inXBoundary;
	yBoundary = inYBoundary;

	//initialise all of the rules to be on
	applyRule1 = applyRule2 = applyRule3 = 1;

	//initialise the max velocity
	maxVel = inMaxVel;
}

Flocking::Flocking(int inNumberOfBoids, std::string inMesh, std::string inBoidTexture, 
	std::string inBoidVertexShader, std::string inBoidFragmentShader, int inXBoundary, 
	int inYBoundary, int inZBoundary, float inMaxVel)
{
	//initialize random seed
	srand((unsigned int)time(NULL));

	//initialise a the number of Boid objects
	for (int i = 0; i < inNumberOfBoids; i++)
	{
		//creates a Boid at a random position on the screen
 		boids.push_back(new Boid(i, inMesh, inBoidTexture, inBoidVertexShader, inBoidFragmentShader, 
			Vec3(0.0f, 0.0f, 0.0f), inMaxVel, 
			Vec3((float)(rand() % inXBoundary), (float)(rand() % inYBoundary), (float)(rand() % inZBoundary))));
	}

	//initialise the boundaries
	xBoundary = inXBoundary;
	yBoundary = inYBoundary;
	zBoundary = inZBoundary;

	//initialise all of the rules to be on
	applyRule1 = applyRule2 = applyRule3 = 1;

	//initialise the max velocity
	maxVel = inMaxVel;
}

Flocking::Flocking(int inNumberOfBoids, std::string inMesh, std::string inBoidVertexShader, 
	std::string inBoidFragmentShader, int inXBoundary, int inYBoundary, int inZBoundary, float inMaxVel)
{
	//initialize random seed
	srand((unsigned int)time(NULL));

	//initialise a the number of Boid objects
	for (int i = 0; i < inNumberOfBoids; i++)
	{
		//generate a random position
		Vec3 rndPos = Vec3(
			((float)(rand() % 200) - 100.0f) * 0.01f,
			((float)(rand() % 200) - 100.0f) * 0.01f,
			((float)(rand() % 200) - 100.0f) * 0.01f);

		//creates a Boid at a random position on the screen
		boids.push_back(new Boid(i, inMesh, inBoidVertexShader, inBoidFragmentShader, Vec3(0.0f, 0.0f, 0.0f), inMaxVel,	rndPos));
	}

	//initialise the boundaries
	xBoundary = inXBoundary;
	yBoundary = inYBoundary;
	zBoundary = inZBoundary;

	//initialise all of the rules to be on
	applyRule1 = applyRule2 = applyRule3 = 1;

	//initialise the max velocity
	maxVel = inMaxVel;
}

Flocking::~Flocking()
{
	//delete pointers
	for (unsigned int i = 0; i < boids.size(); i++)
	{
		delete boids[i];
	}
}

void Flocking::update2D()
{
	//initialise the resultant velocities
	Vec2 v1 = Vec2( 0.0f, 0.0f );
	Vec2 v2 = Vec2( 0.0f, 0.0f );
	Vec2 v3 = Vec2( 0.0f, 0.0f );
	Vec2 v4 = Vec2( 0.0f, 0.0f );

	//The speed increase of the boids
	float speed = 150.0f;

	//test each Boid
	for (unsigned int i = 0; i < boids.size(); i++)
	{
		//test rule 1 and apply activity
		v1 = (rule1(i) * (float)applyRule1);
		//test rule 2 and apply activity
		v2 = (rule2(i) * (float)applyRule2);
		//test rule 3 and apply activity
		v3 = (rule3(i) * (float)applyRule3);

		//apply boundaries
		v4 = roughBoundaries(i);

		//update the Boid velocity
		boids[i]->setDirection2D(boids[i]->getDirection2D() + v1 + v2 + v3 + v4);
		//limit the velocity of the Boid
		limitVelocity(i);
		//update the Boid position
		boids[i]->setPosition2D(boids[i]->getPosition2D() + (boids[i]->getDirection2D() * Application::getDT()) * speed);
	}
}

void Flocking::update3D()
{
	//initialise the resultant velocities
	Vec3 v1 = Vec3(0.0f, 0.0f, 0.0f);
	Vec3 v2 = Vec3(0.0f, 0.0f, 0.0f);
	Vec3 v3 = Vec3(0.0f, 0.0f, 0.0f);
	Vec3 v4 = Vec3(0.0f, 0.0f, 0.0f);

	//The speed increase of the boids
	float speed = 20.0f;

	//test each Boid
	for (unsigned int i = 0; i < boids.size(); i++)
	{
		//test rule 1 and apply activity
		v1 = (ruleOne3D(i) * (float)applyRule1);
		//test rule 2 and apply activity
		v2 = (ruleTwo3D(i) * (float)applyRule2);
		//test rule 3 and apply activity
		v3 = (ruleThree3D(i) * (float)applyRule3);

		//apply boundaries
		v4 = roughBoundaries3D(i);

		//update the Boid velocity
		boids[i]->setDirection3D(boids[i]->getDirection3D() + v1 + v2 + v3 + v4);
		//limit the velocity of the Boid
		limitVelocity3D(i);

		//update the Boid position
		boids[i]->setPosition3D(boids[i]->getPosition3D() + (boids[i]->getDirection3D() * Application::getDT()) * speed);

		//update the game object
		boids[i]->getObject()->getComponent<TransformComponent>().lock()->setPos(boids[i]->getPosition3D());
	}
}

void Flocking::draw2D()
{
	//display the Boid objects
	for (unsigned int i = 0; i < boids.size(); i++)
	{
		//display the Boid
		boids[i]->draw2D();
	}
}

Vec2 Flocking::rule1(int boidIndex)
{
	//initialise the new velocity
	Vec2 vel = Vec2(0.0f, 0.0f);
	//initialise the center of mass
	Vec2 cOfM = Vec2(0.0f, 0.0f);

	/*test each Boid*/
	for (unsigned int i = 0; i < boids.size(); i++)
	{
		//if the Boid to be tested is not the inputed Boid
		if (i != (unsigned int)boidIndex)
		{
			//update the center of mass
			cOfM = boids[i]->getPosition2D() + cOfM;
		}
	}

	//divide the center of mass by the number of Boid objects tested
	cOfM = cOfM / (float)(boids.size() - 1);

	//set the new velocity to the amount to move towards the Boid (1% of the distance in this case)
	vel = (cOfM - boids[boidIndex]->getPosition2D()) / 100;

	//return the new velocity
	return vel;
}

Vec3 Flocking::ruleOne3D(int boidIndex)
{
	//initialise the new velocity
	Vec3 vel = Vec3(0.0f, 0.0f, 0.0f);
	//initialise the center of mass
	Vec3 cOfM = Vec3(0.0f, 0.0f, 0.0f);

	/*test each Boid*/
	for (unsigned int i = 0; i < boids.size(); i++)
	{
		//if the Boid to be tested is not the inputed Boid
		if (i != (unsigned int)boidIndex)
		{
			//update the center of mass
			cOfM = boids[i]->getPosition3D() + cOfM;
		}
	}

	//divide the center of mass by the number of Boid objects tested
	cOfM = cOfM / (float)(boids.size() - 1);

	//set the new velocity to the amount to move towards the Boid (1% of the distance in this case)
	vel = (cOfM - boids[boidIndex]->getPosition3D()) / 100;

	//return the new velocity
	return vel;
}

Vec2 Flocking::rule2(int boidIndex)
{
	//the new velocity
	Vec2 vel = Vec2(0.0f, 0.0f);

	//test each Boid
	for (unsigned int i = 0; i < boids.size(); i++)
	{
		//if the Boid to be tested is not the inputed Boid
		if (i != (unsigned int)boidIndex)
		{
			//if the Boid is closer than 10 pixels to another Boid on the x axis (using absolute values)
			if (std::abs(boids[boidIndex]->getPosition2D().x - boids[i]->getPosition2D().x) < 10)
			{
				vel.x = vel.x - (boids[i]->getPosition2D().x - boids[boidIndex]->getPosition2D().x);
			}

			//if the Boid is closer than 10 pixels to another Boid on the y axis (using absolute values)
			if (std::abs(boids[boidIndex]->getPosition2D().y - boids[i]->getPosition2D().y) < 10)
			{
				vel.y = vel.y - (boids[i]->getPosition2D().y - boids[boidIndex]->getPosition2D().y);
			}
		}
	}

	//return the new velocity
	return vel;
}

Vec3 Flocking::ruleTwo3D(int boidIndex)
{
	//the new velocity
	Vec3 vel = Vec3(0.0f, 0.0f, 0.0f);

	//test each Boid
	for (unsigned int i = 0; i < boids.size(); i++)
	{
		//if the Boid to be tested is not the inputed Boid
		if (i != (unsigned int)boidIndex)
		{
			//if the Boid is closer than 0.05f to another Boid on the x axis (using absolute values)
			if (std::abs(boids[boidIndex]->getPosition3D().x - boids[i]->getPosition3D().x) < 0.3f)
			{
				vel.x = vel.x - (boids[i]->getPosition3D().x - boids[boidIndex]->getPosition3D().x);
			}

			//if the Boid is closer than 0.05f to another Boid on the y axis (using absolute values)
			if (std::abs(boids[boidIndex]->getPosition3D().y - boids[i]->getPosition3D().y) < 0.3f)
			{
				vel.y = vel.y - (boids[i]->getPosition3D().y - boids[boidIndex]->getPosition3D().y);
			}

			//if the Boid is closer than 0.05f to another Boid on the z axis (using absolute values)
			if (std::abs(boids[boidIndex]->getPosition3D().z - boids[i]->getPosition3D().z) < 0.3f)
			{
				vel.z = vel.z - (boids[i]->getPosition3D().z - boids[boidIndex]->getPosition3D().z);
			}
		}
	}

	//return the new velocity
	return vel;
}

Vec2 Flocking::rule3(int boidIndex)
{
	//initialise the new velocity
	Vec2 vel = Vec2(0.0f, 0.0f);

	//test each Boid
	for (unsigned int i = 0; i < boids.size(); i++)
	{
		//if the Boid to be tested is not the inputed Boid
		if (i != (unsigned int)boidIndex)
		{
			//add all of the Boid velocities together
			vel = vel + boids[i]->getDirection2D();
		}
	}

	//get the average velocity
	vel = vel / (float)(boids.size() - 1);

	//set it to about an eighth of the Boid velocity
	vel = (vel - boids[boidIndex]->getDirection2D()) / 8;

	//return the new velocity
	return vel;
}

Vec3 Flocking::ruleThree3D(int boidIndex)
{
	//initialise the new velocity
	Vec3 vel = Vec3(0.0f, 0.0f, 0.0f);

	//test each Boid
	for (unsigned int i = 0; i < boids.size(); i++)
	{
		//if the Boid to be tested is not the inputed Boid
		if (i != (unsigned int)boidIndex)
		{
			//add all of the Boid velocities together
			vel = vel + boids[i]->getDirection3D();
		}
	}

	//get the average velocity
	vel = vel / (float)(boids.size() - 1);

	//set it to about an eighth of the Boid velocity
	vel = (vel - boids[boidIndex]->getDirection3D()) / 8;

	//return the new velocity
	return vel;
}

Vec2 Flocking::roughBoundaries(int boidIndex)
{
	//initialise the new velocity
	Vec2 vel = Vec2(0.0f, 0.0f);

	//check if the Boid is off the right of the screen
	if (boids[boidIndex]->getPosition2D().x > xBoundary)
	{
		//set a negative x velocity
		vel.x = -10.0f;
	}
	//check if the Boid is off the right of the screen
	else if (boids[boidIndex]->getPosition2D().x < 0)
	{
		//set a positive x velocity
		vel.x = 10.0f;
	}

	//check if the Boid is off the bottom of the screen
	if (boids[boidIndex]->getPosition2D().y > yBoundary)
	{
		//set a negative y velocity
		vel.y = -10.0f;
	}
	//check if the Boid is off the top of the screen
	else if (boids[boidIndex]->getPosition2D().y < 0)
	{
		//set a positive y velocity
		vel.y = 10.0f;
	}

	//return the new velocity
	return vel;
}

Vec3 Flocking::roughBoundaries3D(int boidIndex)
{
	//initialise the new velocity
	Vec3 vel = Vec3(0.0f, 0.0f, 0.0f);

	//check if the Boid is off the right of the screen
	if (boids[boidIndex]->getPosition3D().x > xBoundary)
	{
		//set a negative x velocity
		vel.x = -5.0f;
	}
	//check if the Boid is off the right of the screen
	else if (boids[boidIndex]->getPosition3D().x < -xBoundary)
	{
		//set a positive x velocity
		vel.x = 5.0;
	}

	//check if the Boid is off the bottom of the screen
	if (boids[boidIndex]->getPosition3D().y > yBoundary)
	{
		//set a negative y velocity
		vel.y = -5.0f;
	}
	//check if the Boid is off the top of the screen
	else if (boids[boidIndex]->getPosition3D().y < -yBoundary)
	{
		//set a positive y velocity
		vel.y = 5.0f;
	}

	//check if the Boid is off the bottom of the screen
	if (boids[boidIndex]->getPosition3D().z > zBoundary)
	{
		//set a negative z velocity
		vel.z = -5.0f;
	}
	//check if the Boid is off the top of the screen
	else if (boids[boidIndex]->getPosition3D().z < -zBoundary)
	{
		//set a positive z velocity
		vel.z = 5.0f;
	}

	//return the new velocity
	return vel;
}

void Flocking::limitVelocity(int boidIndex)
{
	//test if the absolute of the x velocity is greater than the max velocity
	if (std::abs(boids[boidIndex]->getDirection2D().x) > maxVel)
	{
		//work out if negative or positive
		float sign = boids[boidIndex]->getDirection2D().x / std::abs(boids[boidIndex]->getDirection2D().x);
		//set the x velocity to the max velocity
		boids[boidIndex]->setDirection2D(Vec2(maxVel * sign, boids[boidIndex]->getDirection2D().y));
	}

	//test if the absolute of the y velocity is greater than the max velocity
	if (std::abs(boids[boidIndex]->getDirection2D().y) > maxVel)
	{
		//work out if negative or positive
		float sign = boids[boidIndex]->getDirection2D().y / std::abs(boids[boidIndex]->getDirection2D().y);
		//set the y velocity to the max velocity
		boids[boidIndex]->setDirection2D(Vec2(boids[boidIndex]->getDirection2D().x, maxVel * sign));
	}
}

void Flocking::limitVelocity3D(int boidIndex)
{
	//test if the absolute of the x velocity is greater than the max velocity
	if (std::abs(boids[boidIndex]->getDirection3D().x) > maxVel)
	{
		//work out if negative or positive
		float sign = boids[boidIndex]->getDirection3D().x / std::abs(boids[boidIndex]->getDirection3D().x);
		//set the x velocity to the max velocity
		boids[boidIndex]->setDirection3D(Vec3(maxVel * sign, boids[boidIndex]->getDirection3D().y, boids[boidIndex]->getDirection3D().z));
	}

	//test if the absolute of the y velocity is greater than the max velocity
	if (std::abs(boids[boidIndex]->getDirection3D().y) > maxVel)
	{
		//work out if negative or positive
		float sign = boids[boidIndex]->getDirection3D().y / std::abs(boids[boidIndex]->getDirection3D().y);
		//set the y velocity to the max velocity
		boids[boidIndex]->setDirection3D(Vec3(boids[boidIndex]->getDirection3D().x, maxVel * sign, boids[boidIndex]->getDirection3D().z));
	}

	//test if the absolute of the z velocity is greater than the max velocity
	if (std::abs(boids[boidIndex]->getDirection3D().z) > maxVel)
	{
		//work out if negative or positive
		float sign = boids[boidIndex]->getDirection3D().z / std::abs(boids[boidIndex]->getDirection3D().z);
		//set the z velocity to the max velocity
		boids[boidIndex]->setDirection3D(Vec3(boids[boidIndex]->getDirection3D().x, boids[boidIndex]->getDirection3D().y, maxVel * sign));
	}
}

void Flocking::setRule1(int inApplyRule1)
{
	//set the rule
	applyRule1 = inApplyRule1;
}

void Flocking::setRule2(int inApplyRule2)
{
	//set the rule
	applyRule2 = inApplyRule2;
}

void Flocking::setRule3(int inApplyRule3)
{
	//set the rule
	applyRule3 = inApplyRule3;
}