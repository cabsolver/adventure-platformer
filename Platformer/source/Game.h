#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include <sstream>
#include "Client.h"
#include "level.h"
#include "Animation.h"
#include "Entity.h"
#include "Player.h"
#include "Enemy.h"
#include "MovingPlatform.h"
#include "HealthBar.h"
using namespace sf;

class Game
{
	const int V_WIDTH = 400, V_HIGHT = 240;
	int level_number;
	RenderWindow* window;
public:
	Game(int level);
	~Game();

	bool GameProcessing(Client* client);		// Обработка игры
	void changeLevel(Level& lvl, Client* client);	// Смена уровня
	int chooseLevel(Client* client);	// Выбор уровня
	void StartGame(Client* client);		// Запуск игры
	void KeyboardProcessing(Player& p);		// Обработка нажатий на клавиши
	void ObjectsUpdate(std::list<Entity*>::iterator& it, std::list<Entity*>& entities, Client* client, Player& Player, HealthBar& healthBar, float time);	// Обновление объектов на карте
	void InterspectsProcessing(std::list<Entity*>::iterator& it, std::list<Entity*>& entities, Player& Player, float time);		// Обработка пересечений игрока с объектами
	void getPlayerCoordinateForView(View& view, float x, float y);		// Слежение камеры за игроком (недопускает выход камеры за карту)

};