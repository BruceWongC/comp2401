#include "defs.h"

int main()
{
    BuildingType* building;
    building = (BuildingType*) malloc(sizeof(BuildingType));
    initBuilding(building);
  
    int *user;
    user = (int*) malloc(sizeof(int));
    *user = 0;

    loadBuildingData(building);
    do
    {
    printMenu(user);

    if (*user == 1){
        printRooms(&building->rooms);
    }
    else if (*user == 2){
        printGhostList(&building->ghosts);
    }
    else if (*user == 3){
        printByLikelihood(&building->ghosts,0);
    }
    else if (*user == 4){
        printByLikelihood(&building->ghosts,1);
    }
    else if (*user == 0){
        printf("Exiting...");
        break;
    }
    
    else{
        printf("Error: Invalid Selection. Please try again.\n");
    }

    } while (*user != 0);
  
    cleanupBuilding(building);
    free(user);

  return 0;
}

void printMenu(int *choice)
{
  printf("\nMAIN MENU\n");
  printf("  (1) Print rooms\n");
  printf("  (2) Print ghosts\n");
  printf("  (3) Print ghosts by likelihood\n");
  printf("  (4) Print most/least likely ghosts\n");
  printf("  (0) Exit\n\n");

  printf("Please enter your selection: ");
  scanf("%2d", choice);
  while (getchar() != '\n');
}

