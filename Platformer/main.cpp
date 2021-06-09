#include "source/Game.h"
#include "source/Interface.h"
#include <iostream>

int main()
{
	Interface* menu = new Interface();	// ��������� ������ ����
	while(true)
	{
		Client* client = nullptr;	// ��������� ������ ������������
		int choose = 0;		// ��������� ���������� ������ ������� ����
		/// ��������� ���� �����������/�����������
		do
		{
			choose = menu->Choosing(menu->Autoriz_Menu());
			switch (choose)
			{
				/// ��������������
			case 0:
			{
				system("cls");
				client = (new Client())->logIn();
			} break;

			/// ������������ ������ ������������
			case 1:
			{
				system("cls");
				(new Client())->createClient();
				system("cls");
				std::cout << "\n\t ! Registration success !\n";
			} break;

			/// ������� �� ���������
			case 2:
			{
				system("cls");
				std::cout << " Exiting...";
				delete menu;
				return 0;
			} break;
			}
		} while (client == nullptr);

		/// ���������� ����������� ������������ � ������������ � ����� ///
		if (client->getClientRole() == 0)
		{
			// �������������� ������ ���� 
			Game* game = nullptr;
			int level = client->getProgress();
			do
			{
				system("cls");
				choose = menu->Choosing(menu->User_Menu());
				switch (choose)
				{
					/// ���� ����� Start game, �� ��������� ����
				case 0:
				{
					system("cls");
					std::cout << "\n Game starts !\n";
					/// ������ ����
					game = new Game(level);
					game->StartGame(client);
					system("pause");
				} break;

				/// ����� ���������� �������
				case 1:
				{
					system("cls");
					level = game->chooseLevel(client);
				}break;

				/// ������������� ���������� ������
				case 2:
				{
					system("cls");
					client->viewStats();
					system("pause");
				} break;

				/// ������������� ������� ��������
				case 3:
				{
					system("cls");
					client->viewHiScoreTable();
					system("pause");
				} break;

				/// ������������ �����
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
					/// ������������� ���������� ���� �������������
				case 0:
				{
					system("cls");
					client->viewStats();
					system("pause");
				} break;

				/// ����������� ����������
				case 1:
				{
					system("cls");
					int id = 0;
					cout << " Enter the ID of the User to edit: ";
					cin >> id;
					client->editUser(id);

				} break;

				/// ������� ������������ 
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

				/// ������� � ���� �����������
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