#pragma once
#include "TinyXML/tinyxml.h"
#include <SFML/Graphics.hpp>

using namespace sf;

class Animation
{
	bool loop, flip, playing;   // loop показвает зациклена ли анимация
	float currentFrame, speed;
	std::vector<IntRect> frames, frames_flip;
	Sprite sprite;

public:
	Animation();
	void tick(float time);

	// Установка значений
	void setSpeed(float speed_value);
	void setLoop(bool loop_value);
	void setFlip(bool flip_value);
	void setPlaying(bool isPlaying);
	void setFrames(int x, int y, int w, int h, int step, int i);
	void setFramesFlip(int x, int y, int w, int h, int step, int i);
	void setSpriteTexture(Texture& texture);
	void setSpriteOrigin(int h);
	void setSpritePosition(int x, int y);

	// Получение полей
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
	void create(std::string name, Texture& texture, int x, int y, int w, int h, int count, float speed, int step = 0, bool Loop = true); // Создание анимации вручную
	void loadFromXML(std::string fileName, Texture& t);		// Загрузка анимации из файла XML
	void set(std::string name);		// Установка текущей анимации
	void draw(RenderWindow& window, int x, int y);	// Отрисовываем в окне 
	void flip(bool b = true);	// Переворачиваем анимацию (в зависимости от направления движения)
	void tick(float time);		// Смена анимаций
	void pause();	// Остановка анимации 
	void loop(bool);	// Зацикливание анимации
	void play();	// Проигрывание текущей анимации
	void play(std::string name);	// Проигрывание определенной
	bool isPlaying();	// Определяем, проигрывается ли анимация
	float getH();
	float getW();

};