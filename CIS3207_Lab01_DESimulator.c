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
int INIT_TIME = 0;
int  FIN_TIME = 0;
int ARRIVE_MIN = 0;
int ARRIVE_MAX = 0;
double QUIT_PROB = 0;
int CPU_MIN = 0;
int CPU_MAX = 0;
int DISK1_MIN = 0;
int DISK1_MAX = 0;
int DISK2_MIN = 0;
int DISK2_MAX = 0;


//PROTOTYPE FUNCTIONS----------------------------------------------------------------------------------

//HANDLERS:

//MAIN-------------------------------------------------------------------------------------------------
int main() {

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
}
