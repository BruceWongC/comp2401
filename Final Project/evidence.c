#include "defs.h"

/*	pickEvidence()
	Description: Picks a random evidence based on the type of ghost
	
	In: GhostType* ghost - The ghost structure containing the ghost class being checked

	Output: Returns a random evidence that the given ghost class can leave
*/

EvidenceType pickEvidence(GhostType* ghost){
    int num = randInt(1, EV_COUNT);
    switch (ghost->GhostClass){
    case POLTERGEIST: 
        switch (num){
        case 1:
            return EMF;
            break;
        
        case 2:
            return TEMPERATURE;
            break;

        case 3:
            return FINGERPRINTS;
            break;
        default:
            return EV_UNKNOWN;
            break;
        }
        break;

    case BANSHEE:
        switch (num){
        case 1:
            return EMF;
            break;
        
        case 2:
            return TEMPERATURE;
            break;

        case 3:
            return SOUND;
            break;
        default:
            return EV_UNKNOWN;
            break;
        }
        break;
    
    case BULLIES:
        switch (num){
        case 1:
            return EMF;
            break;
        
        case 2:
            return FINGERPRINTS;
            break;

        case 3:
            return SOUND;
            break;
        default:
            return EV_UNKNOWN;
            break;
        }
        break;

    case PHANTOM:
        switch (num){
        case 1:
            return TEMPERATURE;
            break;
        
        case 2:
            return FINGERPRINTS;
            break;

        case 3:
            return SOUND;
            break;
        default:
            return EV_UNKNOWN;
            break;
        }
        break;

    default:
    	printf("ERROR: Evidence not Found");
        break;
    }

}

/*	initEvidenceList()
	Description: Initializes a given evidence list
	
	In: EvidenceList* ev - The given evidence list

	Output: Initializes EvidenceList structure inside evidence list parameter
*/
void initEvidenceList(EvidenceList* ev){
    NodeTypeEv* node = malloc(sizeof(NodeTypeEv));
    ev->head = node;
    node->next = ev->tail;
    ev->tail = NULL;
    sem_init(&ev->babyLock, 0 ,1);

}

/*	addEvidence()
	Description: Adds evidence to a given evidence list
	
	In: EvidenceType evidence - Evidence being added to evidence list
	In/Out: EvidenceList* ev - Address of evidence list being added to

	Output: The given evidence list with evidence added to the tail if it is not already in the list
*/
void addEvidence(EvidenceList* ev, EvidenceType evidence){//add to next node of ev
    NodeTypeEv* currNode = ev->head; 
    while (currNode->next != NULL){
        currNode = currNode->next;
        if(currNode->data == evidence){
			return;
		}
    }
    NodeTypeEv* newNode = malloc(sizeof(NodeTypeEv));
    newNode->data = evidence;
    newNode->next = NULL;
    currNode->next = newNode;
    ev->tail = newNode;     
}

/*	removeEvidence()
	Description: Removes evidence to a given evidence list
	
	In: EvidenceType evidence - Evidence being removed from evidence list
	In/Out: EvidenceList* ev - Address of evidence list being removed from

	Output: The given evidence list with the given evidence and node removed
*/
void removeEvidence(EvidenceList* ev, EvidenceType evidence){
    NodeTypeEv* curNode = ev->head;
    NodeTypeEv* prevNode = NULL;

    while (curNode->next != NULL){
        prevNode = curNode;
        curNode = curNode->next;
        if(curNode->data == evidence){
        	prevNode->next = curNode->next;
            free(curNode);
            return;
        }

    }

    ev->tail = prevNode;
}

/*	numberToEquipment()
	Description: Takes an integer and returns the corresponding evidence type
	
	In: int n - The given integer

	Output: Returns the evidence type corresponding to the given integer
*/

EvidenceType numberToEquipment(int n){
    switch (n){
    case 0:
        return EMF;
        break;
    case 1:
        return TEMPERATURE;
        break;
    case 2:
        return FINGERPRINTS;
        break;
    case 3:
        return SOUND;
        break;
    default:
    return EV_UNKNOWN;
        break;
    }
}

/*	EvidenceToString()
	Description: Saves the evidence type as a string in the given char array
	
	In: EvidenceType evidence - Evidence type to be converted into a string
	Out: char* name - The given char array

	Output: The given char array with the correct string saved onto it
*/
void EvidenceToString(EvidenceType evidence, char* name){
	switch (evidence){
    case EMF:
        strcpy(name, "EMF");
        break;
    case TEMPERATURE:
        strcpy(name, "TEMPERATURE");
        break;
    case FINGERPRINTS:
        strcpy(name, "FINGERPRINTS");
        break;
    case SOUND:
        strcpy(name, "SOUND");
        break;
    default:
    	printf("Unable to find evidence\n");
        break;
    }
}

/*	cleanupEvidenceList()
	Description: Frees all memory of nodes in an Evidence List
	
	In: EvidenceList evlist - The Evidence List being freed

	Output: The given Evidence List freed of all nodes
*/
void cleanupEvidenceList(EvidenceList evlist){
	NodeTypeEv* prev = evlist.head;
	NodeTypeEv* cur = evlist.head->next;
    if (cur == NULL){
        free(prev);
        return;
    }   
    
	while(cur != NULL){//what if no evidence was placed in the room
		free(prev);
		prev = cur;
		cur = cur->next;
	}

    free(prev);
    
}
