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


//GLOBAL VARIABLES-------------------------------------------------------------------------------------

int SEED = 0;
int INIT_TIME = 0;      //Beginning of simulation
int FIN_TIME = 0;       //End of Simulation
int ARRIVE_MIN = 0;     //New process will enter sys at rand interval between min & max
int ARRIVE_MAX = 0;
double QUIT_PROB = 0;   //Prob process will exit sys after done executing on CPU
int CPU_MIN = 0;        //Time a process spends executing on CPU rand interval between min & max
int CPU_MAX = 0;
int DISK1_MIN = 0;      //Time a process spends doing I/O on Disk rand interval between min & max
int DISK1_MAX = 0;
int DISK2_MIN = 0;
int DISK2_MAX = 0;


//PROTOTYPE FUNCTIONS----------------------------------------------------------------------------------


//MAIN-------------------------------------------------------------------------------------------------
int main() {

    //PART 1: Read variables from config.txt____________________________
    FILE *fptr;
    char varStrValues[12];
    int varValues[12] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
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
        printf("%s\n", varStrValues);
    }

    for(j=0; j<12; j++){
        printf("\n%d",varValues[j]);
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

    printf("\n\nSEED = %d", SEED);
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
    printf("\nDISK2_MAX = %d", DISK2_MAX);

    fclose(fptr);



    /*
    //Loop to execute EventQueue
    while (EventQueue is not empty ) {

        event = EventQueue.pop();

        switch (event.type){
            case JOB_ARRIVAL:
                handle_job_arrival(event, EventQueue);
                break;

            case JOB_CPU_FINISH:
                handle_cpu_exit(event, EventQueue);
                break;

            //add more cases...
        }
    }
    */
}


