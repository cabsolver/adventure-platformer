#include "Interface.h"

vector<string> Interface::Autoriz_Menu()
{
    vector<string> points = {
        "  \t----- Autorization -----\n\t 1. Log In",
        "\n\t 2. Registration",
        "\n\t    Exit" };
    return points;
}

vector<string> Interface::Admin_Menu()
{
    vector<string> points = {
        "  \t-------- Admin --------\n\t 1. View User's info",
        "\n\t 2. Edit User",
        "\n\t 3. Delete User",
        "\n\t  Back" };
    return points;
}

vector<string> Interface::User_Menu()
{
    vector<string> points = {
        "  \t-------- User --------\n\t 1. Start game",
        "\n\t 2. Choose level",
        "\n\t 3. View my statistics",
        "\n\t 4. View high score table",
        "\n\t  Back" };
    return points;
}

vector<string> Interface::Edit_Menu()
{
    vector<string> points = {
        "  \t-------- User --------\n\t 1. ID",
        "\n\t 2. Login",
        "\n\t 3. Role",
        "\n\t 4. Level",
        "\n\t 5. Progress",
        "\n\t 6. Score",
        "\n\t  Back" };
    return points;
}

vector<string> Interface::Confirm(string massage)
{
    vector<string> points = { "\t" + massage + "\n" +
        "\n\t  Yes",
        "\n\t  No" };
    return points;
}

void Interface::Print(vector<string> points, int choose)
{
    int i = 0;
    /// Проходимся по всем пунктам меню и выводим знак "<<", если выбранный пункт соответствует пункту меню 
    for (vector<string>::iterator it = points.begin(); it != points.end(); it++, i++) 
        cout << points[i] << (i == choose ? " <<" : "");
}

int Interface::Choosing(vector<string> points)
{
    int choose = 0;     // Переменная выбора пункта меню
    char key = 0;       // Переменная-буфер для хранения нажатого символа
    while (true)
    {
        system("cls");
        Print(points, choose);  // Отрисовываем пункты меню
        key = _getch();         // Ждем нажатия клавиши
        switch (key)
        {
        case 72: choose--; break;    // Если стрелка вверх, уменьшаем переменную-выбор
        case 80: choose++; break;    // Стрелка вверх - увеличиваем
        case 13: system("cls"); return choose;      // Клавиша ввода - возвращаем полученный выбор
        }
        choose = (choose + points.size()) % points.size();  // Держим переменную-выбор в рамках кол-ва пунктов меню
    }
}
