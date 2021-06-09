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

void Game::StartGame(Client* client) // �-��� ��������� ���� � �������������, ���� ��� ����������
{
	client->setLevel(level_number);
	client->saveProgress();		// ��������� �������� ������
	if (GameProcessing(client)) // ��������� ���� � ������� ������ �� �������� 
	{
		StartGame(client);	// ��������� ���� ��-����� (��������)
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
	//// ������������� ////
	View view(FloatRect(0, 0, V_WIDTH, V_HIGHT));
	Level lvl;

	changeLevel(lvl, client);  // ��������� ����� �� XML �����

		/// �������� ������� �������� �� ������ ///
	Texture slime_enemy, moveplatform_t, adventurer, bullet_t;
	slime_enemy.loadFromFile("../Platformer/sprites/slime.png");
	moveplatform_t.loadFromFile("../Platformer/sprites/movingPlatform.png");
	adventurer.loadFromFile("../Platformer/sprites/adventurer.png");


	/// ��������� �������� ����� XML ///
	AnimationManager player_anim, slime_anim, moveplatform_anim;
	player_anim.loadFromXML("../Platformer/animations/anim_adventurer.xml", adventurer);
	slime_anim.loadFromXML("../Platformer/animations/slime_anim.xml", slime_enemy);

	/// ���������� ������ ��� 
	Texture bg_t = lvl.getBGTexture();
	Sprite background = lvl.getBackground();
	background.setOrigin(bg_t.getSize().x / 2., bg_t.getSize().y / 2.);

	std::list<Entity*>  entities;	// ������ ��������� ������
	std::list<Entity*>::iterator it;	// �������� �� ������

	std::vector<Object> objects = lvl.getObjectsByName("enemy");	// ������� ������ � ������ ��������
	for (int i = 0; i < objects.size(); i++)
		entities.push_back(new Enemy(slime_anim, lvl, objects[i].rect.left, objects[i].rect.top));

	objects = lvl.getObjectsByName("MovingPlatform");	// �������� ���������� ��������
	for (int i = 0; i < objects.size(); i++)
		entities.push_back(new MovingPlatform(moveplatform_anim, lvl, objects[i].rect.left, objects[i].rect.top));

	Object pl = lvl.getObject("player");	// ����������� ������� ������
	Player Player(player_anim, lvl, pl.rect.left, pl.rect.top);	// ������������� ������ ������ ������
	HealthBar healthBar;	// ���������� ������� ����� ��������
	Clock clock;	// ���������� ��� ����������� �������� ���� �� �������
	Clock game_time_clock;	// ���������� ������������ �������� �������

	//// �������� ����  ////
	while (window->isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();

		/// ����������� ����, ���� ����� �����
		if (Player.Health <= 0)
		{
			if (client->getProgress() <= level_number)
				client->setGameTime(game_time_clock.getElapsedTime().asSeconds());
			client->saveProgress();
			std::cout << " GAME OVER\n";
			window->close();
			return false;
		}

		/// ��������� �� ��������� �������, ���� ����� �����
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

		// ���������� �������� ����
		time = time / 500;
		if (time > 40) time = 40;

		/// ������������ ������� ����
		Event event{};
		while (window->pollEvent(event))
		{
			if (event.type == Event::Closed)
				window->close();

			if (event.type == Event::KeyPressed)
				if (event.key.code == Keyboard::Escape) // ���� Esc, �� ������� �� ���� 
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
				else if (event.key.code == Keyboard::Tab)	// ���� Tab, �� ������������� 
				{
					return true;
				}
		}

		// ��������� ������� ������ 
		KeyboardProcessing(Player);

		/// ���������� ��������� ������ � ����������� �� ��������� ������ 
		getPlayerCoordinateForView(view, Player.getX(), Player.getY());

		/// ���������� ��������� �������� 
		ObjectsUpdate(it, entities, client, Player, healthBar, time);

		// ��������� ����������� � ���������
		InterspectsProcessing(it, entities, Player, time);

		/// ���������� �� ����� ///
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
		
		b->update(time);		// ��������� ���� ��������� �� �����
		if (b->life == false)	// ���� ���� ����, ������� ��� �� �������
		{
			client->setScore(3);	// ��������� ������ ����
			it = entities.erase(it);
			delete b;
		}
		else it++;
	}

	Player.update(time);	// ��������� ������ 
	healthBar.update(Player.Health);	// ��������� ����� ��������
}

void Game::KeyboardProcessing(Player& p)
{
	/// ��������� ������� ������ ///
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
		///	����� ///
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

		/// ���������� ��������� ///
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


void Game::getPlayerCoordinateForView(View& view, float x, float y) // ������� ��� ������������ ���������� ������� ������
{
	float temp_X = x, temp_Y = y,			// ��������� ����� ������ � ��������� ��, ����� ������ ����
		left_border_X = V_WIDTH / 2.,
		right_border_X = 1600 - left_border_X,
		top_border_Y = V_HIGHT / 2.,
		bottom_border_Y = 1280 - top_border_Y;

	if (x < left_border_X) temp_X = left_border_X;			// ������� �� ���� ����� �������
	if (x > right_border_X) temp_X = right_border_X;		// ������ �������
	if (y < top_border_Y) temp_Y = top_border_Y;			// ������� �������
	if (y > bottom_border_Y) temp_Y = bottom_border_Y;		// ������ �������	

	view.setCenter(temp_X, temp_Y);	//������ �� �������, ��������� ��� ����������. 
}