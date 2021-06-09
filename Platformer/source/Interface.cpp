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
    /// ���������� �� ���� ������� ���� � ������� ���� "<<", ���� ��������� ����� ������������� ������ ���� 
    for (vector<string>::iterator it = points.begin(); it != points.end(); it++, i++) 
        cout << points[i] << (i == choose ? " <<" : "");
}

int Interface::Choosing(vector<string> points)
{
    int choose = 0;     // ���������� ������ ������ ����
    char key = 0;       // ����������-����� ��� �������� �������� �������
    while (true)
    {
        system("cls");
        Print(points, choose);  // ������������ ������ ����
        key = _getch();         // ���� ������� �������
        switch (key)
        {
        case 72: choose--; break;    // ���� ������� �����, ��������� ����������-�����
        case 80: choose++; break;    // ������� ����� - �����������
        case 13: system("cls"); return choose;      // ������� ����� - ���������� ���������� �����
        }
        choose = (choose + points.size()) % points.size();  // ������ ����������-����� � ������ ���-�� ������� ����
    }
}
