#include "biom.h"



biom::biom(std::string pTexture, std::string biomName)
{
	layers.push_back(new background(pTexture));
	biomId = biomName;
}


biom::~biom()
{
	for (auto & l : layers)
	{
		delete l;
	}
}

void biom::update(Camera & pCamera, float deltaTime, int marginY)
{
	float posX = getPosition().x;

	float cameraX = pCamera.view->getCenter().x - (pCamera.view->getSize().x / 2.0f);

	float xStep = (float)pCamera.windowWidth / (vertexCount - MARGIN);

	if (cameraX - posX > xStep)
	{
		move(cameraX - posX, 0);
	}
}

void biom::reset()
{
	for (auto & l : layers)
	{
		l->setPosition(0, l->getPosition().y);
	}
}

void biom::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	for (auto & l : layers)
	{
		
		target.draw(*l, states);
	}
}
