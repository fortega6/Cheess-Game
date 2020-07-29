Cheess-Game

The program has two modes:

Console mode - The console mode will operate in a similar way to your
implementation for connect4 game in assignment 3. You will develop the console mode so
that it would be easier later to integrate your code with the GUI implementation.

graphical mode (Gui mode) - The graphical mode presents the user with visual
menus and controls enabling the user to play Chess, choose the game’s players (user vs. user
or user vs. computer, and set the game’s difficulty level in case the user is playing against the
computer.

For AI, the Minimax algorithm will be used. The Minimax algorithm is mostly the same as the but I use pruning to improve its efficiency.

The executable for the program will be named “𝑐ℎ𝑒𝑠𝑠𝑝𝑟𝑜𝑔”. The graphical mode is specified
as a command line argument:
./chessprog -c – will start the program in console mode.
./ chessprog -g – will start the program in GUI mode.
./ chessprog – will execute the program; with the default execution mode - console
