Name: Bruce Wong
ID: 101266031

Purpose: List and store information of evidence that user wants to store. User can also delete evidence information if they so choose.

Files:
-main.c: The main file that starts the program
-init.c: Contains functions to initialize EvidenceType and EvidenceArray. Additionally, it contains the function to load starting information
-evidence.c: Contains functions that do the operations of the program
README.txt: Contains description
defs.h: File that holds definitions of constants and the initial fucntions that will be used

Compiling and Running: 
- Go to the directory that contains the program
- Type "gcc -Wall -Wextra -o a3 main.c init.c evidence.c" in terminal to create a executable file
- Type "./a3" to run the executable file

Usage:
- Opening the program gives you 4 options: "1" to add evidence, "2" to delete evidece, "3" to print evidence and "4" to exit program

1: 
- First prompt will ask for an integer to be entered
- Second prompt will ask for a name of a room to be entered
- Third prompt will ask for either 1, 2, or 3 to be entered
- Fourth prompt will ask for an integer to be entered
- Last prompt will ask for 3 integers with space inbetween to be entered

2:
- Will ask for an ID
- If ID is valid, it will be deleted from the array, otherwise it will tell user that it wasn't valid and to try again

3:
- Will show all evidence in array in a easy to read format

0: 
- Exit program 


