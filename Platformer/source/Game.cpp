#include "Game.h"

void Game::changeLevel(Level& lvl, Client* client)
{
	std::string map_file = "../Platformer/maps/Level1.tmx",
		bg_file = "tilesets/BrightDay.png";
	switch (level_number)
	{
	case 1:
	{
		map_file = "../Platformer/maps/Level1.tmx";
		bg_file = "tilesets/BrightDay.png";
	} break;

	case 2:
	{
		map_file = "../Platformer/maps/Level2.tmx";
		bg_file = "tilesets/IceDay.png";
	} break;

	case 3:
	{
		map_file = "../Platformer/maps/Level3.tmx";
		bg_file = "tilesets/BrightDay.png";
	}break;

	case 4:
	{
		map_file = "../Platformer/maps/Level4.tmx";
		bg_file = "tilesets/BrightDay.png";
	} break;

	case 5:
	{
		map_file = "../Platformer/maps/Level5.tmx";
		bg_file = "tilesets/BrightDay.png";
	}break;

	case 6:
	{
		map_file = "../Platformer/maps/Level6.tmx";
		bg_file = "tilesets/BrightDay.png";
	} break;

	case 7:
	{
		map_file = "../Platformer/maps/Level7.tmx";
		bg_file = "tilesets/IceDay.png";
	} break;

	case 8:
	{
		map_file = "../Platformer/maps/Level8.tmx";
		bg_file = "tilesets/BrightDay.png";
	}break;

	case 9:
	{
		map_file = "../Platformer/maps/Level9.tmx";
		bg_file = "tilesets/IceDay.png";
	} break;

	case 10:
	{
		map_file = "../Platformer/maps/Level10.tmx";
		bg_file = "tilesets/BrightDay.png";
	}break;

	default:
		level_number = 1;
		break;
	}
	lvl.LoadFromFile(map_file);
	lvl.setBackground(bg_file);
}

int Game::chooseLevel(Client* client)
{
	int level_choose = 0,
		current_progress = client->getProgress();

	for (int i = 1; i <= current_progress; i++)
	{
		std::cout << " Level " << i << "\n";
	}
	do
	{
		std::cout << "\n Enter level to play: " << "\n";
		std::cin >> level_choose;
		if (level_choose > current_progress)
		{
			std::cout << "\n You have no access to this level! \n"
				<< "\n Please, try again...";
		}
	} while (level_choose > current_progress);
	return level_choose;
}

void Game::StartGame(Client* client) // Ф-ция запускает игру и перезагружает, если это необходимо
{
	client->setLevel(level_number);
	client->saveProgress();		// Сохраняем прогресс игрока
	if (GameProcessing(client)) // Обработка игры и условие выхода из рекурсии 
	{
		StartGame(client);	// Запускает игру по-новой (рекурсия)
	}
}

Game::Game(int level) : level_number(level)
{
	window = new RenderWindow(VideoMode(1024, 608), "Lone in the Field", Style::Default);
}

Game::~Game()
{
	delete window;
}

bool Game::GameProcessing(Client* client)
{
	//// Инициализация ////
	View view(FloatRect(0, 0, V_WIDTH, V_HIGHT));
	Level lvl;

	changeLevel(lvl, client);  // Загружаем карту из XML файла

		/// Загрузка текстур объектов из файлов ///
	Texture slime_enemy, moveplatform_t, adventurer, bullet_t;
	slime_enemy.loadFromFile("../Platformer/sprites/slime.png");
	moveplatform_t.loadFromFile("../Platformer/sprites/movingPlatform.png");
	adventurer.loadFromFile("../Platformer/sprites/adventurer.png");


	/// Загружаем анимации файла XML ///
	AnimationManager player_anim, slime_anim, moveplatform_anim;
	player_anim.loadFromXML("../Platformer/animations/anim_adventurer.xml", adventurer);
	slime_anim.loadFromXML("../Platformer/animations/slime_anim.xml", slime_enemy);

	/// Определяем задний фон 
	Texture bg_t = lvl.getBGTexture();
	Sprite background = lvl.getBackground();
	background.setOrigin(bg_t.getSize().x / 2., bg_t.getSize().y / 2.);

	std::list<Entity*>  entities;	// Список сущностей уровня
	std::list<Entity*>::iterator it;	// Итератор по списку

	std::vector<Object> objects = lvl.getObjectsByName("enemy");	// Загузка врагов в массив объектов
	for (int i = 0; i < objects.size(); i++)
		entities.push_back(new Enemy(slime_anim, lvl, objects[i].rect.left, objects[i].rect.top));

	objects = lvl.getObjectsByName("MovingPlatform");	// Загрузка движущихся платформ
	for (int i = 0; i < objects.size(); i++)
		entities.push_back(new MovingPlatform(moveplatform_anim, lvl, objects[i].rect.left, objects[i].rect.top));

	Object pl = lvl.getObject("player");	// Определение объекта игрока
	Player Player(player_anim, lvl, pl.rect.left, pl.rect.top);	// Инициализация объект класса игрока
	HealthBar healthBar;	// Объявление объекта шкалы здоровья
	Clock clock;	// Переменная для зависимости скорости игры от времени
	Clock game_time_clock;	// Переменная затраченного игрового времени

	//// Основной цикл  ////
	while (window->isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();

		/// Заканчиваем игру, если игрок погиб
		if (Player.Health <= 0)
		{
			if (client->getProgress() <= level_number)
				client->setGameTime(game_time_clock.getElapsedTime().asSeconds());
			client->saveProgress();
			std::cout << " GAME OVER\n";
			window->close();
			return false;
		}

		/// Переходим на следующий уровень, если нашли выход
		if (Player.isExiting())
		{
			if (level_number != 10)
			{

				client->setLevel(++level_number);
				if (client->getProgress() < level_number && client->getProgress() < 10)
				{
					client->increaseProgress();
				}
				if (client->getProgress() <= level_number)
					client->setGameTime(game_time_clock.getElapsedTime().asSeconds());
				client->saveProgress();
				return true;
			}
			else
			{
				client->saveProgress();
				std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n" 
					<< "! Congradulations, you passed it throgh!\n" 
					<< "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
				window->close();
				return false;
			}
		}

		// Регулируем скорость игры
		time = time / 500;
		if (time > 40) time = 40;

		/// Обрабатываем события окна
		Event event{};
		while (window->pollEvent(event))
		{
			if (event.type == Event::Closed)
				window->close();

			if (event.type == Event::KeyPressed)
				if (event.key.code == Keyboard::Escape) // Если Esc, то выходим из игры 
				{
					if (client->getProgress() <= level_number)
						client->setGameTime(game_time_clock.getElapsedTime().asSeconds());
					client->saveProgress();
					window->close();
					return false;
				}
				else if (event.key.code == Keyboard::T)
				{
					level_number++;
					return true;
				}
				else if (event.key.code == Keyboard::Tab)	// Если Tab, то перезагружаем 
				{
					return true;
				}
		}

		// Обработка нажатий клавиш 
		KeyboardProcessing(Player);

		/// Обновление координат камеры в зависимости от положения игрока 
		getPlayerCoordinateForView(view, Player.getX(), Player.getY());

		/// Обновление состояний объектов 
		ObjectsUpdate(it, entities, client, Player, healthBar, time);

		// Обработка пересечения с объектами
		InterspectsProcessing(it, entities, Player, time);

		/// Отображаем на экран ///
		window->setView(view);
		background.setPosition(view.getCenter());
		window->draw(background);
		window->draw(lvl);
		for (it = entities.begin(); it != entities.end(); it++)
			(*it)->draw(*window);
		Player.draw(*window);
		healthBar.draw(*window);
		window->display();
	}
	return 0;
}

