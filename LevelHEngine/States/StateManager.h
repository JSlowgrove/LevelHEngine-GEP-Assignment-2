#pragma once

#include <vector>
#include "State.h"

/**
@brief Creates a StateManager object.
*/
class StateManager
{
public:
	/**
	@brief Constructs a StateManager object.
	*/
	StateManager();

	/**
	@brief Destructs a StateManager object.
	*/
	~StateManager();

	/**
	@brief Adds a new state to the current stack of states.
	@param state A pointer to the State in use.
	*/
	void addState(State* state);

	/**
	@brief Changes the current State to a new State.
	@param state A pointer to the State in use.
	*/
	void changeState(State* state);

	/**
	@brief Removes the last State from the vector.
	*/
	void removeLastState();

	/**
	@brief Handles the user input in the current State.
	@returns If false then quit the application.
	*/
	bool input();

	/**
	@brief Updates the current State.
	*/
	void update();

	/**
	@param Draws the current State.
	*/
	void draw();

private:
	///The current states that are in use
	std::vector<State*> currentStates;
};