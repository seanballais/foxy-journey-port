#pragma once

#include <SFML/Graphics.hpp>

class State
{
public:
	State() {};

	virtual ~State() {};

	virtual void update(float deltaTime) {};
	virtual void handleEvents() {};
	virtual void render() {};
	virtual void scale() {};
	virtual void init() {};

	sf::Event event;
	sf::RenderWindow * window;

};
