#define arrival			0
#define execution 		1
#define deadline		2
#define period			3
#define abs_arrival		4

#define abs_deadline	5
#define priority	6
#define resource_used	7
#define priority_copy	8
#define critical_start	9


#define task_count	0
#define priority_ceiling	1

//stucture of the task
typedef struct
{
	int T[10],instance,alive;
	float execution_copy,critical_execution_copy,critical_execution;
/*
		task parameters from the input file
		T[0] == T[arrival]  			(Arrival time)
		T[1] == T[execution]			(Execution time)
		T[2] == T[deadline] 			(Deadline time)
		T[3] == T[period]  			    (Period)
	
		task parameters modified internally
		T[4] == T[abs_arrival]  		(Absolute Arrival time)
		
		T[5] == T[abs_deadline]  	(Absolute Arrival time)
		T[6] == T[priority]		(priority of the task)
		T[7] == T[resource_used]	(resource used by the task)
		T[8] == T[priority_copy]	(priority copy)
		T[9] == T[critical_start]	(start flag of the critical section)
		

		instance (Number of times the tasks had arrived since time = 0)
		alive (Whether the task is ready? 0 for NOT READY and 1 for READY )
*/
}task;

typedef struct
{
	int R[2],lock,task_exe;
/*
		task parameters from the input file
		R[0] == R[task_count]
		R[1] == R[priority_ceiling]
		lock (Whether the task is LOCKED? 0 for NOT LOCKED and 1 for LOCKED )
		task_exe (the id of the task currently using the resource)
*/
}resource;

#define IDLE_TASK_ID 1023   // Just a random number
#define ALL 1
#define CURRENT 0

int task_inputs(task *t1,int n, FILE* fp);				//tasks parameters input - Arrival time , Execution time , Deadline and Period
float hyperperiod(task *t1,int n);			//Calculate hyperiod period of the task set  
float utilization(task *t1,int n);				//Calculates CPU utilization
int gcd(int a, int b);					//Find greatest common divisor
int lcm(int *a, int n);					//Find Least common multiple
int interrupt_check(task *t1,float tmr,int n);		//Scheduling point interrupt
int min(task *t1,int n,int p);				//Find minimum of given task parameter
int min_sans(task *t1,int n,int p,int m);
void abs_arr_new(task *t1,int n,int k,int all);	//Update absolute arrival time (absolute arrival time = arrivaltime + instance*period) 
void abs_dead_new(task *t1,int n,int all);	//Update absolute deadline (absolute deadline = absolute arrival time + deadline )
void exec_time_copy(task *t1,int n,int all);	//Keep a backup copy of execution time
void resource_input(resource *r1,FILE* fp,task* t,int n);
void cric_exec_copy(task *t1,int n);
