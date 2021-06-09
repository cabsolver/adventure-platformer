#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <conio.h>
#include "Interface.h"

class Client 
{
	static const std::string FILE_PATH;		// Путь к файлу с информацией о пользователях
	std::string login, password;
	int id, level, progress, score, game_time;
	enum Role {User, Admin} role;

public:
	Client();
	Client(Role role, std::string login, std::string password);
	~Client();

	void setGameTime(int time);	// Установка времени прохождения
	void setScore(int score);	// Установка очков
	void setLevel(int level);	// Установка уровня 
	void increaseProgress();	// Увеличение прогресса на одну единицу

	int getLevel();			// Получение текущего уровня пользователя
	int getClientRole();	// Получение роли пользователя (возвращает 0 - User или 1 - Admin)
	int getProgress();		// Получение текущего прогресса

	static std::vector<Client*> getAllClients(std::string file_path);	// Получение всех пользователей из файла
	static int maxId(std::vector<Client*> clients);						// Поиск максимального ID среди пользователей 
	static Client* loginExists(std::string login);						// Проверка логина на существование
	static bool isPassCorrect(Client* verif_client, std::string password);	// Проверка пароля на совпадение
	static std::string inputPass();										// Возвращает пароль замаскированный под '*'

	Client* logIn();														// Авторизация
	Client* createClient();										// Создание нового пользователя 
	Client* saveClient(Role role, std::string login, std::string password);	// Сохранение пользователя в файл
	void saveProgress();	// Сохранение прогресса пользователя
	void viewStats();		// Вывод информации пользователей на экран консоли
	void viewHiScoreTable();
	void editUser(int id);		// Редактирование пользователя
	void deleteUser(int id);

	friend std::ostream& operator<< (std::ostream& os, const Client* client);	// Перегрузка оператора для работы класса с потоком записи/вывода 
	friend std::istream& operator>> (std::istream& is, Client* client);			// Перегрузка оператора для работы класса с потоком чтения/ввода 
};