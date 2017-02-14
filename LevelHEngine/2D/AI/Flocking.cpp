#include "Flocking.h"
#include <cmath>

Flocking::Flocking(int inNumberOfBoids, Sprite* inSprite, int inXBoundary, int inYBoundary, float inMaxVel, int inScreenHeight)
{
	//initialize random seed
	srand((unsigned int)time(NULL));

	//initialise the size of the screen height
	screenHeight = inScreenHeight;

	//initialise a the number of Boid objects
	for (int i = 0; i < inNumberOfBoids; i++)
	{
		//creates a Boid at a random position on the screen
		boids.push_back(new Boid(inSprite, Scaling::scaleNumber(4.0f, inScreenHeight), Vec2(0.0f, 0.0f), inMaxVel, 
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

Flocking::~Flocking()
{
	//delete pointers
	for (unsigned int i = 0; i < boids.size(); i++)
	{
		delete boids[i];
	}
}

void Flocking::update(float dt)
{
	//initialise the resultant velocities
	Vec2 v1 = Vec2( 0.0f, 0.0f );
	Vec2 v2 = Vec2( 0.0f, 0.0f );
	Vec2 v3 = Vec2( 0.0f, 0.0f );
	Vec2 v4 = Vec2( 0.0f, 0.0f );

	//The speed increase of the boids
	float speed = 25.0f;

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
		boids[i]->setDirection(boids[i]->getDirection() + v1 + v2 + v3 + v4);
		//limit the velocity of the Boid
		limitVelocity(i);
		//update the Boid position
		boids[i]->setPosition(boids[i]->getPosition() + (boids[i]->getDirection() * dt) * speed);
	}
}

void Flocking::draw(SDL_Renderer* renderer)
{
	//display the Boid objects
	for (unsigned int i = 0; i < boids.size(); i++)
	{
		//display the Boid
		boids[i]->draw(renderer);
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
			cOfM = boids[i]->getPosition() + cOfM;
		}
	}

	//divide the center of mass by the number of Boid objects tested
	cOfM = cOfM / (float)(boids.size() - 1);

	//set the new velocity to the amount to move towards the Boid (1% of the distance in this case)
	vel = (cOfM - boids[boidIndex]->getPosition()) / 100;

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
			if (std::abs(boids[boidIndex]->getPosition().x - boids[i]->getPosition().x) < 10)
			{
				vel.x = vel.x - (boids[i]->getPosition().x - boids[boidIndex]->getPosition().x);
			}

			//if the Boid is closer than 10 pixels to another Boid on the y axis (using absolute values)
			if (std::abs(boids[boidIndex]->getPosition().y - boids[i]->getPosition().y) < 10)
			{
				vel.y = vel.y - (boids[i]->getPosition().y - boids[boidIndex]->getPosition().y);
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
			vel = vel + boids[i]->getDirection();
		}
	}

	//get the average velocity
	vel = vel / (float)(boids.size() - 1);

	//set it to about an eighth of the Boid velocity
	vel = (vel - boids[boidIndex]->getDirection()) / 8;

	//return the new velocity
	return vel;
}

Vec2 Flocking::roughBoundaries(int boidIndex)
{
	//initialise the new velocity
	Vec2 vel = Vec2(0.0f, 0.0f);

	//check if the Boid is off the right of the screen
	if (boids[boidIndex]->getPosition().x > xBoundary)
	{
		//set a negative x velocity
		vel.x = -10.0f;
	}
	//check if the Boid is off the right of the screen
	else if (boids[boidIndex]->getPosition().x < 0)
	{
		//set a positive x velocity
		vel.x = 10.0f;
	}

	//check if the Boid is off the bottom of the screen
	if (boids[boidIndex]->getPosition().y > yBoundary)
	{
		//set a negative y velocity
		vel.y = -10.0f;
	}
	//check if the Boid is off the top of the screen
	else if (boids[boidIndex]->getPosition().y < 0)
	{
		//set a positive y velocity
		vel.y = 10.0f;
	}

	//return the new velocity
	return vel;
}

void Flocking::limitVelocity(int boidIndex)
{
	//test if the absolute of the x velocity is greater than the max velocity
	if (std::abs(boids[boidIndex]->getDirection().x) > maxVel)
	{
		//work out if negative or positive
		float sign = boids[boidIndex]->getDirection().x / std::abs(boids[boidIndex]->getDirection().x);
		//set the x velocity to the max velocity
		boids[boidIndex]->setDirection(Vec2(maxVel * sign, boids[boidIndex]->getDirection().y));
	}

	//test if the absolute of the y velocity is greater than the max velocity
	if (std::abs(boids[boidIndex]->getDirection().y) > maxVel)
	{
		//work out if negative or positive
		float sign = boids[boidIndex]->getDirection().y / std::abs(boids[boidIndex]->getDirection().y);
		//set the y velocity to the max velocity
		boids[boidIndex]->setDirection(Vec2(boids[boidIndex]->getDirection().x, maxVel * sign));
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