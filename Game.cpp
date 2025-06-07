/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) [2025] Media Design School
File Name : Game.cpp
Description : GD1P01 Assessment 4 Final Project - Battleship
Author : Brandon Henwood
Mail : Brandon.Henwood@mds.ac.nz
**************************************************************************/

#include "Game.h"
#include "Console.h"
#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <windows.h>

// Main menu
void Game::Run()
{
    int menuChoice = 0;
    std::string input;
    // Seeding random number generator, used for random ship placement and player/AI shot targeting
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // Loop main menu until quit
    do
    {
        ClearScreen();
        SetRgb(COLOUR_BLUE_ON_BLACK);
        std::cout << R"(             /$$$$$$$   /$$$$$$  /$$$$$$$$ /$$$$$$$$ /$$       /$$$$$$$$  /$$$$$$  /$$   /$$ /$$$$$$ /$$$$$$$ 
            | $$__  $$ /$$__  $$|__  $$__/|__  $$__/| $$      | $$_____/ /$$__  $$| $$  | $$|_  $$_/| $$__  $$
            | $$  \ $$| $$  \ $$   | $$      | $$   | $$      | $$      | $$  \__/| $$  | $$  | $$  | $$  \ $$
            | $$$$$$$ | $$$$$$$$   | $$      | $$   | $$      | $$$$$   |  $$$$$$ | $$$$$$$$  | $$  | $$$$$$$/
            | $$__  $$| $$__  $$   | $$      | $$   | $$      | $$__/    \____  $$| $$__  $$  | $$  | $$____/ 
            | $$  \ $$| $$  | $$   | $$      | $$   | $$      | $$       /$$  \ $$| $$  | $$  | $$  | $$      
            | $$$$$$$/| $$  | $$   | $$      | $$   | $$$$$$$$| $$$$$$$$|  $$$$$$/| $$  | $$ /$$$$$$| $$      
            |_______/ |__/  |__/   |__/      |__/   |________/|________/ \______/ |__/  |__/|______/|__/      
        )";
        SetRgb(COLOUR_CYAN_ON_BLACK);
        std::cout << R"(
                                                             |__
                                                             |\/
                                                             ---
                                                             / | [
                                                      !      | |||
                                                    _/|     _/|-++'
                                                +  +--|    |--|--|_ |-
                                             { /|__|  |/\__|  |--- |||__/
                                            +---------------___[}-_===_.'____               /\
                                        ____`-' ||___-{]_| _[}-  |     |_[___\==--          \/   _
                         __..._____--==/___]_|__|_____________________________[___\==--___,-----' .7
                        |           By Brandon Henwood, for Media Design School, 2025        BB-61/
~~~~~~~~~~~~~~~~~~~~~~~~\_______________________________________________________________________|~~~~~~~~~~~~~~~~~~~~~~)" << "\n\n";
        SetRgb(COLOUR_GREEN_ON_BLACK);
        displayCentered("1. Start New Game\n");
        displayCentered("2. View Instructions\n");
        displayCentered("3. Toggle Debug Mode: (" + std::string(debugMode ? "ON" : "OFF") + ")\n");
        displayCentered("4. Quit\n");
        displayCentered("Enter your choice (1-4): ");

        std::string input;
        std::getline(std::cin, input);

        if (input.empty())
        {
            // If no input
            displayCentered("No input received. Please enter a number between 1 and 4");
            Sleep(2000);
            continue;
        }

        // Checking for invalid input
        std::istringstream iss(input);
        if (!(iss >> menuChoice) || menuChoice < 1 || menuChoice > 4)
        {
            displayCentered("Invalid input. Please enter a number between 1 and 4");
            Sleep(2000);
            continue;
        }

        switch (menuChoice)
        {
        case 1:
            PlayGame();
            break;
        case 2:
            ShowInstructions();
            break;
        case 3:
            debugMode = !debugMode;
            break;
        case 4:
            displayCentered("Exiting game\n");
            break;
        }

    } while (menuChoice != 4);
}

// Game Loop
void Game::PlayGame()
{
    ClearScreen();

    // Resetting game over screen variables each new game
    playerShots = 0;
    playerHits = 0;
    playerMisses = 0;
    playerShipsSunk = 0;
    aiShots = 0;
    aiHits = 0;
    aiMisses = 0;
    aiShipsSunk = 0;

    // Recording time played since game start
    gameStartTime = time(0);

    playerSurrendered = false;
    nukeLaunched = false;

    // Wiping boards in case of second playthrough
    playerBoard.Reset();
    enemyBoard.Reset();

    std::string input;
    std::string dummy;
    bool validChoice = false;
    bool gameOver = false;

    //Loop until valid placement method chosen
    while (!validChoice)
    {
        ClearScreen();

        std::cout << "Choose the ship placement method\n";
        std::cout << "m for Manual placement\n";
        std::cout << "r for Random placement\n";
        std::cout << "Enter your choice: ";
        std::getline(std::cin, input);

        if (input.empty())
        {
            std::cout << "No input received. Please enter 'r' or 'm'";
            Sleep(2000);
            continue;
        }

        // TF: Conditional Statement
        if (input == "m")
        {
            ClearScreen();
            ManualShipPlacement(playerBoard);
            validChoice = true;
        }
        else if (input == "r")
        {
            playerBoard.PlaceAllShipsRandomly();
            ClearScreen();
            validChoice = true;
        }
        else
        {
            std::cout << "Invalid choice. Please enter 'r' or 'm'";
            Sleep(2000);
        }
    }

    // Enemy ships are now placed randomly on their board
    enemyBoard.PlaceAllShipsRandomly();
    DrawAllBoards();

    // Main gameplay loop: player and computer take turns until game ends
    while (true)
    {
        int row, col;
        bool validShot = false;
        std::string input;
        FireResult result;

        // Loop until valid target selected
        while (!validShot)
        {
            std::cout << "----- Player Turn -----\n";
            std::cout << "Enter a target coordinate (e.g. D5), 'r' for a random target, or 'surrender' to quit: ";
            std::getline(std::cin, input);

            // If input empty
            if (input.empty())
            {
                std::cout << "No input received. Please enter a valid command or coordinate.";
                Sleep(2000);
                ClearScreen();
                DrawAllBoards();
                continue;
            }

            // Nuke is auto win for testing
            if (input == "nuke")
            {
                enemyBoard.Reset();
                playerShipsSunk = 5;
                playerHits += 17;
                playerShots++;
                nukeLaunched = true;
                ClearScreen();
                DrawAllBoards();
                std::cout << "!!!!! NUKE LAUNCHED !!!!!\n";
                std::cout << "You win, but at what cost\n";
                std::cout << "Press enter to continue";
                std::getline(std::cin, dummy);
                break;
            }
            
            // Surrender is auto loss for testing but mainly functions as a quit game
            else if (input == "surrender")
            {
                aiShipsSunk = 5;
                aiHits += 17;
                aiShots++;
                playerSurrendered = true;
                ClearScreen();
                DrawAllBoards();
                std::cout << "YOU SURRENDERED .....\n";
                std::cout << "You lose, the enemy sunk all your ships anyway\n";
                std::cout << "Press enter to continue";
                std::getline(std::cin, dummy);
                break; // skip to game over
            }

            std::string sunkShip;

            // Random shots
            if (input == "r")
            {
                // Loop until valid target
                do {
                    // TF: Pseudo Random Number
                    row = rand() % 10;
                    col = rand() % 10;
                    result = enemyBoard.FireAt(row, col, sunkShip);
                } while (result == INVALID);

                // Display coordinates of random shot
                std::cout << "Random shot fired at " << static_cast<char>('A' + row) << col;
            }

            // Manual targeting update grid and display using fireat and fireresult in Board
            else if (CoordinateInput(input, row, col))
            {
                result = enemyBoard.FireAt(row, col, sunkShip);
            }

            else
            {
                std::cout << "Invalid input format";
                Sleep(2000);
                ClearScreen();
                DrawAllBoards();
                continue;
            }
            ClearScreen();
            DrawAllBoards();
            //Using Fireresult enum
            switch (result)
            {
            case HIT_RESULT:
            {
                std::cout << "----- Player Turn -----\n";
                std::cout << "You hit a ship!\n";
                playerShots++;
                playerHits++;
                std::cout << "Press enter to continue";
                std::getline(std::cin, dummy);
                validShot = true;
                break;
            }

            case MISS_RESULT:
            {
                std::cout << "----- Player Turn -----\n";
                std::cout << "You missed\n";
                playerShots++;
                playerMisses++;
                std::cout << "Press enter to continue";
                std::getline(std::cin, dummy);
                validShot = true;
                break;
            }

            case SUNK_RESULT:
            {
                std::cout << "----- Player Turn -----\n";
                std::cout << "You sunk the enemy's " << sunkShip << "!\n";
                playerShots++;
                playerShipsSunk++;
                std::cout << "Press enter to continue";
                std::getline(std::cin, dummy);
                validShot = true;
                break;
            }

            case INVALID:
            {
                std::cout << "----- Player Turn -----\n";
                std::cout << "Invalid input. That coordinate has already been targeted";
                Sleep(2000);
                ClearScreen();
                DrawAllBoards();
                break;
            }

            default:
                std::cout << "Uh Oh";
                break;
            }

            // Loop back if already targeted coordinate
            if (result == INVALID)
                continue;

            ClearScreen();
            DrawAllBoards();

            // Check win condition: all enemy ships sunk
            if (enemyBoard.AllShipsSunk())
            {
                ClearScreen();
                DrawAllBoards();
                std::cout << "********** VICTORY! **********\n";
                std::cout << "Congratulations! You sank all enemy ships. Well done!\n";
                Sleep(1000);
                std::cout << "Press enter to continue";
                std::getline(std::cin, dummy);
                gameOver = true;
                break;
            }

            // Computer takes random shot
            ComputerTurn();

            // Check loss condition: all player ships sunk
            if (playerBoard.AllShipsSunk())
            {
                ClearScreen();
                DrawAllBoards();
                std::cout << "DEFEAT.....\n";
                std::cout << "You lose. All your ships have been sunk\n";
                Sleep(1000);
                std::cout << "Press enter to continue";
                std::getline(std::cin, dummy);
                gameOver = true;
                break;
            }
        }
        // Break loop if player used nuke or surrendered
        if (playerSurrendered || nukeLaunched || gameOver)
        {
            break;
        }
        ClearScreen();
        DrawAllBoards();
    }
    // Show win/loss screen and game over stats
    gameOverScreen(enemyBoard.AllShipsSunk());
}

// Computer turn
void Game::ComputerTurn()
{
    int row, col;
    std::string sunkShip;
    std::string dummy;
    FireResult result =INVALID;

    // Loop until valid target is selected
    do
    {
        row = rand() % 10;
        col = rand() % 10;
        result = playerBoard.FireAt(row, col, sunkShip);
    } while (result == INVALID);

    // Convert from number to corresponding board letter for displaying coordinate result
    char rowChar = 'A' + row;

    ClearScreen();
    DrawAllBoards();

    std::cout << "----- Computer Turn -----\n";
    // Display coordinates of computer attack
    std::cout << "Enemy fired at " << rowChar << col << ": ";

    // Process result of computer attack with FireAt method
    switch (result)
    {
    case HIT_RESULT:
        std::cout << "Hit!\n";
        aiShots++;
        aiHits++;
        break;  
    case MISS_RESULT:
        std::cout << "Miss\n"; 
        aiShots++;
        aiMisses++;  
        break;
    case SUNK_RESULT:
        std::cout << "Sunk your " << sunkShip << "!\n";
        aiShots++;
        aiHits++;
        aiShipsSunk++;
        break;
    default:
        std::cout << "Oh no\n";
        break;
    }
    std::cout << "Press enter to continue";
    std::getline(std::cin, dummy);
}

// Display player boards and ships, if debug mode on - also displays enemy boards and ships
void Game::DrawAllBoards()
{
    if (debugMode)
    {
        std::cout << "\n"; displayCentered("----- Enemy Fleet (DM) -----\n");
        enemyBoard.Print(true, true);

        std::cout << "\n"; displayCentered("----- Enemy Attacks (DM) -----\n");
        playerBoard.Print(false, true);
    }

        std::cout << "\n"; displayCentered("----- Your Attacks -----\n");
        enemyBoard.Print(false, true);

        std::cout << "\n"; displayCentered("----- Your Fleet -----\n");
        playerBoard.Print(true, true);
}

// Main menu option 2 to show instructions, then back to main menu
void Game::ShowInstructions()
{
    ClearScreen();

    std::string dummy;

    std::cout << "----- Instructions -----\n";
    std::cout << "Objective: Defeat the enemy fleet by sinking all of their ships before they sink yours\n";
    std::cout << "Tip - After you score a hit, target adjacent cells until the ship is sunk!\n";
    std::cout << "A message will be displayed when you sink a ship, as well as scoring a hit or miss\n";
    std::cout << "Make sure to enter all text input in lowercase\n\n";

    std::cout << "----- Ship placement -----\n";
    std::cout << "You can choose whether to place your ships manually or randomly\n";
    std::cout << "For manual placement, enter a grid coordinate in the range and format:\nLetter (A-J) followed by Number (0-9), e.g., A6, C4, J9\n";
    std::cout << "You can rotate the orientation of ship placement by entering 'r'\nKeep in mind that the length of the ship can't extend outside the board\n";
    std::cout << "The ship will extend vertically or horizontally beginning from the selected coordinate\n\n";

    std::cout << "----- Game Controls -----\n";
    std::cout << "To attack, enter a grid coordinate in the range and format - Letter (A-J) followed by Number (0-9), e.g. B8\n";
    std::cout << "You may only target a coordinate once\n";
    std::cout << "To quit the game, enter 'surrender' during your turn\n\n";

    std::cout << "----- Boards and Symbols -----\n";
    std::cout << "You have 2 boards available\n"; 
    std::cout << "Your Attacks - Shows the enemy waters, and displays your hits, misses, and targetable coordinates\n"; 
    std::cout << "Your Fleet - shows your fleet and the enemy hits, misses, and your remaining ships\n";
    std::cout << "  . - Empty coordinate\n";
    std::cout << "  S - Ship\n";
    std::cout << "  X - Hit\n";
    std::cout << "  O - Miss\n\n";

    std::cout << "Press enter to return to the main menu";
    std::getline(std::cin, dummy);
}

// If manual ship placement is selected, player selects coordinates for each ship while board is displayed
void Game::ManualShipPlacement(Board& board)
{
    int row, col;
    std::string input;
    std::string dummy;
    Orientation orientation = HORIZONTAL;

    // Defines ships with name and size
    ShipType ships[5] = {
        { "Carrier", 5 },
        { "Battleship", 4 },
        { "Destroyer", 3 },
        { "Submarine", 3 },
        { "Patrol Boat", 2 }
    };

    std::cout << "<<< Manual Ship Placement >>>\n";
    std::cout << "Enter a grid coordinate in the range and format - Letter (A-J) followed by Number (0-9), (e.g. A6).\n";
    std::cout << "Enter 'r' to rotate ship orientation\n";
    std::cout << "Current orientation: HORIZONTAL\n\n";

    // Loops through each ship to be placed
    for (int i = 0; i < 5; ++i)
    {
        bool placed = false; 

        // Loops until valid spot is selected
        while (!placed)
        {
            // Keep printing board
            board.Print(true);
            // Output ship name and size
            std::cout << "\nPlacing ship '" << ships[i].name << "' (size " << ships[i].size << "): ";
            std::cin >> input;
            std::cin.ignore(1000, '\n');

            // Changes orientation of ship placement (horizontal/vertical) on r input
            if (input == "R" || input == "r")
            {
                ClearScreen();
                orientation = (orientation == HORIZONTAL) ? VERTICAL : HORIZONTAL;
                std::cout << "<<< Manual Ship Placement >>>\n";
                std::cout << "Enter a grid coordinate in the range and format - Letter (A-J) followed by Number (0-9), (e.g. A6)\n";
                std::cout << "Enter 'r' to rotate ship orientation\n";
                std::cout << "Orientation changed to " << (orientation == HORIZONTAL ? "HORIZONTAL" : "VERTICAL") << "\n\n";
                continue;
            }

            // If invalid format, display message and instruction
            if (!CoordinateInput(input, row, col))
            {
                std::cout << "Invalid input. Enter a grid letter and number e.g. E4";
                Sleep(2000);
                ClearScreen();
                std::cout << "<<< Manual Ship Placement >>>\n";
                std::cout << "Enter a grid coordinate in the range and format - Letter (A-J) followed by Number (0-9), (e.g. A3).\n";
                std::cout << "Enter 'r' to rotate ship orientation\n";
                std::cout << "Current orientation: " << (orientation == HORIZONTAL ? "HORIZONTAL" : "VERTICAL") << "\n\n";
                continue;
            }

            // If ship out of bounds or overlapping another ship, display message and instructions
            if (!board.CanPlaceShip(row, col, ships[i].size, orientation))
            {
                std::cout << "You can't park there. A ship cannot overlap another ship or go out of bounds";
                Sleep(2000);
                ClearScreen();
                std::cout << "<<< Manual Ship Placement >>>\n";
                std::cout << "Enter a grid coordinate in the range and format - Letter (A-J) followed by Number (0-9), (e.g. g1).\n";
                std::cout << "Enter 'r' to rotate ship orientation\n";
                std::cout << "Current orientation: " << (orientation == HORIZONTAL ? "HORIZONTAL" : "VERTICAL") << "\n\n";
                continue;
            }

            // Creates a new ship object, Marks ship on grid, sets placed to true and iterates to next ship
            board.PlaceShip(row, col, ships[i].size, ships[i].name, orientation);
            ClearScreen();
            std::cout << "<<< Manual Ship Placement >>>\n";
            std::cout << "Enter a grid coordinate in the range and format - Letter (A-J) followed by Number (0-9), (e.g. C6).\n";
            std::cout << "Enter 'r' to rotate ship orientation\n";
            std::cout << "Current orientation: " << (orientation == HORIZONTAL ? "HORIZONTAL" : "VERTICAL") << "\n\n";
            placed = true;
        }
    }
    board.Print(true);
    std::cout << "\nAll ships placed\n";
    std::cout << "Press enter to continue";
    std::getline(std::cin, dummy);
    ClearScreen();
}

// Game over screen shows win/loss screens, then gameplay stats - time played, number of hits, misses, and ships sunk
// Warning - Not const as method uses game state variables
void Game::gameOverScreen(bool playerWon)
{
    std::string dummy;
    ClearScreen();

    if (playerWon)
    {
        SetRgb(COLOUR_BLUE_ON_BLACK);
        std::cout << R"(                                         __     ___      _                   _ 
                                         \ \   / (_) ___| |_ ___  _ __ _   _| |
                                          \ \ / /| |/ __| __/ _ \| '__| | | | |
                                           \ V / | | (__| || (_) | |  | |_| |_|
                                            \_/  |_|\___|\__\___/|_|   \__, (_)
                                                                       |___/   
)" << "\n";
        SetRgb(COLOUR_YELLOW_ON_BLACK);
        std::cout << R"(                                                                       .''.       
                                           .''.      .        *''*    :_\/_:     . 
                                          :_\/_:   _\(/_  .:.*_\/_*   : /\ :  .'.:.'.
                                      .''.: /\ :   ./)\   ':'* /\ * :  '..'.  -=:o:=-
                                     :_\/_:'.:::.    ' *''*    * '.\'/.' _\(/_'.':'.'
                                     : /\ : :::::     *_\/_*     -= o =-  /)\    '  *
                                      '..'  ':::'     * /\ *     .'/.\'.   '
                                          *            *..*         :)";
        SetRgb(COLOUR_CYAN_ON_BLACK);
        std::cout << R"(
                                                         |__
                                                         |\/
                                                         ---
                                                         / | [
                                                  !      | |||
                                                _/|     _/|-++'
                                            +  +--|    |--|--|_ |-
                                         { /|__|  |/\__|  |--- |||__/
                                        +---------------___[}-_===_.'____               /\
                                    ____`-' ||___-{]_| _[}-  |     |_[___\==--          \/   _
                     __..._____--==/___]_|__|_____________________________[___\==--___,-----' .7
                    |                  *****> Press Enter to continue <*****             BB-61/
~~~~~~~~~~~~~~~~~~~~\_______________________________________________________________________|~~~~~~~~~~~~~~~~~~~~~~~~~~)";

    }
    else
    {
        SetRgb(COLOUR_RED_ON_BLACK);
        std::cout << R"(                                          ____        __            _         
                                         |  _ \  ___ / _| ___  __ _| |_       
                                         | | | |/ _ \ |_ / _ \/ _` | __|      
                                         | |_| |  __/  _|  __/ (_| | |_ _ _ _ 
                                         |____/ \___|_|  \___|\__,_|\__(_|_|_)
                                              
        )";
        
        SetRgb(COLOUR_CYAN_ON_BLACK);
        std::cout << R"(                                                                  /    _,'|
                                                                 /_ _,'   |     
                                                                $$;'     _;     
                                                ,-'-._    ,-'. ,-'    _.'
                                                \     `-,'  ,-'    _,'
                               _od8PP8booo   ,....       ;,'    ,,'  _____
                             d8P''         ,'     \   _,'    ,-' ,oo8P"""Y8.
                             `'             `-.    i,'    ,-',odPP''      8b
                                               `-,'    ,-',o8P'          ,8P
                                            .',-'   ,-',o8P'             d8
                                         .'.-'  _,-',o8P'               ,8P
                                       ',-'  _,' _o8P'                  dP
                            8bo,     _,'  _,'  ,dP'                    d8
                              Y8'    \ ,,'  ,o8P'                    _op'                     _,d8P
                              dP      '  ,o8P'                     ,o8'                   ,oo8P"'
                              Yb     _oo8P'                      ,dP'                 ,odPP''
                               Ybooo8P''                       ,dP'              _,odPP'
                                 ''                           o8'            _oo8P"'
                                                            ,8P         _,odPP''
                                                           d8'    __,odPP"'
                                                           Y8oooo8PP"'
                                       *****> Press Enter to continue <*****)";
        


    }

    SetRgb(COLOUR_GREEN_ON_BLACK);
    Sleep(1000);
    std::getline(std::cin, dummy);
    ClearScreen();
    // Uses start and end time to give total time played in seconds (int)
    time_t endTime = time(0);
    int duration = static_cast<int>(difftime(endTime, gameStartTime));

    // Game over stats and loop back to main menu for another game
    std::cout << (playerWon ? "\n**********VICTORY!**********\n\nCongratulations! You sank all the enemies ships\n\n" : "\nDEFEAT...\n\nYou lose! All you're ships have been sunk\n\n");
    std::cout << "Time Played: " << duration << " seconds\n\n";
    std::cout << "----- Player Stats -----\n";
    std::cout << "Shots Fired: " << playerShots << "\n";
    std::cout << "Hits: " << playerHits << "\n";
    std::cout << "Misses: " << playerMisses << "\n";
    std::cout << "Ships Sunk: " << playerShipsSunk << "\n\n";
    std::cout << "----- Enemy Stats -----\n";
    std::cout << "Shots Fired: " << aiShots << "\n"; 
    std::cout << "Hits: " << aiHits << "\n";
    std::cout << "Misses: " << aiMisses << "\n";
    std::cout << "Ships Sunk: " << aiShipsSunk << "\n";
    std::cout << "\nPress enter to return to the main menu";
    Sleep(1000);
    std::getline(std::cin, dummy);
}
