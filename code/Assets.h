#pragma once
#include <map>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


class asset
{
public:
	asset() { asset::loadVariables("./config/paths.conf"); }
	asset(asset & a){}
	asset & operator=(asset & a){}
	static asset & get() { static asset assets; return assets; }
	~asset() {}
	
	 sf::Texture & getTexture(std::string id);
	 sf::Font & getFont(std::string id);
	 sf::SoundBuffer & getSoundEffect(std::string id);
	
	bool loadMap(std::string path, std::string Id);
	bool loadTexture(std::string path, std::string id);
	bool loadFont(std::string path, std::string id);
	bool loadSoundEffect(std::string path, std::string id);
	

	static void loadVariables(std::string path);

	static std::map<std::string, std::string> variables;

private:
	std::map<std::string,sf::Texture> m_textures;
	std::map<std::string, sf::Font> m_fonts;
	std::map<std::string, sf::SoundBuffer> m_sounds;


};