#include <stdio.h>
#include <string.h>

#include "defs.h"

/*
Function: Print items
Purpose: Print items within struct
ev: struct that holds all information to be printed 
*/
void printEvidence(EvidenceType* ev){
    int hour = 0, min = 0, sec = 0;
    printf("%-5i", ev->id);
    printf("|%20s",ev->room);
    printf(" |%10s",ev->device);
    if(strcmp(ev->device,"EMF") == 0){
        if(ev->value > 4){
            printf(" |%9.1f(HIGH)",ev->value);
        }
        else{
            printf(" |%15.1f",ev->value);
        }
    }
    else if(strcmp(ev->device,"THERMAL") == 0){
        if(ev->value < 0){
            printf(" |%9.2f(COLD)",ev->value);
        }
        else{
            printf(" | %14.2f",ev->value);
        }
    }
    else{
        if(ev->value < 35){
            printf(" |%6.1f(WHISPER)",ev->value);

        }
        else if(ev->value > 70){
            printf(" |%7.1f(SCREAM)",ev->value);
        }
        else{
            printf(" |%15.1f",ev->value);
        }
        
    }

    hour = ev->timestamp / 3600;
    min = (ev->timestamp % 3600) / 60;
    sec = ev->timestamp - hour * 3600 - min * 60;

    if (hour > 9){
        printf(" | %i", hour);
    }
    else{
        printf(" | 0%i", hour);
    }

    if (min > 9){
        printf(":%i", min);
    }
    else{
        printf(":0%i", min);
    }
    
    if (sec > 9){
        printf(":%i", sec);
    }
    else{
        printf(":0%i", sec);
    }
    
    printf("\n");
}

/*
Function: Print evidence array
Purpose: Print all evidence in array
evArr: Given evidence array
*/
void printEvidenceArray(EvidenceArray* evArr){
    printf("  ID |                Room |    Device |          Value | Timestamp\n");

    for (int i = 0; i < evArr->size; i++){
        printEvidence(evArr->elements + i);
    }
    
}

/*
Function: Copy evidence from one struct to another
Purpose: Copy evidence from src to dest
src: Struct that provides the evidence elements
dest: The location of where to copy evidence
*/
void copyEvidence(EvidenceType* dest, EvidenceType* src){
    initEvidence(src->id, src->room, src->device, src->value, src->timestamp, dest);
}


/*
Function: Grow array
Purpose: Grow the capacity of evidence array by 2 times
evArr: the evidence array give to double it's capacity
*/
void growEvidenceArray(EvidenceArray* evArr){
    evArr->capacity = 2 * evArr->capacity;
    EvidenceType* ev;

//    ev = (EvidenceType*) malloc(evArr->capacity * sizeof(EvidenceType));
    ev = (EvidenceType*) calloc(evArr->capacity,sizeof(EvidenceType));

    for (int i = 0; i < evArr->size; i++){
        ev[i] = evArr->elements[i];
    }
    free(evArr->elements);
    evArr->elements = ev;

}

/*
Function: Add evidence to array
Purpose: Add src to dest 
dest: Given array
src: Evidence to put in dest
*/
void addEvidence(EvidenceArray* dest, EvidenceType* src){
    if(dest->capacity == dest->size){
        growEvidenceArray(dest);
    }

    if(dest->size == 0){
        dest->elements[0] = *src;
        dest->size = 1;
    }
    
    else{
        for(int i = 0; i < dest->size; i++){
            if(strcmp(dest->elements[i].room, src->room) < 0){
                shiftElementsUp(dest, src, i);
                break;
            }
            else if (strcmp(dest->elements[i].room, src->room) == 0 && dest->elements[i].timestamp > src->timestamp){
                shiftElementsUp(dest, src, i);
                break;
            }
            else if (i == dest->size - 1){
                addToEnd(dest, src);
                break;
            }
        }
    }
}

/*
Fucntion: Delete evidence
Purpose: Delete evidence with given id
src: The evidence array with stored data
id: id of the evidence to delete
*/
int delEvidence(EvidenceArray* src , int id){
    for(int i = 0; i < src->size; i++){
        if(src->elements[i].id == id){
            shiftELementsDown(src, i);
            return C_OK;
        }
    }

    return C_NOK;
}

/*
Function: Deallocates memory
Purpose: Frees memory that was allocated in evArr
evArr: Array with evidence data
*/
void cleanupEvidenceArray(EvidenceArray* evArr){
    free(evArr->elements);
    free(evArr);
}

/*
Fucntion: Move elements up the array
Purpose: Move elements to place src at 'i' position
evArr: The arr that holds data
src: The evidence to put into evArr
i: position in evArr to put src
*/
void shiftElementsUp(EvidenceArray* evArr, EvidenceType* src, int i){
    for(int j = evArr->size; j > i; j--){
        evArr->elements[j].id = evArr->elements[j-1].id;
        evArr->elements[j].value = evArr->elements[j-1].value;
        evArr->elements[j].timestamp = evArr->elements[j-1].timestamp;
        strcpy(evArr->elements[j].room, evArr->elements[j-1].room);
        strcpy(evArr->elements[j].device, evArr->elements[j-1].device);
    }
    evArr->elements[i].id = src->id;
    evArr->elements[i].value = src->value;
    evArr->elements[i].timestamp = src->timestamp;
    strcpy(evArr->elements[i].room, src->room);
    strcpy(evArr->elements[i].device, src->device);
    evArr->size++;
}

/*
Fucntion: Move elements down the array
Purpose: Move elements to place src at 'i' position
evArr: The arr that holds data
i: position in evArr to remove
*/
void shiftELementsDown(EvidenceArray* evArr, int i){
    for (int j = i; j < evArr->size; j++){
        evArr->elements[j].id = evArr->elements[j+1].id;
        evArr->elements[j].value = evArr->elements[j+1].value;
        evArr->elements[j].timestamp = evArr->elements[j+1].timestamp;
        strcpy(evArr->elements[j].room, evArr->elements[j+1].room);
        strcpy(evArr->elements[j].device, evArr->elements[j+1].device);

    }
    evArr->size--;
}

/*
Function: Add element to end of array
Purpose: Add element to end of array
evArr: Arr with all data
src: Evidence to put at end
*/
void addToEnd(EvidenceArray* evArr, EvidenceType* src){
    evArr->elements[evArr->size].id = src->id;
    evArr->elements[evArr->size].value = src->value;
    evArr->elements[evArr->size].timestamp = src->timestamp;
    strcpy(evArr->elements[evArr->size].room, src->room);
    strcpy(evArr->elements[evArr->size].device, src->device);
    evArr->size++;
}