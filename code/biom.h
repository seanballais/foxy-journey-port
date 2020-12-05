#pragma once
#include<SFML\Graphics.hpp>
#include<vector>

#include "background.h"

enum Bioms
{
	HILLS = 1,
	MOUNTAINS = 2,
	BAMBOO = 3
};

class biom : public sf::Drawable, public sf::Transformable
{
public:
	biom(std::string pTexture = "",std::string biomName = "");
	~biom();

	virtual void update(Camera & pCamera, float deltaTime, int marginY);

	void reset();

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

protected:
	std::vector<background *> layers;

	int vertexCount;

public:
	std::string biomId;
};

