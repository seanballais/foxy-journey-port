#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <map>

#include "state.h"

enum States
{
	MENU,
	GAMEPLAY,
	GAMEOVER
};

class app
{
public:

	app();
	~app();

	void start();

	void changeState(States tNextState);

private:

	void init();

	void render();

	void updateUtils();



public:
	std::map<States, State *> gameStates;

	float score;
private:

	sf::RenderWindow mainWindow;
	sf::Event mainEvent;

	sf::Clock mainClock;

	float deltaTime;

	int windowWidth;
	int windowHeight;

	

	State * currentState;

	States nextState;

	bool stateChange;

	sf::Music music;
};

