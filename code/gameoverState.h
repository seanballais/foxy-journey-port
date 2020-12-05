#pragma once
#include "state.h"
#include "background.h"

class app;

class gameoverState : public State
{
public:
	gameoverState(app * tEngine, sf::RenderWindow * tWindow);
	~gameoverState();

	void update(float deltaTime) override;
	void handleEvents() override;
	void render() override;
	void scale() override;
	void init() override;

	app * engine;

private:
	background * backImage;

	sf::Text gameoverText;
	sf::Text tittleText;
	sf::Text scoreText;

	int opacity;
	bool direction;

	float accumulatedTime;
};


