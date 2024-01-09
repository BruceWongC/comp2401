Bruce Wong 
ID: 101266031
Ka Hei Chan 
ID: 101260193

This program is a simulation of 4 hunter entities attempting to uncover evidence left behind by a ghost entity in an attempt to determine what kind of ghost it is through a house of rooms.

Files:
defs.h:		Contains all definitions and initializes all functions
main.c		Contains main loop code and runs threads, prevents memory leaks, and closes the program
house.c		Contains code for all functions for house structure
ghost.c		Contains code for all functions for ghost structure
hunter.c	Contains code for all functions for hunter structure
room.c		Contains code for all functions for room and room list structures
evidence.c	Contains code for all functions for evidence and evidence list structures
utils.c		Contains code for all miscellaneous utility function
logger.c	Contains code for all logging functions
makefile	makefile used to compile and clean code

Compiling: Enter the directory with all the above files in terminal and run the 'make' command which will compile all code into object files
Running: Enter the directory with all the object files in terminal and run './Final'.

Once the program begins running it will prompt you for the names of the four hunters. After entering them, the program will log their initialization and begin the simulation. The simulation will eventually complete on its own and print the results of the simulation.

