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
    vector<string> Autoriz_Menu();  // ������ ���� �����������
    vector<string> Admin_Menu();    // �������������� 
    vector<string> User_Menu();     // ������
    vector<string> Edit_Menu();     // ���� ��������������
    vector<string> Confirm(string massage);     // ���� �������������

    void Print(vector<string> points, int choose);  // ����� ������� ���� � �������
    int Choosing(vector<string> points);    // ���������� ���� ���������
};