#include "Client.h"

const std::string Client::FILE_PATH = "../Platformer/saves/Clients.txt";

Client::Client() : login("Non"), password("Non"), role(User)
{
	level = progress = 1;
	id = score = 0;
}

Client::Client(Role role, std::string login, std::string password) : login(login), password(password), role(role)
{
	level = progress = 1;
	id = score = game_time = 0;
}

Client::~Client()
{
}

bool Client::isPassCorrect(Client* verif_client, std::string password)
{
	if (verif_client->password == password)
	{
		return true;
	}
	system("cls");
	std::cout << "Wrong password !"
		<< "\n Please, try again\n";
	return false;
}

void Client::setLevel(int level)
{
	this->level = level;
}

void Client::setScore(int score)
{
	this->score += score;
}

void Client::setGameTime(int time)
{
	this->game_time += time;
}

void Client::increaseProgress()
{
	this->progress += 1;
}

int Client::getLevel()
{
	return this->level;
}

int Client::getClientRole()
{
	return this->role;
}

int Client::getProgress()
{
	return this->progress;
}

Client* Client::logIn()
{
	Client* realClient = nullptr;  // Инициализируем пользователя
	std::string login, password;  // Инициализируем строку логина и пароля

	do
	{
		///  Проверка логина ///
		std::cout << " Enter Login: ";
		std::cin >> login;    // Вводим логин
		realClient = loginExists(login);
		if (realClient == nullptr)
		{
			system("cls");
			std::cout << " ! This Login does not exists !\n"
				<< " Please, try again...\n ";
		}
	} while (realClient == nullptr);

	do
	{
		///  Проверка пароля ///
		std::cout << " Enter Password: ";
		password = inputPass();
	} while (!isPassCorrect(realClient, password));

	return realClient;
}

Client* Client::createClient()
{
	Client* realClient = nullptr;  // Инициализируем пользователя
	std::string login, password;  // Инициализируем строку логина и пароля
		Role new_role{};
	fstream file;
	file.open(FILE_PATH, fstream::in | fstream::out);
	if (!file.is_open())
	{
		std::cout << " Open file error!\n";
	}
	else
	{
		do
		{
			///  Проверка логина на уникальность ///
			std::cout << " Create Login: ";
			std::cin >> login;    // Вводим логин
			realClient = loginExists(login);
			if (realClient != nullptr)
			{
				system("cls");
				std::cout << " ! This Login is already used by another User !\n"
					<< " Please, try again...\n ";
			}
		} while (realClient != nullptr);

		std::cout << " Create Password: ";
		 password = inputPass();

		if (file.peek() == EOF)
			new_role = Admin;
		else
			role = User;
	}
	file.close();
	Client* client = saveClient(new_role, login, password);

	return client;
}

Client* Client::loginExists(std::string login)
{
	Client* realClient = nullptr;
	std::vector<Client*> clients = getAllClients(FILE_PATH);
	std::vector<Client*>::iterator it;
	for (it = clients.begin(); it != clients.end(); it++)
	{
		Client* current_client = *it;
		if (current_client->login == login)
		{
			realClient = current_client;
		}
	}
	return realClient;
}

std::string Client::inputPass()
{
	std::string pass = "";
	do
	{
		char key = _getch();
		if (key != 8 && key != 13)
		{
			pass += key;
			std::cout << "*";
		}
		else
		{
			if (key == 8 && pass.length() > 0)
			{
				pass = pass.substr(0, (pass.length() - 1));
				std::cout << "\b \b";
			}
			else if (key == 13)
			{
				break;
			}
		}
	} while (true);
	return pass;
}

std::vector<Client*> Client::getAllClients(std::string file_path)
{
	std::vector<Client*> clients{};
	std::ifstream fin;
	fin.open(file_path);
	if (!fin.is_open())
	{
		std::cout << " Open file error!\n";
	}
	else
	{
		for (int i = 0; !fin.eof(); i++)
		{
			Client* temp = new Client();
			fin >> temp;
			clients.push_back(temp);
		}
	}
	fin.close();
	return clients;
}

