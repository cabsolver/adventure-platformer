#pragma once
#include "Entity.h"

class Player : public Entity
{
	std::map<std::string, bool> key;
	bool onLadder, hit, onExit;
	enum { stay, walk, duck, jump, climb } STATE;	// Поле перечисления состояний игрока 

public:

	Player(AnimationManager& a, Level& lvl, int x, int y);

	void setKey(std::string name, bool value);	// Установка состояний клавиш
	void setHit(bool value);	// Устанавливаем, получает ли игрок урон
	bool isGettingHit();		// Определяем, получает ли игрок урон
	bool isExiting();	// Определяем, нашел ли игрок переход на следующий уровень

	void Keyboard();	// Меняем состояния игрока в зависимости от нажатий 
	void Animation(float time);	// Меняем анимации в зависимости от состояний
	void update(float time);	// Обновляем игрока
	void Collision(int num);	// Обработка столкновений с картой

	friend class Game;
};