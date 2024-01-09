#include "defs.h"

/*
Function: initGhostlist
Purpose: Init items in linkedlist
list: Linklist to init
*/
void initGhostList(GhostListType *list){
    list->head = NULL;
    list->tail = NULL;
}

/*
Function: initGhost
Purpose: init Ghost items
id: ID of ghost
gt: GhostType
r: Room type
like: likelihood value
ghost: ghost to init values
*/
void initGhost(int id, GhostEnumType gt, RoomType *r, float like, GhostType **ghost){
    *ghost = (GhostType*) malloc(sizeof(GhostType));
    (*ghost)->ghostType = gt;
    (*ghost)->room = r;
    (*ghost)->id = id;
    (*ghost)->likelihood = like;

}

/*
Function: addGhost
Purpose: add ghost to list
list: list to add ghost
ghost: Type of ghost
*/
void addGhost(GhostListType *list, GhostType *ghost){
    NodeType* newNode;
    newNode = (NodeType*) malloc (sizeof(NodeType));
    newNode->data = ghost;
    newNode->next = NULL;
  
    if(list->head == NULL){
        list->head = newNode;
        list->tail = newNode;

    }
    else{
        NodeType* currNode = list->head; 

        while (currNode->next != NULL){
            currNode = currNode->next;
        }
        currNode->next = newNode;
        list->tail = newNode;

    }
}

/*
Function: cleanupGhostData
Purpose: free memory from ghost data
list: list with data to cleanup
*/
void cleanupGhostData(GhostListType *list){
    NodeType *currNode = list->head;
    NodeType *nextNode = NULL;

    while (currNode != NULL){
        nextNode = currNode->next;
        free(currNode->data);
        currNode = nextNode;
    }
}

/*
Function: cleanupGhostList
Purpose: free memory from list
list: list to cleanup
*/
void cleanupGhostList(GhostListType *list){
    freeNodes(list->head);
}

/*
Fucntion: freeNodes
Purpose: free nodes from given list
head: head of ghostlist
*/
void freeNodes(NodeType* head){
    NodeType *currNode = head;
    NodeType *nextNode = NULL;

    while (currNode != NULL){
        nextNode = currNode->next;
        free(currNode);
        currNode = nextNode;
    }
}
/*
Function: printGhost
Purpose: print ghost
ghost: ghost data to print
*/
void printGhost(const GhostType *ghost){
    printf("ID:%9i | Type:", ghost->id);

    if(ghost->ghostType == 0){
        printf("    POLTERGEIST |");
    }
    else if (ghost->ghostType == 1){
        printf("         WRAITH |");
    }
    else if (ghost->ghostType == 2){
        printf("        PHANTOM |");
    }
    else if (ghost->ghostType == 3){
        printf("        BULLIES |");
    }
    else{
        printf("          OTHER |");
    }
    
    printf(" Room: ");
    if (ghost->room != NULL){
        printf("%-17s|", ghost->room->name);
    }
    else{
        printf("Unknown          |");
    }

    printf(" Likelihood: ");
    printf("%.2f", ghost->likelihood);
    

}

/*
Function: printGhostList
Purpose: print ghost list
ghost: ghost data list to print
*/
void printGhostList(const GhostListType *list){//ghost type is num so print for correct type
    NodeType *currNode = list->head;
    if(list->head == NULL){
        printf("No ghost in this room\n");
    }

    while (currNode != NULL){
        printGhost(currNode->data);
        printf("\n");

        currNode = currNode->next;
    }
    
}

void addGhostByLikelihood(GhostListType *list, GhostType *ghost){
    NodeType *currNode = list->head;
    NodeType *prevNode = NULL;

    NodeType *newItem = malloc(sizeof(NodeType));
    newItem->data = ghost;

    if (currNode == NULL){//if no items in list
        list->head = newItem;
        list->head->next = NULL;
    }

    while (currNode != NULL){

        if(currNode->data->likelihood < ghost->likelihood){//get node that's less then ghost
            break;
        }

        prevNode = currNode;
        currNode = currNode->next;    
        }

    newItem->next = currNode;//next item gets connected
    if(prevNode == NULL){
        list->head = newItem;//insert to head
    }
    else{
        prevNode->next = newItem;//item bigger than newItem gets connected
        if(currNode == NULL){//tail gets last item
            list->tail = newItem;
            list->tail->next = NULL;
        }


    }




}

void printByLikelihood(const GhostListType *origList, int endsOnly){//add endsonly
    GhostListType* tempList;
    tempList = (GhostListType*) malloc (sizeof(GhostListType));
    initGhostList(tempList);

    NodeType* currNode = origList->head;

    while (currNode != NULL){
        addGhostByLikelihood(tempList, currNode->data);
        currNode = currNode->next;
    }

    currNode = tempList->head;

    if(endsOnly == 1){
        printf("Most likely ghost:\n");
        printGhost(tempList->head->data);
        printf("\nLeast likely ghost:\n");
        printGhost(tempList->tail->data);       
    }
    else{
        printGhostList(tempList);
    }

    cleanupGhostList(tempList);
    free(tempList);

}
