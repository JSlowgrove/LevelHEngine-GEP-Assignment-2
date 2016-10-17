#include "S_StateManager.h"

S_StateManager::S_StateManager()
{
}

S_StateManager::~S_StateManager()
{
	//Loops thorough all of the states in the vector and deletes them all.
	for (unsigned int i = 0; i < currentStates.size(); i++)
	{
		delete currentStates.at(i);
	}
}

void S_StateManager::addState(S_State* state)
{
	//Adds a state to the current states vector, for when we have multiple states at once.
	currentStates.push_back(state);
}

void S_StateManager::changeState(S_State* state)
{
	//Loops thorough all of the states in the vector and deletes them all.
	for (unsigned int i = 0; i < currentStates.size(); i++)
	{
		delete currentStates.at(i);
	}
	
	//Clear the vector of current states.
	currentStates.clear();
	//Add the new state that will be being run.
	addState(state);
}

void S_StateManager::removeLastState()
{
	//Delete the last state in the vector.
	delete currentStates.back();
	//Remove the last state from the vector.
	currentStates.pop_back();
}

bool S_StateManager::input()
{
	return currentStates.back()->input();
}

void S_StateManager::update(float dt)
{
	currentStates.back()->update(dt);
}

void S_StateManager::draw()
{
	//Loops through the running stacks and draws them all, with the latest added state on top.
	for (unsigned int i = 0; i < currentStates.size(); i++)
	{
		currentStates.at(i)->draw();
	}
}

void S_StateManager::drawOpenGL()
{
	/*clear the frame-buffer to a colour*/
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	/*write colour to the frame-buffer*/
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/*loops through the running stacks and draws them all, with the latest added state on top*/
	for (unsigned int i = 0; i < currentStates.size(); i++)
	{
		/*draw the state*/
		currentStates.at(i)->draw();
	}

	/*display the window*/
	SDL_GL_SwapWindow(currentStates[0]->getWindow());
}