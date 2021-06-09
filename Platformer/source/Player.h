#pragma once
#include "Entity.h"

class Player : public Entity
{
	std::map<std::string, bool> key;
	bool onLadder, hit, onExit;
	enum { stay, walk, duck, jump, climb } STATE;	// ���� ������������ ��������� ������ 

public:

	Player(AnimationManager& a, Level& lvl, int x, int y);

	void setKey(std::string name, bool value);	// ��������� ��������� ������
	void setHit(bool value);	// �������������, �������� �� ����� ����
	bool isGettingHit();		// ����������, �������� �� ����� ����
	bool isExiting();	// ����������, ����� �� ����� ������� �� ��������� �������

	void Keyboard();	// ������ ��������� ������ � ����������� �� ������� 
	void Animation(float time);	// ������ �������� � ����������� �� ���������
	void update(float time);	// ��������� ������
	void Collision(int num);	// ��������� ������������ � ������

	friend class Game;
};