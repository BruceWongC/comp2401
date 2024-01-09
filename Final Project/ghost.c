#include "defs.h"

/*	initGhost()
	Description: Initializes a given ghost
	
	In: RoomType* curRoom - Pointer of the room ghost starts in
	Out: GhostType** ghost - Address of pointer of ghost structure

	Output: Initializes Ghost structure inside ghost parameter
*/
void initGhost(RoomType* curRoom, GhostType** ghost){
    *ghost = (GhostType*) malloc(sizeof(GhostType));
    (**ghost).GhostClass = randomGhost();
    (**ghost).curRoom = curRoom;
    (**ghost).boredomTimer = 0;
    l_ghostInit((**ghost).GhostClass, (**ghost).curRoom->name);
}

/*	startGhost()
	Description: Runs ghost thread and behaviors
	
	In/Out: void* ghosty - void pointer argument containing ghost structure

	Output: Simulates and logs all ghost behaviors
*/
void *startGhost(void* ghosty){
    int num = 0;
    int choice = 0;
    GhostType** ghost = ghosty;
    NodeTypeRoom* cur;
    RoomType* tempRoom;

    while((*ghost)->boredomTimer < BOREDOM_MAX){//needs to check if hunter is in room
        (*ghost)->boredomTimer++;
	
        for (int i = 0; i < NUM_HUNTERS; i++){//finds if a hunter in room
            if ((*ghost)->curRoom->hunters[i] != NULL){
                (*ghost)->boredomTimer = 0;
                break;
            }
        }
        

        choice = randInt(1, 4); //This picks a number from 1-3
	    if(choice == 1){// move rooms
	        tempRoom = (*ghost)->curRoom;
	    
            if((*ghost)->boredomTimer > 0){
                sem_wait(&(*ghost)->curRoom->babyLock);
                
                cur = (*ghost)->curRoom->rooms.head->next;
                num = randInt(0, (*ghost)->curRoom->rooms.size);
                for (int i = 0; i < num; i++){
                    cur = cur->next;
                }
                
                sem_post(&(*ghost)->curRoom->babyLock);
		
		        if(&cur->data > &(*ghost)->curRoom){		//Lock sort
            		sem_wait(&cur->data->babyLock);
            		sem_wait(&(*ghost)->curRoom->babyLock);
            	}
            	else {
            		sem_wait(&(*ghost)->curRoom->babyLock);
            		sem_wait(&cur->data->babyLock);
            	}
            
		        (*ghost)->curRoom->ghost = NULL;
                (*ghost)->curRoom = cur->data;
                (*ghost)->curRoom->ghost = *ghost;
                
                sem_post(&(*ghost)->curRoom->babyLock);
                sem_post(&tempRoom->babyLock);

                l_ghostMove((*ghost)->curRoom->name);

            }
       }         
       else if(choice == 2){//pick evidence here
            EvidenceType evidence = pickEvidence(*ghost); //See no reason to be allocated

            sem_wait(&(*ghost)->curRoom->evlist.babyLock);
            addEvidence(&(*ghost)->curRoom->evlist, evidence);
            sem_post(&(*ghost)->curRoom->evlist.babyLock);

            l_ghostEvidence(evidence, (*ghost)->curRoom->name);
            }
       else if(choice == 3){//remove once ghost is done
       		//printf("Pass\n");         
       }

       usleep(GHOST_WAIT);
   }

   (*ghost)->curRoom->ghost = NULL;
   l_ghostExit(LOG_BORED);
   return(0);
}

/*	GhostToString()
	Description: saves a string of the given Ghost Class onto a char array
	
	In: GhostClass ghost - The given Ghost Class
	Out: char* name - The char array where the string is saved

	Output: A char array with the correct string saved onto it
*/
void GhostToString(GhostClass ghost, char* name){
	switch (ghost){
    case POLTERGEIST:
        strcpy(name, "POLTERGEIST");
        break;
    case BANSHEE:
        strcpy(name, "BANSHEE");
        break;
    case BULLIES:
        strcpy(name, "BULLIES");
        break;
    case PHANTOM:
        strcpy(name, "PHANTOM");
        break;
    default:
    	strcpy(name, "UNKNOWN");
        break;
    }
}

