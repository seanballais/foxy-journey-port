#pragma once
#include "physicObject.h"

#include <SFML/Graphics.hpp>

class obstacle :  public sf::CircleShape
{
public:
	obstacle(float x, float y,float pRadius,std::string textureName,float pSlowDown);
	~obstacle();

	float px, py;

	float radius;

	float slowDown;

};

