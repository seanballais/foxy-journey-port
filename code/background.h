#pragma once

#include <deque>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Camera.h"


class background : public sf::Drawable, public sf::Transformable
{
public:
	background(std::string TxtName);
	virtual void update(Camera & pCamera,float deltaTime,int marginY);

	
	~background();

protected:

	sf::Sprite shape;

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

