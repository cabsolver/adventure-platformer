#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Animation.h"
#include "Level.h"
using namespace sf;

class Entity
{
	double x, y, dx, dy, w, h, timer, timer_end;
	AnimationManager anim;
	std::vector<Object> obj;
	bool life, dir;
	std::string Name;
	int Health;
public:

	Entity(AnimationManager& A, int X, int Y);

	virtual void update(float time) = 0;	// ����� ����������� ������� ���������� ��������

	void draw(RenderWindow& window);	// ��������� �������� � ����
	void option(std::string NAME, float SPEED = 0, int HEALTH = 10, std::string FIRST_ANIM = "");  // ��������� ������������� ��������

	// ��������� �������� �����
	void setX(float value);
	void setY(float value);
	void setDx(float value);
	void setDy(float value);
	void setWidht(float value);
	void setHight(float value);

	// ��������� ����� ������
	FloatRect getRect();
	float getX();
	float getY();
	float getDx();
	float getDy();
	float getWidth();
	float getHight();

	// ������������� ������
	friend class Enemy;
	friend class Player;
	friend class MovingPlatform;
	friend class Game;
};