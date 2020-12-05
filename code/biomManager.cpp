#include "biomManager.h"


biomManager::biomManager(physicsObject * pPlayer)
{

	int idx = rand() % 3 + 1;

	switch (idx)
	{
	case HILLS:
		biomsToDraw.push_back(new biom("hills_start", "hills"));
		biomsToDraw.push_back(new biom("hills", "hills"));
		biomsToDraw.push_back(new biom("hills_end", "hills"));
		break;
	case MOUNTAINS:
		biomsToDraw.push_back(new biom("mountains_start", "mountains"));
		biomsToDraw.push_back(new biom("mountains", "mountains"));
		biomsToDraw.push_back(new biom("mountains_end", "mountains"));
		break;
	case BAMBOO:
		biomsToDraw.push_back(new biom("bamboo_start", "bamboo"));
		biomsToDraw.push_back(new biom("bamboo", "bamboo"));
		biomsToDraw.push_back(new biom("bamboo_end", "bamboo"));
		break;
	}

	

	player = pPlayer;
}


biomManager::~biomManager()
{
	for (auto & b : biomsToDraw)
	{
		delete b;
	}
}

void biomManager::update(Camera & pCamera, float deltaTime, int marginY)
{

	if (!biomsToDraw.empty())
	{
		biomsToDraw.front()->setPosition(getPosition());

		
		
		accumulatedOffset += player->vx * deltaTime * 0.25f;

		float moveValue = accumulatedOffset;

			if (moveValue >= WINDOW_WIDTH)
			{
			
				accumulatedOffset = 0.0f;

				delete biomsToDraw.front();
				biomsToDraw.pop_front();

				if (!biomsToDraw.empty())
				{
					biomsToDraw.front()->setPosition(getPosition());
				}
				
			}
			else
			{
				biomsToDraw.front()->move(moveValue * -1, 0);
			}

		
		if(biomsToDraw.size() > 1)
		for (size_t i = 1; i < biomsToDraw.size(); i++)
		{
			biomsToDraw[i]->setPosition(biomsToDraw[i - 1]->getPosition() + sf::Vector2f(WINDOW_WIDTH, 0));
		}

		if (biomsToDraw.size() == 1)
		{
			int index = rand() % 3 + 1;

			addBiom(index);
		}

	}
}

void biomManager::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (auto & b : biomsToDraw)
	{
		target.draw(*b, states);
	}
}

void biomManager::addBiom(int biomId)
{
	
	if(!biomsToDraw.empty())
	//biomsToDraw.push_back(new biom(biomsToDraw.front()->biomId + "_end",biomsToDraw.front()->biomId));

	switch (biomId)
	{
		case HILLS:
			biomsToDraw.push_back(new biom("hills_start","hills"));
			biomsToDraw.push_back(new biom("hills","hills"));
			biomsToDraw.push_back(new biom("hills_end", "hills"));
			break;

		case MOUNTAINS:
			biomsToDraw.push_back(new biom("mountains_start","mountains"));
			biomsToDraw.push_back(new biom("mountains","mountains"));
			biomsToDraw.push_back(new biom("mountains_end", "mountains"));
			break;

		case BAMBOO:
			biomsToDraw.push_back(new biom("bamboo_start", "bamboo"));
			biomsToDraw.push_back(new biom("bamboo", "bamboo"));
			biomsToDraw.push_back(new biom("bamboo_end", "bamboo"));
			break;
	}
}
