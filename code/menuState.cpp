#include "menuState.h"
#include "app.h"

#include "gameplayState.h"

#include "Assets.h"





menuState::menuState(app * tEngine, sf::RenderWindow * tWindow)
{
	window = tWindow;
	engine = tEngine;

	init();
}


menuState::~menuState()
{
	delete backImage;
}

void menuState::update(float deltaTime)
{
	accumulatedTime += deltaTime;

	if (accumulatedTime >= 0.1)
	{
		accumulatedTime = 0.0f;


		if (direction) { opacity += 15; }
		else{ opacity -= 15; }
			
	}

	if (opacity > 255)
	{
		opacity = 255;
		direction = false;
	}

	if (opacity < 0)
	{
		opacity = 0;
		direction = true;
	}

	menuText.setFillColor(sf::Color(255, 255, 255, opacity));
}

void menuState::handleEvents()
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
			case sf::Keyboard::Space:
				engine->changeState(GAMEPLAY);
				break;
			}
			break;
		}
	}
}

void menuState::render()
{
	window->clear(sf::Color::Black);

	window->draw(*backImage);
	window->draw(tittleText);
	window->draw(menuText);

	window->display();
}

void menuState::scale()
{
	int backgroundId = rand() % 3 + 1;

	delete backImage;

	switch (backgroundId)
	{
	case 1:
		backImage = new background("hills");
		break;

	case 2:
		backImage = new background("mountains");
		break;

	case 3:
		backImage = new background("bamboo");
		break;
	}

	backImage->setPosition(0, 0);
}

void menuState::init()
{
	scale();

	menuText.setFont(asset::get().getFont("ESKARGOT"));
	tittleText.setFont(asset::get().getFont("ESKARGOT"));

	tittleText.setString("Foxy Journey");
	tittleText.setFillColor(sf::Color::White);
	tittleText.setCharacterSize(90);
	tittleText.setStyle(sf::Text::Bold);

	tittleText.setPosition(window->getSize().x / 2 - tittleText.getGlobalBounds().width / 2,window->getSize().y * 0.25f);

	menuText.setString("Press [SPACE] to play");
	menuText.setFillColor(sf::Color::White);
	menuText.setCharacterSize(50);
	menuText.setStyle(sf::Text::Bold);

	menuText.setPosition(window->getSize().x / 2 - menuText.getGlobalBounds().width / 2, window->getSize().y * 0.5f);
	
	direction = true;
	opacity = 255;

	accumulatedTime = 0.0f;
}
