#include<stdio.h>
#include<stdlib.h>
#include"sched.h"

int timer=0;


int main()
{
	task *t;
	int temp;
	float temp1;
	int n,hyper_period,active_task_id, q_task_id, deadline_task_id, Value_task_id;
	float cpu_utilization;
	
	FILE* filepointer;
	char line[1025];
	char value[10];
	line[1024]='\0';
	int label;
	filepointer=fopen("question1_taskset.txt","r"); /*put path to the input folder here*/


if (filepointer==NULL)
{
	fprintf(stderr,"Error: input file cannot be opened - access denies\n");
	printf("Error: input file cannot be opened - access denies\n");
	exit(1);
}

if(fgets(line,1024,filepointer)!=NULL)
{
	if (line[1024]!='\0')
	{
		fprintf(stderr,"Error: Line in file exceeding length\n");
		printf("Error: Line in file exceeding length\n");
		exit(1);
	}
/* parsing values from the file */
	else{
	int i=0;
	while(line[i]!='\n')
	{
		value[i]=line[i];
		i++;
	}
		value[i]='\0';
		n=atoi(value);
	}
	}
		t=malloc(n*sizeof(task));
		int simulation_time=task_inputs(t,n,filepointer);
		cpu_utilization = utilization(t,n);
		hyper_period=hyperperiod(t,n);
		exec_time_copy(t,n,ALL);
		abs_arr_new(t,n,0,ALL);
		abs_dead_new(t,n,ALL);

		int count[n];
		int k, j, m;

		int sched[simulation_time+1];
		for(k=0;k<simulation_time+1;k++)
			sched[k]=0;
		for(k=0;k<n;k++)
			count[k]=0;
		int preempt[n];
		for(k=0;k<n;k++)
			preempt[k]=0;
		int drop[n];
		for(k=0;k<n;k++)
		drop[k]=0;
		FILE* filepointer2;
		filepointer2=fopen("hvdf_output.txt","w"); /*put path to the output folder here*/

if (filepointer2==NULL)
{
	fprintf(stderr,"Error: input file cannot be opened - access denies\n");
	printf("Error: input file cannot be opened - access denies\n");
	exit(1);
}

fprintf(filepointer2,"CPU Utilization %f\n",cpu_utilization);
//printf("CPU Utilization %f\n",cpu_utilization);

		if(cpu_utilization<1)
		{
				fprintf(filepointer2,"Tasks can be scheduled\n");
				//printf("Tasks can be scheduled\n");
		}
		else
		{
				fprintf(filepointer2,"Schedule is not feasible\n");
				//printf("Schedule is not feasible; system is overloaded.\n");
		}
	
	int x;
	float value_density[n];

	//printing the task file
	/*
	printf ("\nSr. No.  Task_label  Arrival  Execution  Deadline   Period    Value  Value Density");


    for (x = 0; x < n; x++)
    {
        printf ("\n   %d    \t%d       %d     \t %d   \t  %d    \t%d    \t %d    \t %d    \n", x+1, t[x].T[actual_id],  t[x].T[arrival], t[x].T[execution], t[x].T[deadline], t[x].T[period], t[x].T[Value], value_density[x]);
    } 
*/
	
	float v;
	float wcet;

	//printf("%f\t%f\n",v,wcet);
	
	for(x=0; x<n; x++)
	{
		v = (float)t[x].T[Value];
		wcet = (float)t[x].T[execution];
		value_density[x] = (v/wcet);
		t[x].value_density = value_density[x];
		
	}

	

	//Printing the task table after computing value_density:

	//printf("\nAfter computing value density:\n");

	//printf ("\nSr. No.  Task_label  Arrival  Execution  Deadline   Period    Value  Value Density");

/*
    for (x = 0; x < n; x++)
    {
        printf ("\n   %d    \t%d       %d     \t %d   \t  %d    \t%d    \t %d    \t %f    \n", x+1, t[x].T[actual_id],  t[x].T[arrival], t[x].T[execution], t[x].T[deadline], t[x].T[period], t[x].T[Value], t[x].value_density);
    } 
*/
	//sort it according to deadline

	int y;
	for(y=1; y<n; y++)
	{
		for(x=0; x < n ; x++)
		{
			if(t[x].T[deadline]>t[x+1].T[deadline])
			{
				temp=t[x].T[deadline];
				t[x].T[deadline]=t[x+1].T[deadline];
				t[x+1].T[deadline]=temp;

				temp=t[x].T[arrival];
				t[x].T[arrival]=t[x+1].T[arrival];
				t[x+1].T[arrival]=temp;

				temp=t[x].T[execution];
				t[x].T[execution]=t[x+1].T[execution];
				t[x+1].T[execution]=temp;

				temp=t[x].T[period];
				t[x].T[period]=t[x+1].T[period];
				t[x+1].T[period]=temp;

				temp=t[x].T[abs_arrival];
				t[x].T[abs_arrival]=t[x+1].T[abs_arrival];
				t[x+1].T[abs_arrival]=temp;

				temp=t[x].T[execution_copy];
				t[x].T[execution_copy]=t[x+1].T[execution_copy];
				t[x+1].T[execution_copy]=temp;

				temp=t[x].T[abs_deadline];
				t[x].T[abs_deadline]=t[x+1].T[abs_deadline];
				t[x+1].T[abs_deadline]=temp;

				temp=t[x].T[Value];
				t[x].T[Value]=t[x+1].T[Value];
				t[x+1].T[Value]=temp;

				temp=t[x].T[actual_id];
				t[x].T[actual_id]=t[x+1].T[actual_id];
				t[x+1].T[actual_id]=temp;

				temp1=t[x].value_density;
				t[x].value_density=t[x+1].value_density;
				t[x+1].value_density=temp1;

				temp=t[x].instance;
				t[x].instance=t[x+1].instance;
				t[x+1].instance=temp;

				temp=t[x].alive;
				t[x].alive=t[x+1].alive;
				t[x+1].alive=temp;

			}
		}

}

//Printing the task table after sorting a/c to EDF:
/*
	printf("\nAfter sorting according to deadline:\n");

	printf ("\nSr. No.  Task_label  Arrival  Execution  Deadline   Period    Value  Value Density");


    for (x = 0; x < n; x++)
    {
        printf ("\n   %d    \t%d       %d     \t %d   \t  %d    \t%d    \t %d    \t %f    \n", x+1, t[x].T[actual_id],  t[x].T[arrival], t[x].T[execution], t[x].T[deadline], t[x].T[period], t[x].T[Value], t[x].value_density);
    } 
*/

	while(timer<=simulation_time)
	{
		if(interrupt_check(t,timer,n))
			{
				//Get the task id of the Highest value density task
				 //Value_task_id = max(t,n,Value);
				 Value_task_id = max(t,n,*value_density);
				 active_task_id = Value_task_id;
			//	 printf("HELLLL000 %d\n",active_task_id);
			
			}
		int i;
		for(i=0;i<n;i++)
            {
            if(t[i].T[execution_copy]>=t[i].T[abs_deadline]-timer&&timer!=t[i].T[abs_arrival]&&t[i].alive!=0&&i!=active_task_id)	
                {
                drop[i]++;	
                fprintf(filepointer2,"Task %d dropped\n", t[i].T[actual_id]);
				//printf("Task %d dropped\n", t[i].T[actual_id]);
            	t[i].instance++;
                t[i].alive = 0;
            	exec_time_copy(t,i,CURRENT);
                abs_arr_new(t,i,t[i].instance,CURRENT);
                abs_dead_new(t,i,CURRENT);
                }
            }

			if(active_task_id==IDLE_TASK_ID)
		    {
		      fprintf(filepointer2,"%d  Idle\n", timer);
			  //printf("%d  Idle\n", timer);
		      sched[timer]=0;
		    }

		    if(active_task_id!=IDLE_TASK_ID)
		    {
				if(t[active_task_id].T[execution_copy]!=0)
		    	{
		    	if (t[active_task_id].T[execution_copy]==t[active_task_id].T[execution])
				{
		    		fprintf(filepointer2,"%d  Task %d started\n", timer,t[active_task_id].T[actual_id]);
					//printf("%d  Task %d started\n", timer,t[active_task_id].T[actual_id]);		
				}
		    	else
		    	 	fprintf(filepointer2,"%d  Task %d\n", timer,t[active_task_id].T[actual_id]);
					//printf("%d  Task %d\n", timer,t[active_task_id].T[actual_id]);
		    	 	t[active_task_id].T[execution_copy]--;
		    	 	sched[timer]=t[active_task_id].T[actual_id];
		    	 	int i;
		    		for(i=0;i<n;i++)
		    	 	{
		    	 	if (sched[timer]==i+1)
		    	 	count[i]++;
		    	 	}
		    	}

		    if(timer>0)
		    {
		    	if(sched[timer-1]!=sched[timer]&&sched[timer]!=0&&sched[timer-1]!=0)
		    	{
		    	 	if(sched[timer-1]!=sched[timer-t[sched[timer-1]-1].T[execution]])
		    	 	{
		    	 		preempt[sched[timer-1]-1]++;
   						fprintf(filepointer2,"Task %d pre-empted\n", sched[timer-1]);
						//printf("Task %d pre-empted\n", sched[timer-1]);
					}
   					if(sched[timer-1]==sched[timer-t[sched[timer-1]-1].T[execution]] && count[sched[timer-1]-1]%t[sched[timer-1]-1].T[execution]!=0)
		    	 	{
		    	 		preempt[sched[timer-1]-1]++;
   						fprintf(filepointer2,"Task %d pre-empted\n", sched[timer-1]);
						//printf("Task %d pre-empted\n", sched[timer-1]);
					}
		    	}
		    }

		    if(t[active_task_id].T[execution_copy]==0)
		    {
		    	t[active_task_id].instance++;
		    	t[active_task_id].alive = 0;
		    	exec_time_copy(t,active_task_id,CURRENT);
		    	abs_arr_new(t,active_task_id,t[active_task_id].instance,CURRENT);
		    	abs_dead_new(t,active_task_id,CURRENT);
		    	active_task_id = max(t,n,*value_density);
			}
			}
		    ++timer;
	}
	free(t);
	int i;
	int totalpre=0;
	int totaldrop=0;

	for (i=0;i<n;i++)
	{
	fprintf(filepointer2,"%d times Task%d got pre-empted\n",preempt[i],i+1);
	//printf("%d times Task%d got pre-empted\n",preempt[i],i+1);
	totalpre=totalpre+preempt[i];
	}

	for (i=0;i<n;i++)
	{
	fprintf(filepointer2,"%d times Task%d got dropped\n",drop[i],i+1);
	//printf("%d times Task%d got dropped\n",drop[i],i+1);
	totaldrop=totaldrop+drop[i];
	}
	
	for (i=0;i<n;i++)
	{
	fprintf(filepointer2,"For %d time units Task%d occurred\n",count[i],i+1);
	//printf("For %d time units Task%d occurred\n",count[i],i+1);
	}
	
	fprintf(filepointer2,"%d total pre-emptions in the given Task set\n",totalpre);
	//printf("%d total pre-emptions in the given Task set\n",totalpre);
	fprintf(filepointer2,"%d total drops in the given Task set\n",totaldrop);
	//printf("%d total drops in the given Task set\n",totaldrop);
	fclose(filepointer2);

	return 0;
}


