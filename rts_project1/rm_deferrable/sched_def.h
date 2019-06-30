#define arrival			0
#define execution 		1
#define deadline		2
#define period			3
#define abs_arrival		4
#define execution_copy  5
#define abs_deadline	6
#define def		7
#define ap_arrival		0
#define ap_execution 		1
#define ap_execution_copy  	2

//stucture of a task
typedef struct
{
	int T[8],instance,alive;
/*
		task parameters from the input file
		T[0] == T[arrival]  			(Arrival time)
		T[1] == T[execution]			(Execution time)
		T[2] == T[deadline] 			(Deadline time)
		T[3] == T[period]  			    (Period)
	
		task parameters modified internally
		T[4] == T[abs_arrival]  		(Absolute Arrival time)
		T[5] == T[execution_copy]	(Execution time copy)
		T[6] == T[abs_deadline]  	(Absolute Arrival time)
		T[7] == T[def]  		(is a deferrable server?)

		instance (Number of times the tasks had arrived since time = 0)
		alive (Whether the task is ready? 0 for NOT READY and 1 for READY )
*/
}task;

typedef struct
{
	int A[3],alive;
/*
		task parameters from the input file
		A[0] == T[ap_arrival]  			(Arrival time)
		A[1] == T[ap_execution]			(Execution time)
	
		task parameters modified internally
		A[2] == T[ap_execution_copy]	(Execution time copy)

		alive (Whether the aperiodic task is ready? 0 for NOT READY and 1 for READY )
*/
}aperiodic;

#define IDLE_TASK_ID 1023   // Just a random number
#define ALL 1
#define CURRENT 0

int task_inputs(task *t1,int n, FILE* fp);				//tasks parameters input - Arrival time , Execution time , Deadline and Period
int hyperperiod(task *t1,int n);			//Calculate hyperiod period of the task set  
float utilization(task *t1,int n);				//Calculates CPU utilization
int gcd(int a, int b);					//Find greatest common divisor
int lcm(int *a, int n);					//Find Least common multiple
int interrupt_check(task *t1,int tmr,int n);		//check for interrupt
int min(task *t1,int n,int p);				//Find minimum of given task parameter
void abs_arr_new(task *t1,int n,int k,int all);	//Update absolute arrival time (absolute arrival time = arrivaltime + instance*period) 
void abs_dead_new(task *t1,int n,int all);	//Update absolute deadline (absolute deadline = absolute arrival time + deadline )
void exec_time_copy(task *t1,int n,int all);	//Keep a backup copy of execution time
int aperiodic_task_input(aperiodic *a1,int n, FILE* fp);	// aperiodic task parameters input
int min_aperiodic(aperiodic *a1,int n,int p);		//to check the next aperiodic task available
int aperiodic_interrupt(aperiodic *a1,int tmr,int n);	//check if aperiodic task is available
