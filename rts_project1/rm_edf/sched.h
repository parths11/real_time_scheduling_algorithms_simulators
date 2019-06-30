#define arrival			0
#define execution 		1
#define deadline		2
#define period			3
#define abs_arrival		4
#define execution_copy  5
#define abs_deadline	6

//stucture of the task
typedef struct
{
	int T[7],instance,alive;
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

		instance (Number of times the tasks had arrived since time = 0)
		alive (Whether the task is ready? 0 for NOT READY and 1 for READY )
*/
}task;

#define IDLE_TASK_ID 1023   // Just a random number
#define ALL 1
#define CURRENT 0

int task_inputs(task *t1,int n, FILE* fp);				//tasks parameters input - Arrival time , Execution time , Deadline and Period
int hyperperiod(task *t1,int n);			//Calculate hyperiod period of the task set  
float utilization(task *t1,int n);				//Calculates CPU utilization
int gcd(int a, int b);					//Find greatest common divisor
int lcm(int *a, int n);					//Find Least common multiple
int interrupt_check(task *t1,int tmr,int n);		//Scheduling point interrupt
int min(task *t1,int n,int p);				//Find minimum of given task parameter
void abs_arr_new(task *t1,int n,int k,int all);	//Update absolute arrival time (absolute arrival time = arrivaltime + instance*period) 
void abs_dead_new(task *t1,int n,int all);	//Update absolute deadline (absolute deadline = absolute arrival time + deadline )
void exec_time_copy(task *t1,int n,int all);	//Keep a backup copy of execution time

