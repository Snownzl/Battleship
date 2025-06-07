/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) [2025] Media Design School
File Name : Board.cpp
Description : GD1P01 Assessment 4 Final Project - Battleship
Author : Brandon Henwood
Mail : Brandon.Henwood@mds.ac.nz
**************************************************************************/

#include "Board.h"
#include "Console.h"
#include <iostream>

// Board constructor, sets all ship pointers to null
Board::Board()
{
    for (int i = 0; i < MAX_SHIPS; ++i)
    {
        ships[i] = nullptr;
    }
    Reset(); 
}

// Board deconstructor, calls reset to clean up memory by deleting ships
// TF: Destructor
Board::~Board()
{
    Reset(); 
}

// Wipes board for new game on call
void Board::Reset() 
{
    // Reset the grid
    for (int row = 0; row < 10; ++row)
        for (int col = 0; col < 10; ++col)
            grid[row][col] = EMPTY;

    // Delete ships
    for (int i = 0; i < MAX_SHIPS; ++i)
    {
        if (ships[i] != nullptr)
        {
            delete ships[i]; 
            ships[i] = nullptr; 
        }
    }
    shipCount = 0;
}

// Display boards
void Board::Print(bool showShips, bool centered) const
{
    // Centering board on console
    std::string padding = centered ? std::string(48, ' ') : "";

    SetRgb(COLOUR_GREEN_ON_BLACK);

    // Column numbers
    std::cout << padding << "   ";
    for (int col = 0; col < 10; ++col)
        std::cout << col << " ";
    std::cout << "\n";

    // Row Letter and state
    for (int row = 0; row < 10; ++row)
    {
        std::cout << padding;
        SetRgb(COLOUR_GREEN_ON_BLACK);
        char rowChar = 'A' + row;
        std::cout << rowChar << "  ";

        for (int col = 0; col < 10; ++col)
        {
            switch (grid[row][col])
            {
            case EMPTY:
                SetRgb(COLOUR_WHITE_ON_BLACK);
                std::cout << ". ";
                break;

            case SHIP:
                if (showShips)
                {
                    SetRgb(COLOUR_CYAN_ON_BLACK);
                    std::cout << "S ";
                }
                else
                {
                    SetRgb(COLOUR_WHITE_ON_BLACK);
                    std::cout << ". ";
                }
                break;

            case HIT:
                SetRgb(COLOUR_RED_ON_BLACK);
                std::cout << "X ";
                break;

            case MISS:
                SetRgb(COLOUR_YELLOW_ON_BLACK);
                std::cout << "O ";
                break;
            }
        }
        std::cout << "\n";
    }

    SetRgb(COLOUR_GREEN_ON_BLACK); // Reset colour after print
}

// For manual ship placement, checking if valid location
bool Board::CanPlaceShip(int row, int col, int size, Orientation orientation) const
{ 
    // Checking each section of chosen ship location
    for (int i = 0; i < size; ++i)
    {
        int r = row + (orientation == VERTICAL ? i : 0);
        int c = col + (orientation == HORIZONTAL ? i : 0);

        // Return false if out of bounds or overlapping another ship
        // TF: Logical Operator
        if (r < 0 || r >= 10 || c < 0 || c >= 10)
            return false;
        if (grid[r][c] != EMPTY)
            return false;
    }
    return true;
}

// Updating chosing ship location in board
bool Board::PlaceShip(int row, int col, int size, const std::string& name, Orientation orientation)
{
    // Return false if all ships already placed or invalid location
    if (shipCount >= MAX_SHIPS)
        return false;
    if (!CanPlaceShip(row, col, size, orientation))
        return false;

    // Mark grid cells
    for (int i = 0; i < size; ++i)
    {
        // TF: Arithmetic Operator
        int r = row + (orientation == VERTICAL ? i : 0);
        int c = col + (orientation == HORIZONTAL ? i : 0); 
        grid[r][c] = SHIP;
    }

    // Double check if existing ship in current slot and delete
    if (ships[shipCount] != nullptr)
    {
        delete ships[shipCount];
    }
    // Create new ship object on the heap and store pointer in array
    // TF: Pointer Initialised
    // TF: Dynamic Memory
    ships[shipCount] = new Ship(row, col, size, name, orientation);
    shipCount++;

    return true;
}

// Randomly place ships on board in valid locations
void Board::PlaceAllShipsRandomly()
{
    // Ship list: name and size
    ShipType ships[5] = {
        { "Carrier", 5 },
        { "Battleship", 4 },
        { "Destroyer", 3 }, 
        { "Submarine", 3 },
        { "Patrol Boat", 2 }
    }; 

    // Randomly choose coordinate with rand until valid spot found for all ships
    // TF: Iteration Structure
    for (int i = 0; i < 5; ++i)
    {
        bool placed = false;
        while (!placed)
        {
            int row = rand() % 10;
            int col = rand() % 10;
            Orientation o = static_cast<Orientation>(rand() % 2);

            placed = PlaceShip(row, col, ships[i].size, ships[i].name, o);
        }
    }
}

// Updates grid after attack and returns from FireResult
FireResult Board::FireAt(int row, int col, std::string& outSunkShipName)
{
    // Check if target within grid bounds
    if (row < 0 || row >= 10 || col < 0 || col >= 10)
        return INVALID;

    // Check if spot already attacked
    if (grid[row][col] == HIT || grid[row][col] == MISS)
        return INVALID; // Already targeted

    // If ship is hit
    if (grid[row][col] == SHIP)
    {
        grid[row][col] = HIT;

        // Check which ship was hit and register hit or sunk status
        for (int i = 0; i < shipCount; ++i)
        { 
            if (ships[i] && ships[i]->OccupiesCell(row, col)) 
            {
                // TF: Pointer Dereferenced
                ships[i]->RegisterHit(); 

                if (ships[i]->IsSunk()) 
                {
                    outSunkShipName = ships[i]->GetName();
                    return SUNK_RESULT;
                }
                else
                    return HIT_RESULT;
            }
        }
        return HIT_RESULT;
    }
    else
    {
        grid[row][col] = MISS;
        return MISS_RESULT;
    }
}

// Check if any ships left for win/loss condition
bool Board::AllShipsSunk() const
{
    for (int row  = 0; row < 10; ++row)
    {
        for (int col = 0; col < 10; ++col)
        {
            // TF: Relational Operator
            if (grid[row][col] == SHIP) 
                return false;
        }
    }
    return true;
}
