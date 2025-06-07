/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) [2025] Media Design School
File Name : Console.cpp
Description : GD1P01 Assessment 4 Final Project - Battleship
Author : Brandon Henwood
Mail : Brandon.Henwood@mds.ac.nz
**************************************************************************/

#include "Console.h"
#include <iostream>
#include <cctype>

// Set console colour
void SetRgb(EColour colour) {
    switch (colour) {
    case COLOUR_WHITE_ON_BLACK:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        break;
    case COLOUR_RED_ON_BLACK:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
        break;
    case COLOUR_GREEN_ON_BLACK:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
        break;
    case COLOUR_YELLOW_ON_BLACK:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
        break;
    case COLOUR_BLUE_ON_BLACK:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
        break;
    case COLOUR_MAGENTA_ON_BLACK:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
        break;
    case COLOUR_CYAN_ON_BLACK:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
        break;
    default:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        break;
    }
}

// Clears the console screen
void ClearScreen()
{
    COORD coordScreen = { 0, 0 };
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD dwConSize;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    GetConsoleScreenBufferInfo(hConsole, &csbi);
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

    FillConsoleOutputCharacter(hConsole, TEXT(' '), dwConSize, coordScreen, &cCharsWritten);
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
    SetConsoleCursorPosition(hConsole, coordScreen);
}

// Center text in console
void displayCentered(const std::string& text)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int consoleWidth = 80; // fallback width

    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) 
        consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;

    int padding = (consoleWidth - static_cast<int>(text.length())) / 2; 
    if (padding > 0) std::cout << std::string(padding, ' ');
    std::cout << text;
}

// Validates, converts, and processes input for player turn attack targeting
bool CoordinateInput(const std::string& input, int& outRow, int& outCol)
{
    // Must be 2 characters
    if (input.length() != 2)
        return false;

    // First character must be A-J
    char rowChar = toupper(input[0]);
    if (rowChar < 'A' || rowChar > 'J')
        return false;

    // Second character must be 0-9
    char colChar = input[1];
    if (!isdigit(colChar))
        return false;

    // Convert letter
    int col = colChar - '0';

    // Convert digit
    outRow = rowChar - 'A';
    outCol = col;
    return true;
}
