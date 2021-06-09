#include "source/Game.h"
#include "source/Interface.h"
#include <iostream>

int main()
{
	Interface* menu = new Interface();	// Объявляем объект меню
	while(true)
	{
		Client* client = nullptr;	// Объявляем объект пользователя
		int choose = 0;		// Объявляем переменную выбора пунктов меню
		/// Реализуем меню авторизации/регистрации
		do
		{
			choose = menu->Choosing(menu->Autoriz_Menu());
			switch (choose)
			{
				/// Авторизируемся
			case 0:
			{
				system("cls");
				client = (new Client())->logIn();
			} break;

			/// Регистрируем нового пользователя
			case 1:
			{
				system("cls");
				(new Client())->createClient();
				system("cls");
				std::cout << "\n\t ! Registration success !\n";
			} break;

			/// Выходим из программы
			case 2:
			{
				system("cls");
				std::cout << " Exiting...";
				delete menu;
				return 0;
			} break;
			}
		} while (client == nullptr);

		/// Определяем возможности пользователя в соответствии с ролью ///
		if (client->getClientRole() == 0)
		{
			// Инициализируем объект игры 
			Game* game = nullptr;
			int level = client->getProgress();
			do
			{
				system("cls");
				choose = menu->Choosing(menu->User_Menu());
				switch (choose)
				{
					/// Если выбор Start game, то запускаем игру
				case 0:
				{
					system("cls");
					std::cout << "\n Game starts !\n";
					/// Запуск игры
					game = new Game(level);
					game->StartGame(client);
					system("pause");
				} break;

				/// Выбор пройденных уровней
				case 1:
				{
					system("cls");
					level = game->chooseLevel(client);
				}break;

				/// Просматриваем статистику игрока
				case 2:
				{
					system("cls");
					client->viewStats();
					system("pause");
				} break;

				/// Просматриваем таблицу рекордов
				case 3:
				{
					system("cls");
					client->viewHiScoreTable();
					system("pause");
				} break;

				/// Возвращаемся назад
				case 4:
				{
					system("cls");
					std::cout << " Going back...\n";
				} break;
				}
			} while (choose != 4);
			delete game;
		}
		else if (client->getClientRole() == 1)
		{
			do
			{
				system("cls");
				choose = menu->Choosing(menu->Admin_Menu());
				switch (choose)
				{
					/// Просматриваем информацию всех пользователей
				case 0:
				{
					system("cls");
					client->viewStats();
					system("pause");
				} break;

				/// Редактируем информацию
				case 1:
				{
					system("cls");
					int id = 0;
					cout << " Enter the ID of the User to edit: ";
					cin >> id;
					client->editUser(id);

				} break;

				/// Удаляем пользователя 
				case 2:
				{
					system("cls");
					int id = 0;
					cout << " Enter the ID of the User to delete: ";
					cin >> id;
					if (id > 0)
						client->deleteUser(id);
					else
						cout << " Wrong ID!\n";
					system("pause");
				}break;

				/// Выходим в меню авторизации
				case 3:
				{
					system("cls");
					std::cout << " Going back...\n";
				} break;
				}
			} while (choose != 3);
		}
		delete client;
	}
}