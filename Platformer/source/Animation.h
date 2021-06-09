#pragma once
#include "TinyXML/tinyxml.h"
#include <SFML/Graphics.hpp>

using namespace sf;

class Animation
{
	bool loop, flip, playing;   // loop ��������� ��������� �� ��������
	float currentFrame, speed;
	std::vector<IntRect> frames, frames_flip;
	Sprite sprite;

public:
	Animation();
	void tick(float time);

	// ��������� ��������
	void setSpeed(float speed_value);
	void setLoop(bool loop_value);
	void setFlip(bool flip_value);
	void setPlaying(bool isPlaying);
	void setFrames(int x, int y, int w, int h, int step, int i);
	void setFramesFlip(int x, int y, int w, int h, int step, int i);
	void setSpriteTexture(Texture& texture);
	void setSpriteOrigin(int h);
	void setSpritePosition(int x, int y);

	// ��������� �����
	bool isLooped();
	bool isFliped();
	bool isPlaying();
	float getSpeed();
	std::vector<IntRect> getFrames();
	std::vector<IntRect> getFramesFlip();
	Sprite getSprite();

};



class AnimationManager
{
	std::string currentAnim;
	std::map<std::string, Animation> animList;

public:
	AnimationManager();
	~AnimationManager();
	void create(std::string name, Texture& texture, int x, int y, int w, int h, int count, float speed, int step = 0, bool Loop = true); // �������� �������� �������
	void loadFromXML(std::string fileName, Texture& t);		// �������� �������� �� ����� XML
	void set(std::string name);		// ��������� ������� ��������
	void draw(RenderWindow& window, int x, int y);	// ������������ � ���� 
	void flip(bool b = true);	// �������������� �������� (� ����������� �� ����������� ��������)
	void tick(float time);		// ����� ��������
	void pause();	// ��������� �������� 
	void loop(bool);	// ������������ ��������
	void play();	// ������������ ������� ��������
	void play(std::string name);	// ������������ ������������
	bool isPlaying();	// ����������, ������������� �� ��������
	float getH();
	float getW();

};