/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) [2025] Media Design School
File Name : Ship.h
Description : GD1P01 Assessment 4 Final Project - Battleship
Author : Brandon Henwood
Mail : Brandon.Henwood@mds.ac.nz
**************************************************************************/

#pragma once
#include <string>

// Ship orientation for manual placement
enum Orientation
{
    HORIZONTAL,
    VERTICAL
};

// Used for each ship on board
// TF: Class
class Ship
{
public:
    Ship(int row, int col, int size, const std::string& name, Orientation orientation);

    // Returns size of the ship (number of cells it occupies)
    int GetSize() const;
    // Returns true if the ship has taken a hit for each number of cells it occupies
    bool IsSunk() const; 
    // Returns true if ship occupies the targeted cell
    bool OccupiesCell(int row, int col) const;
    // Returns the type name of the ship
    std::string GetName() const;
    // Adds one hit to the ship
    void RegisterHit();

// TF: Access Specifier
private:
    int size;
    int hitsTaken; 
    int startRow;
    int startCol;

    std::string name;

    Orientation orientation;
};
