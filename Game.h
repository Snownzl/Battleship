/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) [2025] Media Design School
File Name : Game.h
Description : GD1P01 Assessment 4 Final Project - Battleship
Author : Brandon Henwood
Mail : Brandon.Henwood@mds.ac.nz
**************************************************************************/

#pragma once
#include "Board.h"

// Manages main menu, gameplay loop, manual ship placement, player and computer turns
class Game
{
public: 
    // Initial loop with main menu
    void Run();
    void ComputerTurn();
    // Battleship game loop
    void PlayGame();
    // Prints current board layout to screen every call
    void DrawAllBoards();
    void ShowInstructions();

private:
    // Player and computer boards used for placing ships, tracking and displaying shots
    Board playerBoard;
    Board enemyBoard;

    // Game over screen stats
    // TF: Variable Type
    int playerShots = 0;
    int playerHits = 0;
    int playerMisses = 0;
    int playerShipsSunk = 0;
    int aiShots = 0;
    int aiHits = 0; 
    int aiMisses = 0; 
    int aiShipsSunk = 0;
    // Displays computer boards when true
    bool debugMode = false;
    // Used to skip computer turn after player launches nuke or surrenders
    bool playerSurrendered = false;
    bool nukeLaunched = false;

    time_t gameStartTime = 0;

    // Enter manual ship placement mode
    void ManualShipPlacement(Board& board);
    // enter game over screen to show game summary before returning to main menu
    void gameOverScreen(bool playerWon);
};