void Game::ObjectsUpdate(std::list<Entity*>::iterator& it, std::list<Entity*>& entities, Client* client, Player& Player, HealthBar& healthBar, float time)
{
	for (it = entities.begin(); it != entities.end();)
	{
		Entity* b = *it;
		
		b->update(time);		// Обновляем всех сущностей на карте
		if (b->life == false)	// Если враг убит, убираем его из массива
		{
			client->setScore(3);	// Начисляем игроку очки
			it = entities.erase(it);
			delete b;
		}
		else it++;
	}

	Player.update(time);	// Обновляем игрока 
	healthBar.update(Player.Health);	// Обновляем шкалу здоровья
}

void Game::KeyboardProcessing(Player& p)
{
	/// Обработка нажатий клавиш ///
	if (Keyboard::isKeyPressed(Keyboard::Left)) p.setKey("L", true);
	if (Keyboard::isKeyPressed(Keyboard::Right)) p.setKey("R", true);
	if (Keyboard::isKeyPressed(Keyboard::Up)) p.setKey("Up", true);
	if (Keyboard::isKeyPressed(Keyboard::Down)) p.setKey("Down", true);
	if (Keyboard::isKeyPressed(Keyboard::Space)) p.setKey("Space", true);
}

void Game::InterspectsProcessing(std::list<Entity*>::iterator& it, std::list<Entity*>& entities, Player& Player, float time)
{
	for (it = entities.begin(); it != entities.end(); it++)
	{
		///	Враги ///
		if ((*it)->Name == "Enemy")
		{
			Entity* enemy = *it;
			if (enemy->Health <= 0)
			{
				enemy->dx = 0;
				continue;
			}
			if (Player.getRect().intersects(enemy->getRect()))
				if (Player.dy > 0)
				{
					Player.dy = -0.2;
					enemy->Health = 0;
				}
				else if (!Player.isGettingHit())
				{
					Player.Health -= 25;
					Player.setHit(true);
					if (Player.dir)
						Player.x += 10;
					else
						Player.x -= 10;
				}
		}

		/// Движущиеся платформы ///
		if ((*it)->Name == "MovingPlatform")
		{
			Entity* movPlat = *it;
			if (Player.getRect().intersects(movPlat->getRect()))
				if (Player.dy > 0)
					if (Player.y + Player.h < movPlat->y + movPlat->h)
					{
						Player.y = movPlat->y - Player.h + 3;
						Player.x += movPlat->dx * time;
						Player.dy = 0;
						Player.STATE = Player::stay;
					}
		}
	}
}


void Game::getPlayerCoordinateForView(View& view, float x, float y) // Функция для установления правильной позиции камеры
{
	float temp_X = x, temp_Y = y,			// Считываем коорд игрока и проверяем их, чтобы убрать края
		left_border_X = V_WIDTH / 2.,
		right_border_X = 1600 - left_border_X,
		top_border_Y = V_HIGHT / 2.,
		bottom_border_Y = 1280 - top_border_Y;

	if (x < left_border_X) temp_X = left_border_X;			// Убираем из вида левую сторону
	if (x > right_border_X) temp_X = right_border_X;		// Правую сторону
	if (y < top_border_Y) temp_Y = top_border_Y;			// Верхнюю сторону
	if (y > bottom_border_Y) temp_Y = bottom_border_Y;		// Нижнюю сторону	

	view.setCenter(temp_X, temp_Y);	//следим за игроком, передавая его координаты. 
}