#include "player.h"
#include "Assets.h"

static const int FRAMECOUNT = 8;

Player::Player(float px, float py) : physicsObject(px, py)
{
	currentFrame = 1;
	animationSpeed = 0.9;
	accumulatedTime = 0.0f;

	

	shape.setTexture(asset::get().getTexture("fox1"));

}


Player::~Player()
{
}

void Player::update(float deltaTime)
{
	accumulatedTime += deltaTime;

	if (accumulatedTime >= animationSpeed)
	{
		accumulatedTime = 0.0f;
		currentFrame += 1;

		if (currentFrame > FRAMECOUNT)
		{
			currentFrame = 1;
		}

		shape.setTexture(asset::get().getTexture("fox" + std::to_string(currentFrame)));
	}

	if (vx == 0)
	{
		shape.setTexture(asset::get().getTexture("fox7"));
	}

	if (!canJump)
	{
		shape.setTexture(asset::get().getTexture("fox1"));
	}

	
}

void Player::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(shape, states);
}
