#include "app.h"
#include "menuState.h"
#include "gameplayState.h"
#include "gameoverState.h"
#include "Assets.h"



app::app()
{
	init();
}


app::~app()
{
	for (auto & i : gameStates)
	{
		delete i.second;
	}
}

void app::start()
{
	music.play();
	while (mainWindow.isOpen())
	{
		if (stateChange)
		{
			currentState = gameStates[nextState];
			currentState->scale();
			stateChange = false;
		}

		updateUtils();

		currentState->handleEvents();
		currentState->update(deltaTime);
		currentState->render();
		
	}

}

void app::init()
{
	windowWidth = 1152;
	windowHeight = 756;

	asset::loadVariables("./config/paths.conf");

	mainWindow.create(sf::VideoMode(windowWidth,windowHeight),"Foxy Journey",sf::Style::Titlebar | sf::Style::Close);

	sf::Image icon;
	icon.loadFromFile(asset::variables["$TEXTURES"] + "icon.png");
	mainWindow.setIcon(64,64,icon.getPixelsPtr());

	mainWindow.setFramerateLimit(30);

	deltaTime = 0.0f;

	mainClock.restart();

	stateChange = false;

	gameStates[MENU] = new menuState(this, &mainWindow);
	gameStates[GAMEPLAY] = new gameplayState(this, &mainWindow);
	gameStates[GAMEOVER] = new gameoverState(this, &mainWindow);

	changeState(MENU);

	music.setLoop(true);
	music.setVolume(20);

	music.openFromFile(asset::variables["$SOUNDS"] + "foxJourney.wav");
}

void app::render()
{
	mainWindow.clear();
	mainWindow.display();
}

void app::updateUtils()
{
	deltaTime = mainClock.getElapsedTime().asSeconds();
	mainClock.restart();
}

void app::changeState(States tNextState)
{
	nextState = tNextState;
	stateChange = true;
}
