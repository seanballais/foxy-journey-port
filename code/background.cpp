#include "background.h"
#include "noiseGenerator.h"
#include "Assets.h"



background::background(std::string TxtName)
{
	

	shape.setTexture(asset::get().getTexture(TxtName));


}

void background::update(Camera & pCamera, float deltaTime, int MarginY)
{

}



background::~background()
{
	
}

void background::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	target.draw(shape, states);
	
}
