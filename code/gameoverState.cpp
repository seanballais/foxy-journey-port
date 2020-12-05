#include "gameoverState.h"
#include "app.h"

#include "gameplayState.h"

#include "Assets.h"





gameoverState::gameoverState(app * tEngine, sf::RenderWindow * tWindow)
{
	window = tWindow;
	engine = tEngine;
	backImage = nullptr;

	init();
}


gameoverState::~gameoverState()
{
	delete backImage;
}

void gameoverState::update(float deltaTime)
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

	gameoverText.setFillColor(sf::Color(255, 255, 255, opacity));
}

void gameoverState::handleEvents()
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
			case sf::Keyboard::Return:
				engine->changeState(MENU);
				break;
			}
			break;
		}
	}
}

void gameoverState::render()
{
	window->clear(sf::Color::Black);

	window->draw(*backImage);
	window->draw(tittleText);
	window->draw(gameoverText);
	window->draw(scoreText);

	window->display();
}

void gameoverState::scale()
{
	int backgroundId = rand() % 3 + 1;

	if (backImage) {
		delete backImage;
	}

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

	window->setView(window->getDefaultView());

	scoreText.setString(std::to_string(engine->score));
}

void gameoverState::init()
{
	scale();

	gameoverText.setFont(asset::get().getFont("ESKARGOT"));
	tittleText.setFont(asset::get().getFont("ESKARGOT"));
	scoreText.setFont(asset::get().getFont("ESKARGOT"));

	tittleText.setString("Game Over");
	tittleText.setFillColor(sf::Color::White);
	tittleText.setCharacterSize(90);
	tittleText.setStyle(sf::Text::Bold);

	tittleText.setPosition(window->getSize().x / 2 - tittleText.getGlobalBounds().width / 2,window->getSize().y * 0.25f);

	gameoverText.setString("Press [ENTER] to continue");
	gameoverText.setFillColor(sf::Color::White);
	gameoverText.setCharacterSize(40);
	gameoverText.setStyle(sf::Text::Bold);

	gameoverText.setPosition(window->getSize().x / 2 - gameoverText.getGlobalBounds().width / 2, window->getSize().y * 0.7f);
	
	
	scoreText.setFillColor(sf::Color(241,101,18));
	scoreText.setCharacterSize(50);
	scoreText.setStyle(sf::Text::Bold);

	scoreText.setPosition(window->getSize().x / 2 - scoreText.getGlobalBounds().width / 2, window->getSize().y * 0.5f);

	direction = true;
	opacity = 255;

	accumulatedTime = 0.0f;
}
