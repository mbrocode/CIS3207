/*
 * Name:	Manuel Broco
 * Section:	01
 * Date:	09/06/2019
 * Lab:  	CIS3207_Lab01_DESimulator
 * Goal: 	To design and implement a discrete event simulator that mimics how the cpu works.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Event Types:
#define CPU_ARRIVAL 0
#define CPU_FINISH 1
#define DISK_ARRIVAL 2
#define DISK_FINISH 3
#define SIMULATION_END 4

//States:
#define IDLE 0
#define BUSY 1


//GLOBAL VARIABLES--------------------------------------------------------

typedef struct event {
    int taskID;
    int eType;          //event type like CPU_ARRIVAL, SIMULATION_END, etc. Used to determine servicing
    int time;           //when event occurs to store in event queue
} event;

typedef struct node{
    struct event task;
    struct node* next;
} node;

event evnt;

node* CPU_Q = NULL;
node* D1_Q = NULL;
node* D2_Q = NULL;
node* E_Q = NULL;

//reset values to 0 when done for file read bit...
int SEED = 0;
int INIT_TIME = 0;      //Beginning of simulation
int FIN_TIME = 0;       //End of Simulation
int ARRIVE_MIN = 0;     //New process will enter sys at rand interval between min & max
int ARRIVE_MAX = 0;
float QUIT_PROB = 0.0;  //Prob process will exit sys after done executing on CPU
int CPU_MIN = 0;        //Time a process spends executing on CPU rand interval between min & max
int CPU_MAX = 0;
int DISK1_MIN = 0;      //Time a process spends doing I/O on Disk rand interval between min & max
int DISK1_MAX = 0;
int DISK2_MIN = 0;
int DISK2_MAX = 0;

int Time_CURRENT = 0;
int Time_RANDOM = 0;
int CPU_NoT = 0;
int D1_NoT = 0;
int D2_NoT = 0;
int E_NoT = 0;
int TOTAL_NoT = 1;

int CPU_STAT = IDLE;
int D1_STAT = IDLE;
int D2_STAT = IDLE;

//PROTOTYPE FUNCTIONS-----------------------------------------------------

int randTime(int max, int min, int* curTime);
event startEvent(int tID, int type, int tme);
void printNodeContents(node a);
void printEventContents(event a);

//Priority / Event Queue fNs:
void push(event tsk, node** eQ, int* eTotal);
event pop(int* eTotal, node** eQ);

//FIFO Queue fNs:
void enQueue(event tsk, node** fQ, int* tTotal);
event deQueue(int* tTotal, node** fQ);

//Handler fNs:
void CPU_Handler(event);
void DISK_Handler(event);


int main() {

    //READ FILE / COPY VARIABLE VALUES:----------------------------------
    FILE *fptr;
    char varStrValues[12];
    int varValues[12];
    int i = 0, j = 0;

    if ((fptr = fopen("config.txt","r")) == NULL){
       printf("Error! opening file");
       exit(1);
    }

    while(fscanf(fptr, "%*s %s", varStrValues) == 1){
        if(i==5){
            sscanf(varStrValues, "%f", &QUIT_PROB);
        }
        sscanf(varStrValues, "%d", &varValues[i++]);
        //printf("%s\n", varStrValues);
    }

    SEED = varValues[0];
    INIT_TIME = varValues[1];
    FIN_TIME = varValues[2];
    ARRIVE_MIN = varValues[3];
    ARRIVE_MAX = varValues[4];
    CPU_MIN = varValues[6];
    CPU_MAX = varValues[7];
    DISK1_MIN = varValues[8];
    DISK1_MAX = varValues[9];
    DISK2_MIN = varValues[10];
    DISK2_MAX = varValues[11];

    printf("INITIAL VARIABLES:");
    printf("\nSEED = %d", SEED);
    printf("\nINIT_TIME = %d", INIT_TIME);
    printf("\nFIN_TIME = %d", FIN_TIME);
    printf("\nARRIVE_MIN = %d", ARRIVE_MIN);
    printf("\nARRIVE_MAX = %d", ARRIVE_MAX);
    printf("\nQUIT_PROB = %2.1f", QUIT_PROB);
    printf("\nCPU_MIN = %d", CPU_MIN);
    printf("\nCPU_MAX = %d", CPU_MAX);
    printf("\nDISK1_MIN = %d", DISK1_MIN);
    printf("\nDISK1_MAX = %d", DISK1_MAX);
    printf("\nDISK2_MIN = %d", DISK2_MIN);
    printf("\nDISK2_MAX = %d\n\n", DISK2_MAX);

    fclose(fptr);


    //INTIALIZATION------------------------------------------------------
    Time_CURRENT = INIT_TIME;
    srand(SEED);

    //
    push(startEvent(0, SIMULATION_END, FIN_TIME), &E_Q, &E_NoT);
    //printNodeContents(*E_Q);
    push(startEvent(1, CPU_ARRIVAL, INIT_TIME), &E_Q, &E_NoT);
    //printNodeContents(*E_Q);

    printf("\nEVENT ID: \tEVENT TYPE: \t    EVENT TIME: ");


    //MAIN LOOP:---------------------------------------------------------
    //Loop to execute EventQueue
    while (E_NoT != 0 && Time_CURRENT < FIN_TIME) {

        //pop event from top of EventQ to be serviced
        evnt = pop(&E_NoT, &E_Q);
        //printEventContents(evnt);

        //update current time
        Time_CURRENT = evnt.time;
        //printf("\nCurrent Time: %d\n", Time_CURRENT);

        //service task according to its event type
        switch (evnt.eType){

            case CPU_ARRIVAL:
                CPU_Handler(evnt);
                break;

            case CPU_FINISH:
                CPU_Handler(evnt);
                break;

            case DISK_ARRIVAL:
                DISK_Handler(evnt);
                break;

            case DISK_FINISH:
                DISK_Handler(evnt);
                break;

            case SIMULATION_END:
                printf("\n    %d \t\tSIMULATION_END \t\t%d\n", evnt.taskID, Time_CURRENT);
                break;
        }
    }
    return 0;
}


///FUNCTIONS:____________________________________________________________

//RANDOM TIME: given interval, return random time------------------------
int randTime(int max, int min, int* curTime){
    int rTime = ((rand() % (max - min + 1)) + min) + *curTime;
    (*curTime) + rTime;
    return rTime;
}

//START EVENT: given data, return event----------------------------------
event startEvent(int tID, int type, int tme){
    event task;
    task.taskID = tID;
    task.eType = type;
    task.time = tme;
    return task;
}

//PRINT NODE CONTENTS: given node, print details of node-----------------
void printNodeContents(node a){
    printf("\n---------Contents of Node------------");
    printf("\nNode task taskID: \t%d", a.task.taskID);
    printf("\nNode task event type: \t%d", a.task.eType);
    printf("\nNode task event time: \t%d", a.task.time);
    printf("\nNode next: \t\t%d\n", a.next);
}

//PRINT EVENT CONTENTS: given event, print details of event--------------
void printEventContents(event a){
    printf("\n---------Contents of Event------------");
    printf("\nEvent task taskID: \t%d", a.taskID);
    printf("\nEvent task event type: \t%d", a.eType);
    printf("\nEvent task event time: \t%d\n", a.time);
}


///PRIORITY QUEUE:_______________________________________________________

//PUSH: given event, push a node with that event onto Event Queue--------
void push(event tsk, node** eQ, int* eTotal){

    //variable to help organize priority
    node* oldNode;
    oldNode = *eQ;

    //build node to hold event
    node* newNode = (node*)malloc(sizeof(node));
    newNode->task = tsk;
    newNode->next = NULL;

    //increment events total
    (*eTotal)++;

    //only applicable on first run to start empty Q
    if(*eQ == NULL){
        *eQ = newNode;
        return;
    }

    //check for lowest time to prioritize Q
    if(newNode->task.time < oldNode->task.time){
        newNode->next = oldNode;
        *eQ = newNode;
        return;
    }

    //reorganize linked list based on priority
    while(oldNode->next != NULL && newNode->task.time >= oldNode->next->task.time){
        oldNode = oldNode->next;
    }
    newNode->next = oldNode->next;
    oldNode->next = newNode;

    return;
}

//POP: given event Q, pop an event from top of eQ node-------------------
event pop(int* eTotal, node** eQ) {

    //pull top priority node data
    node *newNode = *eQ;

    //change second priority in eQ to top priority
    *eQ = (*eQ)->next;

    //pull event from node holding it
    event task = newNode->task;

    //deallocate the memory previously allocated to node
    free(newNode);

    //decrement event number of events
    (*eTotal)--;

    return task;
}


///FIFO QUEUEs:__________________________________________________________

//ENQUEUE: given event, enqueue a node with that event onto FIFO queue---
void enQueue(event tsk, node** fQ, int* tTotal){

    //variable to help link list
    node* oldNode;
    oldNode = *fQ;

    //build node to hold event
    node* newNode = (node*)malloc(sizeof(node));
    newNode->task = tsk;
    newNode->next = NULL;

    //increment task total
    (*tTotal)++;

    //check to see if fifo Q is empty
    if(*fQ == NULL){
        *fQ = newNode;
        return;
    }

    //if Q is not empty place node in line and connect list together
    while(oldNode->next != NULL){
        oldNode = oldNode->next;
    }
    oldNode->next = newNode;

    return;
}

//DEQUEUE: given fifo Q, dequeue an event from front of fQ node----------
event deQueue(int* tTotal, node** fQ){

    //pull front of fQ node data
    node *newNode = *fQ;

    //change second in fQ to first
    *fQ = (*fQ)->next;

    //pull event from node holding it
    event task = newNode->task;

    //deallocate the memory previously allocated to node
    free(newNode);

    //decrement event number of events
    (*tTotal)--;

    return task;
}


///EVENT HANDLERS:_______________________________________________________

//CPU HANDLER: given an event, handle it---------------------------------
void CPU_Handler(event tsk){

    //create rand num between 0-1
    float r, randNum;
    r = rand();
    randNum = r / RAND_MAX;

    //check if event type is CPU_FINISH
    if(tsk.eType == CPU_FINISH){

        printf("\n   %d \t\tCPU_FINISH \t\t%d", tsk.taskID, Time_CURRENT);
        CPU_STAT = IDLE;

        //check if process will exit the system
        if(randNum < QUIT_PROB){

            printf("\n   %d \t\tEXITS SYSTEM \t\t%d", tsk.taskID, Time_CURRENT);

        }else{

            //enter process back into eQ for disk I/O
            push(startEvent(evnt.eType, DISK_ARRIVAL, randTime(ARRIVE_MAX, ARRIVE_MIN, &Time_CURRENT)), &E_Q, &E_NoT);
        }
    }

    //check is event type is CPU_ARRIVAL
    if(tsk.eType == CPU_ARRIVAL){

        printf("\n   %d \t\tCPU_ARRIVAL \t\t%d" , tsk.taskID, Time_CURRENT);

        //enter process into fQ for CPU
        enQueue(tsk, &CPU_Q, &CPU_NoT);
        TOTAL_NoT++;
        push(startEvent(TOTAL_NoT, CPU_ARRIVAL, randTime(ARRIVE_MAX, ARRIVE_MIN, &Time_CURRENT)), &E_Q, &E_NoT);

        //check if CPU is available
        if (CPU_STAT == IDLE){

            printf("\n   %d \t\tSERVICED ON CPU \t%d" , tsk.taskID, Time_CURRENT);

            //pull task from front of CPU fQ
            tsk = deQueue(&CPU_NoT, &CPU_Q);

            //enter process back into eQ to finish on CPU
            push(startEvent(tsk.taskID, CPU_FINISH, randTime(CPU_MAX, CPU_MIN, &Time_CURRENT)), &E_Q, &E_NoT);
            CPU_STAT = BUSY;
        }
    }
    return;
}

//DISK HANDLER: given an event, handle it--------------------------------
void DISK_Handler(event tsk){

    //check if event type is DISK_FINISH
    if(tsk.eType == DISK_FINISH){

        //check to see which Disk has a smaller Q, finish task at smaller Q
        if(D1_NoT <= D2_NoT){

            printf("\n   %d \t\tDISK1_FINISH \t\t%d", tsk.taskID, Time_CURRENT);
            D1_STAT = IDLE;

        }else{

            printf("\n   %d \t\tDISK2_FINISH \t\t%d", tsk.taskID, Time_CURRENT);
            D2_STAT = IDLE;
        }
    }

    //check is event type is DISK_ARRIVAL
    if(tsk.eType == DISK_ARRIVAL){

        //check to see which Disk has a smaller Q, service task at smaller Q
        if(D1_NoT <= D2_NoT){

            //enter process into fQ for D1
            enQueue(tsk, &D1_Q, &D1_NoT);

            printf("\n   %d \t\tDISK1_ARRIVAL \t\t%d", tsk.taskID, Time_CURRENT);

            //check is D1 is available
            if (D1_STAT == IDLE){

                printf("\n   %d \t\tSERVICED ON D1 \t\t%d" , tsk.taskID, Time_CURRENT);

                //pull task from front of D1 fQ
                tsk = deQueue(&D1_NoT, &D1_Q);

                //enter process back into eQ to finish on D1
                push(startEvent(tsk.taskID, DISK_FINISH, randTime(DISK1_MAX, DISK1_MIN, &Time_CURRENT)), &E_Q, &E_NoT);
                D1_STAT = BUSY;
            }
        }else{

            //enter process into fQ for D2
            enQueue(tsk, &D2_Q, &D2_NoT);

            printf("\n   %d \t\tDISK2_ARRIVAL \t\t%d", tsk.taskID, Time_CURRENT);

            //check is D2 is available
            if (D2_STAT == IDLE){

                printf("\n   %d \t\tSERVICED ON D2 \t\t%d" , tsk.taskID, Time_CURRENT);

                //pull task from front of D2 fQ
                tsk = deQueue(&D2_NoT, &D2_Q);

                //enter process back into eQ to finish on D2
                push(startEvent(tsk.taskID, DISK_FINISH, randTime(DISK2_MAX, DISK2_MIN, &Time_CURRENT)), &E_Q, &E_NoT);
                D2_STAT = BUSY;
            }
        }
    }
    return;
}
