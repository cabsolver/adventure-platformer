#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <SFML/Graphics.hpp>
using namespace std;

class Interface
{
public:
    vector<string> Autoriz_Menu();  // Пункты меню авторизации
    vector<string> Admin_Menu();    // Администратора 
    vector<string> User_Menu();     // Игрока
    vector<string> Edit_Menu();     // Меню редактирования
    vector<string> Confirm(string massage);     // Меню подтверждения

    void Print(vector<string> points, int choose);  // Вывод пунктов меню в консоль
    int Choosing(vector<string> points);    // Управление меню стрелками
};