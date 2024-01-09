Name: Bruce Wong
STD ID: 101266031

Purpose: Store information into arrays and display them to the user.

Files:
-main.c: Main file that starts program
-ghost.c: Holds all functions that operate on ghosts
-room.c: Holds all functions that operate on rooms
-building.c: Holds initialize building, clean and load information functions 
-defs.h: Holds definitions for structs, variables and functions
-README.txt: Contains description

Compiling and Running: 
- Go to the directory that contains the program
- Type "gcc -Wall -Wextra -o a4 main.c ghost.c room.c building.c" in terminal to create a executable file.
- Type "./a4" to run the executable file

Usage:
-Running program gives you 5 options

1. Prints rooms
2. Prints list of all ghosts
3. Prints list of all ghosts by likelihood (from highest to lowest)
4. Prints ghosts with highest and lowest likelihood
0. Exits program 



