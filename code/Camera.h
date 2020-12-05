#pragma once

#include <SFML/Graphics.hpp>

const int MARGIN = 16;

const float GRAVITY = 45.0f;

const int OBSTACLES_ON_SCREEN_X = 8;

const int CHUNK_SIZE = 4; //size of terrain chunk(screen width as unit)

const int WINDOW_WIDTH = 1152;

struct Camera
{
	int windowHeight;
	int windowWidth;

	const sf::View * view;

	std::string biom;

};
