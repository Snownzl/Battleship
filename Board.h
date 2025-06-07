/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) [2025] Media Design School
File Name : Board.h
Description : GD1P01 Assessment 4 Final Project - Battleship
Author : Brandon Henwood
Mail : Brandon.Henwood@mds.ac.nz
**************************************************************************/

#pragma once
#include "Ship.h"
#include <cstdlib> // For rand
#include <ctime>   // For seeding rand
#include <string>

// States of each cell in grid
enum CellState
{
    EMPTY,
    SHIP,
    HIT,
    MISS
};

// Result of player/computer attacks
enum FireResult
{
    INVALID,
    MISS_RESULT,
    HIT_RESULT,
    SUNK_RESULT
};

// Contains size and names of the 5 ships
struct ShipType {
    std::string name;
    int size;
};

// Used for player or enemy game board related logic, e.g. ship placement, tracking attacks
class Board
{
public:
	Board();
	~Board();

    // Checks if player chose a valid ship placement location
    bool CanPlaceShip(int row, int col, int size, Orientation orientation) const;
    // Updates board with ship placed manually
    bool PlaceShip(int row, int col, int size, const std::string& name, Orientation orientation);
    // Used for checking win/loss state
    bool AllShipsSunk() const; 
    // Wipes board for new game
    void Reset();
    // Prints individual boards
    // TF: Default Parameter
    void Print(bool showShips = false, bool centered = false) const;
    // For ship placement - random option
    void PlaceAllShipsRandomly();
    // Updates grid after attack and returns from FireResult
    FireResult FireAt(int row, int col, std::string& outSunkShipName);

private:
    int shipCount;
    // TF: Constant
    static const int MAX_SHIPS = 5;

    // Array of ship pointers, stores and tracks ship state (number of hits, sunk)
    Ship* ships[MAX_SHIPS];
    // Array for game board tracking from CellState enum
    // TF: Array
    CellState grid[10][10];
};
