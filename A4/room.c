#include "defs.h"

/*
Function: initRoom
Purpose init room struct
id: id of room
name: name of room
room: given room
*/
void initRoom(int id, char *name, RoomType **room){
    *room = (RoomType*) malloc(sizeof(RoomType));
    (*room)->id = id;
    strcpy((*room)->name, name);

    initGhostList(&(*room)->ghosts);

}

/*
Function: initRoomArray
Purpose: init array
arr: Array to init
*/
void initRoomArray(RoomArrayType *arr){
    arr->size = 0;
    arr->capacity = MAX_ARR;
}

/*
Function: addRoom
Purpose: add room to list
arr: list to add
r: Room to add
*/
void addRoom(RoomArrayType *arr, RoomType *r){
    if(arr->size < arr->capacity){
        arr->rooms[arr->size] = r;
        arr->size++;
    }

}

/*
Function: cleanupRoomArray
Purpose: Free allocated memory in room array
arr: array to clean up
*/
void cleanupRoomArray(RoomArrayType *arr){
    for (int i = 0; i < arr->size; i++){
        freeNodes(arr->rooms[i]->ghosts.head);      
        free(arr->rooms[i]);

    }    
}

/*
Function: printRooms
Purpose: print the array of rooms
arr: Room array to print
*/
void printRooms(const RoomArrayType *arr){
    for (int i = 0; i < arr->size; i++){
        printf("Room %i: %s", arr->rooms[i]->id, arr->rooms[i]->name);
        printf("\n--------------\n");
        printGhostList(&arr->rooms[i]->ghosts);
        printf("--------------\n\n");
    }
    



}