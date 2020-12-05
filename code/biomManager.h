#pragma once
#include "biom.h"
#include "physicObject.h"

#include <SFML/Graphics.hpp>

#include <deque>

class biomManager : public sf::Drawable, public sf::Transformable
{
public:
	biomManager(physicsObject * pPlayer);
	~biomManager();

	void update(Camera & pCamera, float deltaTime, int marginY);

	std::deque<biom *> biomsToDraw;

	

private:
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

	void addBiom(int biomId);

	float transitionStep;
	float accumulatedOffset;

	physicsObject * player;

private:
	
};

