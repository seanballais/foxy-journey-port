#pragma once
#include "physicObject.h"

class Player : public physicsObject
{
public:
	Player(float px, float py);
	~Player();

	virtual void update(float deltaTime) override;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;


private:
	int animationSpeed;

	int currentFrame;

	float accumulatedTime;
};

