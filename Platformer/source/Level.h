#pragma once
#include <SFML/Graphics.hpp>
#include "TinyXML/tinyxml2.h"
#include <iostream>
#include <cctype>
class Object
{
	std::string name;
	std::string type;
	std::map<std::string, std::string> properties;
	sf::FloatRect rect;
public:

	Object(float x, float y, float width, float height) : rect(x, y, width, height)
	{}
	
	int GetPropertyInt(const std::string& name);
	float GetPropertyFloat(const std::string& name);
	std::string GetPropertyString(const std::string& name);
	friend class Level;
	friend class Player;
	friend class Enemy;
	friend class Game;
};

class Level : public sf::Drawable
{
	sf::Texture bg_texture;
	sf::Sprite background;
	sf::Texture* texture;
	std::vector<sf::VertexArray> tile_layers;
	std::vector<Object> objects;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	Level();
	~Level();

	void setBackground(std::string image);
	sf::Sprite getBackground();
	sf::Texture getBGTexture();

	Object getObject(const std::string& name);
	std::vector<Object>  getObjectsByName(const std::string& name);
	std::vector<Object>  getObjectsByType(const std::string& type);
	std::vector<Object>& getAllObjects();

	bool LoadFromFile(const std::string& tmx_file_path);
};