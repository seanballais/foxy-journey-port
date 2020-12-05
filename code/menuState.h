#pragma once
#include "state.h"
#include "background.h"

class app;

class menuState : public State
{
public:
	menuState(app * tEngine, sf::RenderWindow * tWindow);
	~menuState();

	void update(float deltaTime) override;
	void handleEvents() override;
	void render() override;
	void scale() override;
	void init() override;

	app * engine;

private:
	background * backImage;

	sf::Text menuText;
	sf::Text tittleText;

	int opacity;
	bool direction;

	float accumulatedTime;
};


