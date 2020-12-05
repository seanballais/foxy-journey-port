#include "physicObject.h"

physicsObject::physicsObject(float x, float y)
{

	px = x;
	py = y;

	vx = vy = 0.0f;
	ax = ay = 0.0f;

	canJump = false;

	jumpiness = 80.0f;

	radius = 40;

}

physicsObject::~physicsObject()
{

}
void physicsObject::updateTextures()
{
	

	shape.setPosition(px - 2 * radius, py -  3.5 * radius);
}

void physicsObject::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	target.draw(shape, states);
}


