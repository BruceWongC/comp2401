#include <stdio.h>
#include <string.h>

#include "defs.h"

int main(){
  EvidenceArray* evArr;
  evArr = (EvidenceArray*) malloc (sizeof(EvidenceArray));
  initEvidenceArray(evArr, MAX_CAP);
  
  loadEvidenceData(evArr);

  EvidenceType* ev;
  ev = (EvidenceType*) malloc(sizeof(EvidenceType));

  int* user;
  user = (int*) malloc(sizeof(int));
  *user = 0;    
  int ID = 0, dvCode = 0, h = 0, m = 0, s = 0, totalSec = 0, userInput = 0;
  float value = 0;

  char *name = "";
  char *equip = "";

  name = (char*) malloc(2 * MAX_LEN * sizeof(char));
  equip = (char*) malloc(MAX_LEN * sizeof(char));

  do{
    printMenu(user);

    if (*user == 1){

      printf("Enter the evidence ID: ");
      while(scanf("%i", &ID) != 1){
          while (getchar() != '\n');
          printf("Please enter a valid evidence ID: ");
      }
      getchar();

      printf("Enter the Room name: ");
      fgets(name, 2 * MAX_LEN, stdin);

      for (int i = 0; i < 16; i++){
          if(strcmp(&name[i],"\n") == 0){
              name[i] = '\0';
              break;
          }
      }

      printf("Enter the device code [EMF: 1, THERMAL: 2, SOUND: 3]: ");
      while(scanf("%i", &dvCode) != 1){
          while (getchar() != '\n');
          printf("Please enter a valid value: ");
      }
        
      if(dvCode == 1){
          strcpy(equip,"EMF");
      }
      else if (dvCode == 2){
          strcpy(equip,"THERMAL");
      }
      else{
          strcpy(equip,"SOUND");

      }
      
      printf("Enter the evidence value: ");
      while(scanf("%f", &value)!= 1){
          while (getchar() != '\n');
          printf("Please enter a valid evidence value: ");
      }
      
      printf("Enter the timestamp: ");
      while(scanf("%i %i %i", &h, &m, &s)!= 3){
          while (getchar() != '\n');
          printf("Please enter a valid timestamp: ");
      }           
      totalSec = h * 3600 + m * 60 + s;

      initEvidence(ID, name, equip, value, totalSec, ev);
      addEvidence(evArr, ev);
    }
    else if (*user == 2){
      printf("Please enter ID: ");
      while(scanf("%i", &userInput) != 1){
          while (getchar() != '\n');
          printf("Please enter a valid value: ");
      }
      if(delEvidence(evArr, userInput) == C_NOK){
        printf("ID doesn't exist. Please try again\n");
      }


    }
    else if (*user == 3){
      printEvidenceArray(evArr);
      printf("\n");
    }
      
  } while (*user != 0);
  
  free(ev);
  cleanupEvidenceArray(evArr);
  free(name);
  free(user);
  free(equip);
  return 0;
}

/* 
  Function: Print Menu
  Purpose:  Print the main menu and get the user's choice via user input
  Params:   
    Output: int* choice - the choice typed by the user
*/
void printMenu(int* choice)
{
  // NOTE: Do not make _any_ modifications to this function.
  int c = -1;
  int numOptions = 3;

  printf("\nMAIN MENU\n");
  printf("  (1) Add evidence\n");
  printf("  (2) Delete evidence\n");
  printf("  (3) Print evidence\n");
  printf("  (0) Exit\n\n");

  printf("Please enter your selection: ");
  scanf("%d", &c);

  if (c == 0) {
    *choice = c;
    return;
  }

  while (c < 0 || c > numOptions) {
    printf("Please enter your selection: ");
    scanf("%d", &c);
  }

  *choice = c;
}

