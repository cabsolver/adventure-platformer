#include "Entity.h"

Entity::Entity(AnimationManager& A, int X, int Y)
{
	anim = A;
	x = X;
	y = Y;
	dir = 0;

	life = true;
	timer = 0;
	timer_end = 0;
	dx = dy = 0;
}

void Entity::draw(RenderWindow& window)
{
	anim.draw(window, x, y + h);
}

FloatRect Entity::getRect()		// Получение размера 
{
	return FloatRect(x, y, w, h);
}

void Entity::option(std::string NAME, float SPEED, int HEALTH, std::string FIRST_ANIM)	// Характеристики сущности
{
	Name = NAME;
	if (FIRST_ANIM != "") anim.set(FIRST_ANIM);
	w = anim.getW();
	h = anim.getH();
	dx = SPEED;
	Health = HEALTH;
}

// Установка значений полей

void Entity::setX(float value) { x = value; }

void Entity::setY(float value) { y = value; }

void Entity::setDx(float value) { dx = value; }

void Entity::setDy(float value) { dy = value; }

void Entity::setWidht(float value) { w = value; }

void Entity::setHight(float value) { h = value; }

// Получение полей класса

float Entity::getX() { return x; }

float Entity::getY() { return y; }

float Entity::getDx() { return dx; }

float Entity::getDy() { return dx; }

float Entity::getWidth() { return w; }

float Entity::getHight() { return h; }
