#include "StateManager.h"

namespace States
{

	StateManager::StateManager()
	{
	}

	StateManager::~StateManager()
	{
		//loops thorough all of the states in the vector and deletes them all
		for (unsigned int i = 0; i < currentStates.size(); i++)
		{
			delete currentStates.at(i);
		}
	}

	void StateManager::addState(State* state)
	{
		currentStates.push_back(state);
		Core::Logging::logI(state->getName() + " State added");
	}

	void StateManager::changeState(State* state) 
	{
		std::string name;
		//loops thorough all of the states in the vector and deletes them all
		for (unsigned int i = 0; i < currentStates.size(); i++)
		{
			name = currentStates.at(i)->getName();
			delete currentStates.at(i);
			Core::Logging::logI(name + " State removed");
		}
	
		//clear the vector of current states
		currentStates.clear();
		//add the new state that will be being run
		addState(state);
		Core::Logging::logI("State changed to " + state->getName());
	}

	void StateManager::removeLastState()
	{
		std::string name = currentStates.back()->getName();
		//delete the last state in the vector
		delete currentStates.back();
		//remove the last state from the vector
		currentStates.pop_back();
		Core::Logging::logI(name + " State removed");
	}

	bool StateManager::input() 
	{
		return currentStates.back()->input();
	}

	void StateManager::update(float dt) 
	{
		//updates the state on the top of the stack so the lower state are unaltered
		currentStates.back()->update(dt);
	}

	void StateManager::draw() 
	{
		//clear the frame-buffer to a colour
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		//write colour to the frame-buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//loops through the running stacks and draws them all, with the latest added state on top
		for (unsigned int i = 0; i < currentStates.size(); i++)
		{
			//draw the state
			currentStates.at(i)->draw();
		}

		//display the window
		SDL_GL_SwapWindow(currentStates[0]->getWindow());
	}

}// End of states namespace