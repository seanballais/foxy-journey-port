#pragma once
#include <SFML\Graphics.hpp>

class physicsObject : public sf::Drawable, public sf::Transformable
{
public:

	float px, py;
	float vx, vy;
	float ax, ay;
	float radius;

	float jumpiness; //:-)

	bool canJump;

	physicsObject(float x, float y);
	
	~physicsObject();
	

	void updateTextures();

	
	virtual void update(float deltaTime) {}

protected:

	sf::Sprite shape;

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	
};
