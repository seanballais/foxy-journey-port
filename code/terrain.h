#pragma once

#include<deque>
#include<vector>

#include <SFML/Graphics.hpp>

#include "Camera.h"
#include "obstacle.h"


class terrain : public sf::Drawable, public sf::Transformable
{
public:
	terrain(int pVertexCount,sf::Color pColor);
	virtual void update(Camera & pCamera,float deltaTime,int marginY);

	std::deque<float> terrainVerticies;

	std::deque<obstacle * > obstacles;

	std::deque<float> seed;


	int vertexCount;

	bool generateObstacles;

	~terrain();

protected:

	sf::VertexArray verticies;


	

	float obstacleGeneration;

	float obstacleGenTime;


private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

