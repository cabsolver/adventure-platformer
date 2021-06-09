#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <conio.h>
#include "Interface.h"

class Client 
{
	static const std::string FILE_PATH;		// ���� � ����� � ����������� � �������������
	std::string login, password;
	int id, level, progress, score, game_time;
	enum Role {User, Admin} role;

public:
	Client();
	Client(Role role, std::string login, std::string password);
	~Client();

	void setGameTime(int time);	// ��������� ������� �����������
	void setScore(int score);	// ��������� �����
	void setLevel(int level);	// ��������� ������ 
	void increaseProgress();	// ���������� ��������� �� ���� �������

	int getLevel();			// ��������� �������� ������ ������������
	int getClientRole();	// ��������� ���� ������������ (���������� 0 - User ��� 1 - Admin)
	int getProgress();		// ��������� �������� ���������

	static std::vector<Client*> getAllClients(std::string file_path);	// ��������� ���� ������������� �� �����
	static int maxId(std::vector<Client*> clients);						// ����� ������������� ID ����� ������������� 
	static Client* loginExists(std::string login);						// �������� ������ �� �������������
	static bool isPassCorrect(Client* verif_client, std::string password);	// �������� ������ �� ����������
	static std::string inputPass();										// ���������� ������ ��������������� ��� '*'

	Client* logIn();														// �����������
	Client* createClient();										// �������� ������ ������������ 
	Client* saveClient(Role role, std::string login, std::string password);	// ���������� ������������ � ����
	void saveProgress();	// ���������� ��������� ������������
	void viewStats();		// ����� ���������� ������������� �� ����� �������
	void viewHiScoreTable();
	void editUser(int id);		// �������������� ������������
	void deleteUser(int id);

	friend std::ostream& operator<< (std::ostream& os, const Client* client);	// ���������� ��������� ��� ������ ������ � ������� ������/������ 
	friend std::istream& operator>> (std::istream& is, Client* client);			// ���������� ��������� ��� ������ ������ � ������� ������/����� 
};