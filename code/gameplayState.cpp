#include <cmath>

#include "gameplayState.h"
#include "app.h"

#include "Assets.h"
#include "noiseGenerator.h"

#include "terrain.h"

#include "player.h"





gameplayState::gameplayState(app * tEngine, sf::RenderWindow * tWindow)
{
	window = tWindow;
	engine = tEngine;

	init();
}


gameplayState::~gameplayState()
{
	delete currentTerrain;

	delete currentBiomManager;

	for (auto & object : objects)
	{
		delete object;
	}
}

void gameplayState::update(float deltaTime)
{
	
	
		if (!currentBiomManager->biomsToDraw.empty())
			mainCamera.biom = currentBiomManager->biomsToDraw.front()->biomId;

		if (player->px > mainCamera.windowWidth * CHUNK_SIZE)
		{
			player->px = mainCamera.windowWidth / 2;
			currentTerrain->setPosition(0, currentTerrain->getPosition().y);
			currentBiomManager->setPosition(0, currentBiomManager->getPosition().y);

		}



		for (int x = 0; x < 3; x++)
			for (auto & i : objects)
			{

				i->ay += GRAVITY;

				i->vx += i->ax * deltaTime;
				i->vy += i->ay * deltaTime;

				float newPosX = i->px + i->vx * deltaTime;
				float newPosY = i->py + i->vy * deltaTime;

				i->ax = 0.0f;
				i->ay = 0.0f;

				bool colision = false;

				for (int v = 0; v < currentTerrain->terrainVerticies.size(); v++)
				{
					float testX = v * (window->getSize().x / (currentTerrain->terrainVerticies.size() - MARGIN)) + currentTerrain->getPosition().x;
					float testY = currentTerrain->terrainVerticies[v] * 100 + window->getSize().y * 0.78;

					float distance = sqrtf((newPosX - testX) * (newPosX - testX) + (newPosY - testY) * (newPosY - testY));


					if (distance < i->radius - 1)
					{
						colision = true;
					}

					if (currentTerrain->obstacles[v] != nullptr)
					{
						if (distance < (i->radius + currentTerrain->obstacles[v]->radius))
						{
							i->vx += currentTerrain->obstacles[v]->slowDown;

							if (i->vx < 0) i->vx = 0;

							delete currentTerrain->obstacles[v];
							currentTerrain->obstacles[v] = nullptr;

						}
					}


				}

				if (colision)
				{
					i->canJump = true;

					if (i->vx != 0)
						i->py -= 1.0f;


					i->vy = 0.0f;
				}
				else
				{


					i->px = newPosX;
					i->py = newPosY;
				}




			}



		float cameraX = player->px;
		float cameraY = player->py;

		if (cameraY > mainCamera.windowHeight / 2)
		{
			cameraY = mainCamera.windowHeight / 2;
		}

		for (auto & o : objects)
		{
			o->update(deltaTime);
		}

		gameView.setCenter(cameraX, cameraY);

		window->setView(gameView);

		mainCamera.view = &window->getView();

		currentTerrain->update(mainCamera, deltaTime, mainCamera.windowHeight * 0.78);

		currentBiomManager->setPosition(player->px - mainCamera.windowWidth / 2, 0);
		currentBiomManager->update(mainCamera, deltaTime, mainCamera.windowHeight * 0.78);

		playerScore += player->vx * deltaTime;;

		if (player->vx <= 50)
		{
			gameOver = true;
			engine->score = playerScore;
			engine->changeState(GAMEOVER);
		}
	
	
}

void gameplayState::handleEvents()
{


	while (window->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window->close();
			break;

		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
			case sf::Keyboard::Left:
				//player->vx = 0.0f;
				break;

			case sf::Keyboard::Right:
				//player->vx = 300.0f;
				break;

			case sf::Keyboard::Space:

				if(player->canJump)
				player->vy = player->jumpiness * -1;
				player->canJump = false;
				break;
			}
			break;
		}
	}
}

void gameplayState::render()
{
	window->clear(sf::Color(80,175,228));

	window->draw(*currentBiomManager);
	window->draw(*currentTerrain);
	
	for (auto & i : objects)
	{
		i->updateTextures();
		window->draw(*i);
	}

	window->display();
}

void gameplayState::scale()
{
	mainCamera.windowHeight = window->getSize().y;
	mainCamera.windowWidth = window->getSize().x;

	reset();
	
	
}

void gameplayState::init()
{
	srand(time(NULL));

	player = new Player(window->getSize().x / 2.0f,window->getSize().y / 2);

	objects.push_back(player);

	gameView.setCenter(player->px,player->py);
	gameView.setSize(window->getSize().x,window->getSize().y);

	window->setView(gameView);

	currentTerrain = new terrain(window->getSize().x, sf::Color(30,30,30));

	currentBiomManager = new biomManager(player);

		
}

void gameplayState::reset()
{
	player->vx = 300.0f;
	player->vy = 0;

	player->px = window->getSize().x * 0.5f;
	player->py = window->getSize().y * 0.7f;

	gameView.setCenter(player->px, player->py);
	gameView.setSize(window->getSize().x, window->getSize().y);

	window->setView(gameView);

	playerScore = 0.0f;

	delete currentBiomManager;
	delete currentTerrain;

	currentTerrain = new terrain(window->getSize().x, sf::Color(30, 30, 30));

	currentBiomManager = new biomManager(player);
	
	player->ax = 0.01f;

	update(0.0f);
}
