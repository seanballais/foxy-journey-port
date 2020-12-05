#include "terrain.h"
#include "noiseGenerator.h"



terrain::terrain(int pVertexCount,sf::Color pColor)
{
	
	vertexCount = pVertexCount + MARGIN;

	//srand(time(NULL));

	verticies.setPrimitiveType(sf::Quads);

	verticies.resize( 4 * (vertexCount));

	for (int i = 0; i < vertexCount * 4; i++)
	{
		verticies[i].color = pColor;
	}


	srand(time(NULL));

	for (int i = 0; i < vertexCount; i++)
	{
		seed.push_back((float)rand() / (float)RAND_MAX);

		obstacles.push_back(nullptr);
	}

	generateObstacles = true;

	generateNoise(seed, terrainVerticies, 8, 2);


	obstacleGeneration = 0.5;

	obstacleGenTime = 0.0f;

}

void terrain::update(Camera & pCamera, float deltaTime, int MarginY)
{

	obstacleGenTime += deltaTime;

	float posX = getPosition().x;

	float xStep = (float)pCamera.windowWidth / (vertexCount - MARGIN);

	float cameraX = pCamera.view->getCenter().x - (pCamera.view->getSize().x / 2.0f);

	if (cameraX - posX >= xStep)
	{
		

		for (int i = 0; i < (cameraX - posX) / xStep; i++)
		{

			float val = terrainVerticies.front();
			terrainVerticies.pop_front();
			terrainVerticies.push_back(val);

			
			delete obstacles.front();

			obstacles.pop_front();
			obstacles.push_back(nullptr);
		}


		if (obstacleGenTime >= obstacleGeneration && generateObstacles)
		{
			obstacleGenTime = 0.0f;
			
			
				if (((float)rand() / (float)RAND_MAX) > 0.79)
				{
					
					float ObstacleRadius = pCamera.windowWidth / (OBSTACLES_ON_SCREEN_X * 2) - 15;

					obstacles.back() = new obstacle(0, 0, ObstacleRadius, "obstacle_" + pCamera.biom, -25);

				}

			
		}

		this->move(cameraX - posX, 0);

	}


	for (int i = 0; i < vertexCount - 1; i++)
	{
		
		sf::Vertex * Quad = &verticies[i * 4];

		Quad[0].position = sf::Vector2f(i * xStep, terrainVerticies[i] * 100 + MarginY);
		Quad[1].position = sf::Vector2f((i + 1) * xStep, terrainVerticies[i + 1] * 100 + MarginY);
		Quad[2].position = sf::Vector2f((i + 1) * xStep, pCamera.windowHeight);
		Quad[3].position = sf::Vector2f(i * xStep, pCamera.windowHeight);
	}

	for (int i = 0; i < vertexCount; i++)
	{
		if (obstacles[i] != nullptr)
		{


			float buffX = i * xStep;

			float buffY = terrainVerticies[i] * 100 + MarginY;

			obstacles[i]->px = buffX;
			obstacles[i]->py = buffY;

			obstacles[i]->setPosition(buffX - obstacles[i]->getRadius(), buffY - obstacles[i]->getRadius());


		}
	}


}



terrain::~terrain()
{
	for (auto & o : obstacles)
	{
		delete o;
	}
}

void terrain::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	for (auto & o : obstacles)
	{
		if (o != nullptr)
		{
			target.draw(*o, states);
		}
	}

	target.draw(verticies, states);
	
}
