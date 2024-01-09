#include "defs.h"
#include <string.h>

/*
Purpose: Return an allocated room with initialized values
In:
Name: Name of room to set its room name

Output: room that will be used by hunters and ghost to move around (stored in house too)
*/
RoomType* createRoom(char* name){
    RoomType* room = calloc(1, sizeof(RoomType));
    strcpy(room->name, name);
    room->ghost = NULL;
    
    sem_init(&room->babyLock, 0 ,1);
    
    initEvidenceList(&room->evlist);
    initRoomList(&room->rooms);
    return room;
}

/*
Purpose: Initialize roomlist
In:
list: RoomList to initialize its data

Output: Initialized roomlist struct for rooms connected to given room
*/
void initRoomList(RoomList *list){
    NodeTypeRoom* node = malloc(sizeof(NodeTypeRoom));
    list->head = node;
    list->head->next = list->tail;
    list->tail = NULL;
}

/*
Purpose: Connect the 2 rooms together by putting them in each others roomlist
In/out:
room1: Room #1 to connect
room2: Room #2 to connect

Output: Both rooms with both rooms connected to each other
*/
void connectRooms(RoomType* room1, RoomType* room2){
    addRoom(&room1->rooms, room2);//assume '&' before room stops complaining then
    addRoom(&room2->rooms, room1);
}

/*
Purpose: add inputed room into the roomlist linked list
In:
room: room to add to linked list

In/out:
roomList: roomList to add the room to the linked list

Output: roomlist with given room added 
*/
void addRoom(RoomList* roomList, RoomType* room){//add to next node of roomList
    NodeTypeRoom* newNode = malloc(sizeof(NodeTypeRoom));
    newNode->data = room;
    newNode->next = NULL;
    NodeTypeRoom* currNode = roomList->head; 
    while (currNode->next != NULL){
        currNode = currNode->next;
    }
    currNode->next = newNode;
    roomList->tail = newNode;
    roomList->size++;
    return;
}

/*
Purpose: Free all data in the roomList nodes
In:
list: RoomList to free all its data

Ouput: Roomlist with node data freed
*/
void cleanupRoomListData(RoomList* list){
	NodeTypeRoom* cur = list->head->next;

	while(cur->next != NULL){

		cleanupEvidenceList(cur->data->evlist);
		cleanupRoomList(&cur->data->rooms);
		free(cur->data);
		cur = cur->next;
	}
	cleanupEvidenceList(cur->data->evlist);
    cleanupRoomList(&cur->data->rooms);
    free(cur->data);
}

/*
Purpose: Free the allocated memory of each node in roomlist
In:
list: roomlist to free its nodes

Output: Roomlist with nodes all freed
*/
void cleanupRoomList(RoomList* list){
    NodeTypeRoom* prev = list->head;
    NodeTypeRoom* cur = list->head->next;
    
	while(cur != NULL){
		free(prev);
		prev = cur;
		cur = cur->next;
	}
	free(prev);
}