Client* Client::saveClient(Role role, std::string login, std::string password)
{
	// Инициализируем нового пользователя и устанавливаем роль, логин и пароль
	Client* new_client = new Client(role, login, password);

	std::ofstream fout;
	// Открываем поток записи в файл для добавления
	fout.open(FILE_PATH, std::ofstream::app);

	std::vector<Client*> clients = getAllClients(FILE_PATH);

	// Присваиваем новому пользователю ID на один больше чем максимальный среди всех пользователей
	new_client->id = maxId(clients) + 1;

	// Дописываем в файл нового пользователя
	if (!fout.is_open())
	{
		std::cout << "\n Open file error!";
	}
	else
	{
		fout << new_client << "\n";
	}
	fout.close();
	return new_client;
}

int Client::maxId(std::vector<Client*> clients)
{
	int max_id = 0;
	std::vector<Client*>::iterator it;
	for (it = clients.begin(); it != clients.end(); it++)
	{
		Client* current_client = *it;
		if (current_client->id > max_id)
		{
			max_id = current_client->id;
		}
	}
	return max_id;
}

void Client::saveProgress()
{
	std::vector<Client*> clients = getAllClients(FILE_PATH); // Получаем всех пользователей из файла
	std::ofstream fout;
	// Открываем файл на перезапись
	fout.open(FILE_PATH);
	if (!fout.is_open())
	{
		std::cout << "\n Open file error!";
	}
	else
	{
		std::vector<Client*>::iterator it;
		int id = 1;
		// Проходимся по всем пользователям
		for (it = clients.begin(); it != clients.end(); it++, id++)
		{
			Client* current_client = *it;
			if (id == this->id)		// Если совпадение по ID, то записываем новую информацию
			{
				fout << this << "\n";
			}
			else if (current_client->id != 0)	// Переписываем старую
			{
				fout << current_client << "\n";
			}
		}
		std::cout << " Save success!" << "\n";
	}
	fout.close();
}

void Client::viewStats()
{
	std::vector<Client*> clients = getAllClients(FILE_PATH);
	if (this->role == 0)	// Если игрок, то показываем только его статистику
	{
		std::cout << "Current Level " << "\tProgress  " << "Score" << "\tGame Time\n";
		std::cout << clients[id - 1]->level << "\t\t  " << clients[id - 1]->progress
			<< "\t  " << clients[id - 1]->score << "\t " << clients[id - 1]->game_time << "\n";
	}
	else	// Иначе весь список 
	{
		std::vector<Client*>::iterator it;
		std::cout << "Id" << "\tLogin" << "\t\tRole" << "\tCurrent Level " << "\tProgress  " << "Score" << "\tGame Time\n";
		for (it = clients.begin(); it != clients.end(); it++, id++)
		{
			Client* current_client = *it;
			if (current_client->id != 0)
			{
				std::cout << current_client->id << "\t" << current_client->login
					<< "\t\t " << current_client->role << "\t " << current_client->level
					<< "\t\t " << current_client->progress << "\t  " << current_client->score << "\t " << current_client->game_time << "\n";
			}
		}
	}
}

void Client::viewHiScoreTable()
{
	std::vector<Client*> clients = getAllClients(FILE_PATH);
	std::vector<Client*>::iterator it;
	std::cout << "Player" << "\tProgress  " << "Score" << "\tGame Time\n";
	for (it = clients.begin(); it != clients.end(); it++)
	{
		Client* current_client = *it;
		if (current_client->id != 0)
		{
			std::cout << current_client->login << "\t " << current_client->progress
				<< "\t  " << current_client->score << "\t " << current_client->game_time << "\n";
		}
	}
}

