#pragma once
#include "Entity.h"

class Enemy : public Entity
{
public:
	Enemy(AnimationManager& a, Level& lev, int x, int y) : Entity(a, x, y)
	{
		float enemy_speed = ((rand() % 5) + 1) / static_cast<float>(100);
		int health = 15;
		option("Enemy", enemy_speed, health, "move");
		obj = lev.getAllObjects();
	}

	void update(float time)		// Обновление состояния врага
	{
		dy += 0.0005 * time;
		
		x += dx * time;		// Координата положения
		Collision(0);

		y += dy * time;
		Collision(1);

		timer += time;		// Таймер движения
		if (timer > 5000)	// Если больше, меняется направление врага
		{ 
			dx *= -1;	
			timer = rand() % 4000;;	// Таймер обнуляется
		}

		if (Health <= 0)	// Если здоровье врага на нуле
		{
			anim.set("dead");	// Проигрываем анимацию смерти 
			anim.loop(false);	// Останавливаем воспроизведение
			dx = 0;
			timer_end += time;
			if (timer_end > 6000) 
				life = false;	// Объявляем конец жизни врага
		}
		anim.tick(time);
	}

	void Collision(int num)
	{
		for (int i = 0; i < obj.size(); i++)
			if (getRect().intersects(obj[i].rect))
			{
				if (obj[i].name == "solid")
				{
					if (dy > 0 && num == 1) { y = obj[i].rect.top - h; dy = 0;}
					if (dy < 0 && num == 1) { y = obj[i].rect.top + obj[i].rect.height; dy = 0; }
					if (dx > 0 && num == 0) { x = obj[i].rect.left - w; }
					if (dx < 0 && num == 0) { x = obj[i].rect.left + obj[i].rect.width; }
				}

				if (obj[i].name == "SlopeLeft")
				{
					FloatRect r = obj[i].rect;
					int y0 = (x + w / 2 - r.left) * r.height / r.width + r.top - h;
					if (y > y0)
						if (x + w / 2 > r.left)
						{
							y = y0; dy = 0;
						}
				}

				if (obj[i].name == "SlopeRight")
				{
					FloatRect r = obj[i].rect;
					int y0 = -(x + w / 2 - r.left) * r.height / r.width + r.top + r.height - h;
					if (y > y0)
						if (x + w / 2 < r.left + r.width)
						{
							y = y0; dy = 0;
						}
				}

			}
	}
};