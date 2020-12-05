#pragma once
#include "state.h"
#include "terrain.h"
#include "biomManager.h"
#include "Camera.h"

#include "physicObjects.h"

#include <list>

class app;

class gameplayState : public State
{
public:
	gameplayState(app * tEngine, sf::RenderWindow * tWindow);
	~gameplayState();

	void update(float deltaTime) override;
	void handleEvents() override;
	void render() override;
	void scale() override;
	void init() override;


	app * engine;

	Camera mainCamera;

	sf::View gameView;

	physicsObject * player;
	
	std::list<physicsObject *> objects;

	terrain * currentTerrain;

	biomManager * currentBiomManager;

	bool gameOver;

	float playerScore;

	
private:
	void reset();
};


