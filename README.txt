
 /$$$$$$$   /$$$$$$  /$$$$$$$$ /$$$$$$$$ /$$       /$$$$$$$$  /$$$$$$  /$$   /$$ /$$$$$$ /$$$$$$$ 
| $$__  $$ /$$__  $$|__  $$__/|__  $$__/| $$      | $$_____/ /$$__  $$| $$  | $$|_  $$_/| $$__  $$
| $$  \ $$| $$  \ $$   | $$      | $$   | $$      | $$      | $$  \__/| $$  | $$  | $$  | $$  \ $$
| $$$$$$$ | $$$$$$$$   | $$      | $$   | $$      | $$$$$   |  $$$$$$ | $$$$$$$$  | $$  | $$$$$$$/
| $$__  $$| $$__  $$   | $$      | $$   | $$      | $$__/    \____  $$| $$__  $$  | $$  | $$____/ 
| $$  \ $$| $$  | $$   | $$      | $$   | $$      | $$       /$$  \ $$| $$  | $$  | $$  | $$      
| $$$$$$$/| $$  | $$   | $$      | $$   | $$$$$$$$| $$$$$$$$|  $$$$$$/| $$  | $$ /$$$$$$| $$      
|_______/ |__/  |__/   |__/      |__/   |________/|________/ \______/ |__/  |__/|______/|__/      
                                                                                                  
                           

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
	|   Battleship game by Brandon Henwood, Media Design School, 2025    BB-61/
	 \_______________________________________________________________________|


NOTES FOR TESTING:
 - Enter "nuke" during the player turn to trigger win condition (and surrender for lose condition as per instructions below)
 - Recommend adjusting console window height (width is fine) to double the default size when using debug mode as enemy boards are displayed vertically stacked above the player boards

 - All game input should be lower case

 - If you enter an invalid input the game will display an info message and pause for 2 second before allowing you to try again

To Win:
 - Sink all enemy ships
To lose:
 - Have all your ships sunk by the enemy

DEBUG MODE:
 - Shows both enemy boards (fleet and attacks) as well as the players and tracks computer hits, misses etc.


----- Instructions -----
Objective: Defeat the enemy fleet by sinking all of their ships before they sink yours
Tip - After you score a hit, target adjacent cells until the ship is sunk!
A message will be displayed when you sink a ship, as well as scoring a hit or miss
Make sure to enter all text input in lowercase

----- Ship placement -----
You can choose whether to place your ships manually or randomly
For manual placement, enter a grid coordinate in the range and format: Letter (A-J) followed by Number (0-9), e.g., A6, C4, J9
You can rotate the orientation of ship placement by entering 'r' Keep in mind that the length of the ship can't extend outside the board
The ship will extend vertically or horizontally beginning from the selected coordinate

----- Controls -----
To attack, enter a grid coordinate in the range and format - Letter (A-J) followed by Number (0-9), e.g. B8
Enter a grid coordinate in the range and format - Letter (A-J) followed by Number (0-9), e.g. B8
You may only target a coordinate once
To quit the game, enter 'surrender' during your turn

----- Boards and Symbols -----
You have 2 boards available
Your Attacks - Shows the enemy waters, and displays your hits, misses, and targetable coordinates
Your Fleet - shows your fleet and the enemy hits, misses, and your remaining ships
  . - Empty coordinate
  S - Ship
  X - Hit
  O - Miss

Credits:
ASCII text from: https://patorjk.com/software/taag/#p=testall&f=Graffiti&t=BATTLESHIP
Main Menu 'BATTLESHIPS' Font Name: Big Money-ne
Victory Screen 'Victory!' Font Name: Standard

ASCII battleship art from: https://www.asciiart.eu/vehicles/navy (By Matthew Bace)
ASCII Fireworks art from: https://www.asciiart.eu/holiday-and-events/fireworks (By Joan Stark)
