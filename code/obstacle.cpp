#include "obstacle.h"
#include "Assets.h"


obstacle::obstacle(float x, float y,float pRadius, std::string textureName,float pSlowDown) 
{
	px = x;
	py = y;
	radius = pRadius;

	slowDown = pSlowDown;

	setPosition(x, y);
	setRadius(radius);

	//setFillColor(sf::Color::Red);
	setTexture(&asset::get().getTexture(textureName));
}


obstacle::~obstacle()
{
}
