Manuel Broco
Project 1: Discrete Event Simulator
CIS 3207 Section 1
September 16, 2019

OVERVIEW:
This project was to build a discrete event simulator. Tasks enter the simulator via nodes in a priority queue. The priority arranges these nodes by the time remaining in it’s execution. When 
this task is pop’ed off the priority queue it enters the simulator. Based on its event type it will either be handled by the CPU handler or the DISK handler. Both of these handlers work 
generally the same. They either handle arrival or finish events and if they are busy the tasks will enter into a FIFO queue where they will wait to be serviced. The DISK handler however 
will choose between either servicing with Disk1 or Disk2 depending on whose queue is shorter. Once either all tasks in event queue are done or the final time is reached the simulator 
finishes. 

DATA STRUCTURES:
This project utilized 2 structs I made to hold events and nodes. I used a priority queue, FIFO queues, which were basically linked list. 

EVENT:
This basically represents a single unit of change in the system. It is a struct I made that holds data like task ID, event type, and time.

NODE:
This basically stores events to be executed and builds the different queues. It is a struct I made that holds data like the event and a pointer to the next node in the queue

PRIORITY QUEUE:
This was used to hold all the events as the were created and was prioritized by the amount of time left in the node event.time, where lowest values had higher priority to exit queue first. 

FIFO QUEUE:
The different devices each had their own FIFO queue. One queue each for the CPU, Disk1, and Disk2 to determine which task would be serviced next. 

DESIGN:
I used the resources provided by the professor and the different TA’s heavily in designing this program. Based on the constraints provided I new that I needed a certain number of event types, 
queues, and initial variables being SEED, INIT_TIME, FIN_TIME, ARRIVE_MIN, ARRIVE_MAX, QUIT_PROB, CPU_MIN, CPU_MAX, D1_MIN, D1_MAX, D2_MIN, and D2_MAX. These variables helped extensively with 
TESTING. Since I could set a starting SEED and other variables, this meant I could take the randomness out and focus on what results I was getting and test against other runs to debug and 
develop. 
I started by building the event and node sturctures and but print functions to show each individually for debugging. From building these I learned I needed to keep track of the number of 
tasks. I then moved onto the push() function, which probably took the longest out of all the functions surprisingly. This was probably because I was refreshing my memory on c programming 
using pointers. Next I worked on pop() and worked my way to enQueue() and deQueue() functions. Luckily push() and enQueue() were very similar as was pop() and deQueue(). 
Once I finished the queue functions I began work on the event handler functions starting with the CPU_Handler function following the materials provided on canvas. I finished up with the 
DISK_Handler function and how to print the console to a log.txt. 
