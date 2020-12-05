#include "./Assets.h"



#include <fstream>

std::map<std::string, std::string> asset::variables;



bool asset::loadTexture(std::string path, std::string id)
{
	if (!m_textures[id].loadFromFile(path)) { std::cerr << "[ERROR] Cannot load texture " << path << std::endl; return false; }
	return true;
}

bool asset::loadFont(std::string path, std::string id)
{
	if (!m_fonts[id].loadFromFile(path)) { std::cerr << "[ERROR] Cannot load font " << path << std::endl; return false; }
	return true;
}

bool asset::loadSoundEffect(std::string path, std::string id)
{
	if (!m_sounds[id].loadFromFile(path)) { std::cerr << "[ERROR] Cannot load sound " << path << std::endl; return false; }
	return true;
}


sf::Texture & asset::getTexture(std::string id)
{
	if (m_textures.find(id) == m_textures.end())
	{
		loadTexture(asset::variables["$TEXTURES"] + id + ".png",id);
	}
	return  m_textures[id];
}

sf::Font & asset::getFont(std::string id)
{
	if (m_fonts.find(id) == m_fonts.end())
	{
		loadFont(asset::variables["$FONTS"] + id + ".ttf",id);
	}
	return m_fonts[id];
}

sf::SoundBuffer & asset::getSoundEffect(std::string id)
{
	if (m_sounds.find(id) == m_sounds.end())
	{
		loadFont(asset::variables["$SOUNDS"] + id + ".ogg", id);
	}
	return m_sounds[id];
}


void asset::loadVariables(std::string path)
{
	std::ifstream input;

	input.open(path);

	if (input.is_open())
	{
		std::string buffer;

		while (input >> buffer)
		{
			std::string key = buffer;

			input >> buffer;

			asset::variables[key] = buffer;
		}
	}
}