void Client::editUser(int id)
{
	std::vector<Client*> clients = getAllClients(FILE_PATH);
	Interface* edit_menu = new Interface();
	int choose = 0;
	string info;
	do
	{
		choose = edit_menu->Choosing(edit_menu->Edit_Menu());
		if (choose == 2 && choose != 6)
		{
			cout << " Enter Role (0 - User, 1 - Admin): ";
			cin >> info;
		}
		else if (choose != 6)
		{
			cout << " Enter information: ";
			cin >> info;
		}
		switch (choose)
		{
		case 0:
		{
			if (atoi(info.c_str()) > 0)
				clients[id - 1]->id = atoi(info.c_str());
			else
				cout << "\n Wrong info"
				<< "\n Please, try again... \n";
		} break;

		case 1: clients[id - 1]->login = info; break;

		case 2:
		{
			if (atoi(info.c_str()) == 0)
				clients[id - 1]->role = Role::User;
			else if (atoi(info.c_str()) == 1)
				clients[id - 1]->role = Role::Admin;
			else
				cout << "\n Wrong info"
				<< "\n Please, try again... \n";
		} break;

		case 3:
		{
			if (atoi(info.c_str()) > 0 && atoi(info.c_str()) <= 10)
				clients[id - 1]->level = atoi(info.c_str());
			else
				cout << "\n Wrong info"
				<< "\n Please, try again... \n";
		} break;

		case 4:
		{

			if (atoi(info.c_str()) > 0 && atoi(info.c_str()) <= 10)
				clients[id - 1]->progress = atoi(info.c_str());
			else
				cout << "\n Wrong info"
				<< "\n Please, try again... \n";
		} break;

		case 5:
		{

			if (atoi(info.c_str()) > 0)
				clients[id - 1]->score = atoi(info.c_str());
			else
				cout << "\n Wrong info"
				<< "\n Please, try again... \n";
		} break;

		case 6:
		{

			if (atoi(info.c_str()) > 0)
				clients[id - 1]->game_time = atoi(info.c_str());
			else
				cout << "\n Wrong info"
				<< "\n Please, try again... \n";
		} break;

		case 7: cout << " Going back...\n";  break;
		}
	} while (choose != 6);
	if (!edit_menu->Choosing(edit_menu->Confirm("Save changes?")))
		clients[id - 1]->saveProgress();
	delete edit_menu;
}

void Client::deleteUser(int id)
{
	Interface* edit_menu = new Interface();
	std::vector<Client*> clients = getAllClients(FILE_PATH); // Получаем всех пользователей из файла
	if (this->id != id && !edit_menu->Choosing(edit_menu->Confirm("Save changes?")))	// Получаем разрешение от пользователя
	{
		// Открываем файл на перезапись
		std::ofstream fout;
		fout.open(FILE_PATH);
		if (!fout.is_open())
		{
			std::cout << "\n Open file error!";
		}
		else	// Перезаписываем всю информацию без пользователя под нужным ID
		{
			std::vector<Client*>::iterator it;
			for (it = clients.begin(); it != clients.end(); it++)
			{
				Client* current_client = *it;
				if (current_client->id != 0 && current_client->id != id)
				{
					fout << current_client << "\n";
				}
			}
			std::cout << " Delete success!" << "\n";
		}
		fout.close();
	}
	else if (this->id == id)		// Невозможно удалить свою учетную запись
	{
		std::cout << " You can't delete yourself!\n";
	}
	delete edit_menu;
}

std::ostream& operator<< (std::ostream& os, const Client* client)
{
	os << client->id << " " << client->login << " " << client->password << " "
		<< client->role << " " << client->level << " " << client->progress << " "
		<< client->score << " " << client->game_time;
	return os;
}

std::istream& operator>> (std::istream& is, Client* client)
{
	int role = 0;
	is >> client->id >> client->login >> client->password >> role
		>> client->level >> client->progress >> client->score >> client->game_time;

	if (role == 0) client->role = Client::User;
	else client->role = Client::Admin;
	return is;
}