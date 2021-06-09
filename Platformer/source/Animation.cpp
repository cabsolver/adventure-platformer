#include "Animation.h"

Animation::Animation()
{
	currentFrame = 0;
	playing = true;
	flip = false;
	loop = true;
}

void Animation::tick(float time)
{
	if (!playing) return;

	currentFrame += speed * time;	// ��������� ���� (����� ������� �� ������� � ��������)

	if (currentFrame > frames.size()) // ���� ����� �� ��������� ���� ��������
	{
		currentFrame -= frames.size(); // ������������ � �������
		if (!loop)	// �������� �� ��������� - ������������� 
		{
			playing = false;
			return;
		}
	}

	int i = currentFrame;
	sprite.setTextureRect(frames[i]);	// ������������� �������� �� ����
	if (flip)
		sprite.setTextureRect(frames_flip[i]);
}

void Animation::setSpeed(float speed_value) { this->speed = speed_value; }

void Animation::setLoop(bool loop_value) { this->loop = loop_value; }

void Animation::setFlip(bool flip_value) { this->flip = flip_value; }

void Animation::setPlaying(bool isPlaying) { this->playing = isPlaying; }

void Animation::setFrames(int x, int y, int w, int h, int step, int i) { this->frames.push_back(IntRect(x + i * step, y, w, h)); }

void Animation::setFramesFlip(int x, int y, int w, int h, int step, int i) { this->frames_flip.push_back(IntRect(x + i * step + w, y, -w, h)); }

void Animation::setSpriteTexture(Texture& texture) { this->sprite.setTexture(texture); }

void Animation::setSpriteOrigin(int h) { this->sprite.setOrigin(0, h); }

void Animation::setSpritePosition(int x, int y) { this->sprite.setPosition(x, y); }

bool Animation::isLooped() { return loop; }

bool Animation::isFliped() { return flip; }

bool Animation::isPlaying() { return playing; }

float Animation::getSpeed() { return speed; }

std::vector<IntRect> Animation::getFrames() { return frames; }

std::vector<IntRect> Animation::getFramesFlip() { return frames_flip; }

Sprite Animation::getSprite() { return sprite; }


AnimationManager::AnimationManager()
{}

AnimationManager::~AnimationManager()
{
	animList.clear();
}

// �������� �������� �������
void AnimationManager::create(std::string name, Texture& texture, int x, int y, int w, int h, int count, float speed, int step, bool Loop)
{
	Animation a;
	a.setSpeed(speed);
	a.setLoop(Loop);
	a.setSpriteTexture(texture);
	a.setSpriteOrigin(h);

	for (int i = 0; i < count; i++)
	{
		a.setFrames(x, y, w, h, step, i);
		a.setFramesFlip(x, y, w, h, step, i);
	}
	animList[name] = a;
	currentAnim = name;
}

//�������� �� ����� XML
void AnimationManager::loadFromXML(std::string fileName, Texture& t)
{
	TiXmlDocument animFile(fileName.c_str());	// �������������� �������� XML

	animFile.LoadFile();	// ��������� ����

	TiXmlElement* head;
	head = animFile.FirstChildElement("sprites");	// ��������� � ������ ��������

	TiXmlElement* animElement;
	animElement = head->FirstChildElement("animation");	// ��������� � ������ ��������
	while (animElement)
	{
		Animation anim;
		currentAnim = animElement->Attribute("title");	// �������� ��������
		int delay = atoi(animElement->Attribute("delay"));	// �������� �������� ���������������
		anim.setSpeed(1.0 / delay);		// ������������� �������� 
		anim.setSpriteTexture(t);	// ������������� ��������

		TiXmlElement* cut;
		cut = animElement->FirstChildElement("cut");	// ��������� � ������� ������� ����� 
		while (cut)
		{
			// �������� ����� 
			int x = atoi(cut->Attribute("x"));
			int y = atoi(cut->Attribute("y"));
			int w = atoi(cut->Attribute("w"));
			int h = atoi(cut->Attribute("h"));

			anim.setFrames(x, y, w, h, 0, 0);	// ��������� ������ 
			anim.setFramesFlip(x, y, w, h, 0, 0);	// � ���������� ����
			cut = cut->NextSiblingElement("cut");	// ��������� � ���������� �����
		}

		anim.setSpriteOrigin(anim.getFrames()[0].height);	// ��������� ��������

		animList[currentAnim] = anim;	// ����������� �������� �� �� ��������� � ������
		animElement = animElement->NextSiblingElement("animation"); // ��������� � ��������� ��������
	}
}

void AnimationManager::set(std::string name)
{
	currentAnim = name;
	animList[currentAnim].setFlip(0);
}

void AnimationManager::draw(RenderWindow& window, int x = 0, int y = 0)
{
	animList[currentAnim].setSpritePosition(x, y);
	window.draw(animList[currentAnim].getSprite());
}

void AnimationManager::flip(bool b) { animList[currentAnim].setFlip(b); }

void AnimationManager::tick(float time) { animList[currentAnim].tick(time); }

void AnimationManager::pause() { animList[currentAnim].setPlaying(false); }

void AnimationManager::loop(bool isLooped) { animList[currentAnim].setLoop(isLooped); }

void AnimationManager::play() { animList[currentAnim].setPlaying(true); }

void AnimationManager::play(std::string name) { animList[name].setPlaying(true); }

bool AnimationManager::isPlaying() { return animList[currentAnim].isPlaying(); }

float AnimationManager::getH() { return animList[currentAnim].getFrames()[0].height; }

float AnimationManager::getW() { return animList[currentAnim].getFrames()[0].width; }