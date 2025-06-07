/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) [2025] Media Design School
File Name : Ship.cpp
Description : GD1P01 Assessment 4 Final Project - Battleship
Author : Brandon Henwood
Mail : Brandon.Henwood@mds.ac.nz
**************************************************************************/

#include "Ship.h"

// Ship constructor, sets the ships size, position, name, and orientation
// TF: Constructor
Ship::Ship(int row, int col, int size, const std::string& name, Orientation orientation)
{
    startRow = row;
    startCol = col;
    this->size = size;
    this->name = name;
    this->orientation = orientation;
    hitsTaken = 0;
}

// Returns size of the ship (number of cells it occupies)
int Ship::GetSize() const
{
    return size;
}

// Returns the type name of the ship
std::string Ship::GetName() const
{
    return name;
}

// Adds one hit to the ship
void Ship::RegisterHit()
{
    hitsTaken++;
}

// Returns true if the ship has taken a hit for each number of cells it occupies
bool Ship::IsSunk() const
{
    return hitsTaken >=size;
}

// Returns true if ship occupies the targeted cell
bool Ship::OccupiesCell(int row, int col) const
{
    if (orientation == HORIZONTAL)
        return row == startRow && col >= startCol && col < startCol + size;
    else
        return col == startCol && row >= startRow && row < startRow + size;
}
