/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) [2025] Media Design School
File Name : Console.h
Description : GD1P01 Assessment 4 Final Project - Battleship
Author : Brandon Henwood
Mail : Brandon.Henwood@mds.ac.nz
**************************************************************************/

#pragma once
#include <windows.h>
#include <string>

// colour console options
enum EColour {
    COLOUR_WHITE_ON_BLACK = 0,
    COLOUR_RED_ON_BLACK = 1,
    COLOUR_GREEN_ON_BLACK = 2,
    COLOUR_YELLOW_ON_BLACK = 3,
    COLOUR_BLUE_ON_BLACK = 4,
    COLOUR_MAGENTA_ON_BLACK = 5,
    COLOUR_CYAN_ON_BLACK = 6,
};

// Change current console colour
void SetRgb(EColour colour);

// Clears the console screen
void ClearScreen(); 

// Center text in console
void DisplayCentered(const std::string& text);

// Validates, converts, and processes input for player turn attack targeting
// TF: Reference
bool CoordinateInput(const std::string& input, int& row, int& col);
