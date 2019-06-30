#include<stdio.h>
#include<stdlib.h>
#include"sched_def.h"

int timer=0;

int main()
{
task *t;
aperiodic *ap;
int n,a_n,hyper_period,resp_time=0;
float cpu_utilization;
float avg_resp_time;
FILE* filepointer;
	char line[1025];
	char value[10];
	line[1024]='\0';
	int label;
	filepointer=fopen("/home/parth/Desktop/rts_project1/rm_deferrable/question2_taskset.txt","r");	/*put the path to the input file here*/
if (filepointer==NULL)
{
fprintf(stderr,"Error: input file cannot be opened - access denies\n");
exit(1);
}
if(fgets(line,1024,filepointer)!=NULL)
{
if (line[1024]!='\0')
{
fprintf(stderr,"Error: Line in file exceeding length\n");
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
int active_task_id=n+5;
a_n=task_inputs(t,n,filepointer);
int a_n_copy=a_n;
int aperiodic_task_id=a_n+5;
ap=malloc(a_n*sizeof(aperiodic));
int simulation_time=aperiodic_task_input(ap,a_n,filepointer);
cpu_utilization = utilization(t,n);

hyper_period=hyperperiod(t,n);

exec_time_copy(t,n,ALL);
abs_arr_new(t,n,0,ALL);
abs_dead_new(t,n,ALL);
int count[n];
int k;
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
filepointer2=fopen("/home/parth/Desktop/rts_project1/rm_deferrable/defoutput.txt","w");	/*put path to the output file here*/
if (filepointer2==NULL)
{
fprintf(stderr,"Error: input file cannot be opened - access denies\n");
exit(1);
}

	while(timer<= simulation_time)
	  { 


			if(a_n_copy==0)
			{
				if(interrupt_check(t,timer,n-1))
			 			{
		    	 			active_task_id = min(t,n-1,period);
			 			}
			}
			 else
			 {
			 if(interrupt_check(t,timer,n))
			 {
		    	 active_task_id = min(t,n,period);
			 }
			}



			 
			 //check for deferrable server
             if(t[active_task_id].T[def]==1 && a_n_copy>0)
                 {
                 if(aperiodic_interrupt(ap,timer,a_n))
                     {
                     aperiodic_task_id = min_aperiodic(ap,a_n,ap_arrival);
                     if (aperiodic_task_id==IDLE_TASK_ID)
                     {
                         t[active_task_id].instance++;
                     t[active_task_id].alive = 0;
                         exec_time_copy(t,active_task_id,CURRENT);
                     abs_arr_new(t,active_task_id,t[active_task_id].instance,CURRENT);
                     abs_dead_new(t,active_task_id,CURRENT);
                         active_task_id = min(t,n-1,period);
                     }

                 }

                 else
                     {
                     if(interrupt_check(t,timer,n-1))
                         {
                             active_task_id = min(t,n-1,period);
                         }
                     }

                     if(ap[aperiodic_task_id].A[ap_execution]==0 && aperiodic_task_id!=IDLE_TASK_ID)
                     {
                         a_n_copy--;
                         if (a_n_copy==0)
                         {
                         t[active_task_id].T[def]=0;
                         t[active_task_id].T[execution_copy]=0;
                         }   
                     ap[aperiodic_task_id].alive=0;
                     resp_time += timer-ap[aperiodic_task_id].A[ap_arrival];
                     if(aperiodic_interrupt(ap,timer,a_n))
                     {
                     aperiodic_task_id = min_aperiodic(ap,a_n,ap_arrival);
                     if (aperiodic_task_id==IDLE_TASK_ID)
                     {
                         t[active_task_id].instance++;
                     t[active_task_id].alive = 0;
                         exec_time_copy(t,active_task_id,CURRENT);
                     abs_arr_new(t,active_task_id,t[active_task_id].instance,CURRENT);
                     abs_dead_new(t,active_task_id,CURRENT);
                         active_task_id = min(t,n-1,period);
                     }
                     }
                 else
                     {
                     if(interrupt_check(t,timer,n-1))
                         {
                             active_task_id = min(t,n-1,period);
                         }
                     }
                     }
                 }



			 int i;
			 for(i=0;i<n;i++)
                     {
                     if(t[i].T[execution_copy]>=t[i].T[abs_deadline]-timer&&timer!=t[i].T[abs_arrival]&&t[i].alive!=0&&i!=active_task_id)
                         {
                         drop[i]++;	
                         fprintf(filepointer2,"Task %d dropped\n", i+1);
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
		      sched[timer]=0;
		    }

		     if(active_task_id!=IDLE_TASK_ID)
		     {

		    	 if(t[active_task_id].T[execution_copy]!=0)
		    	 	 {
		    	 	 if(t[active_task_id].T[def]==1 && a_n_copy>0)
		    	 	 {
		    	 	 	ap[aperiodic_task_id].A[ap_execution]--;
		    	 	 	t[active_task_id].T[execution_copy]--;
		    	 	 fprintf(filepointer2,"%d  Aperiodic Task %d\n", timer,aperiodic_task_id+1);
		    	 	 sched[timer]=active_task_id+1;
		    	 	 int i;
		    	 	 for(i=0;i<n;i++)
		    	 	 {
		    	 	 	if (sched[timer]==i+1)
		    	 	 		count[i]++;
		    	 	 }
		    	 	 }
		    	 	 else
		    	 	 {
		    	 	 	t[active_task_id].T[execution_copy]--;
		    	 	 	fprintf(filepointer2,"%d  Task %d\n", timer,active_task_id+1);
		    	 	 	sched[timer]=active_task_id+1;
		    	 	 	int i;
		    	 	 for(i=0;i<n;i++)
		    	 	 {
		    	 	 	if (sched[timer]==i+1)
		    	 	 		count[i]++;
		    	 	 }
		    	 	 }
		    	 	 }
		    	 	 
		    	 	 if(timer>0)
		    	 {
		    	 if(sched[timer-1]!=sched[timer]&&sched[timer]!=0&&sched[timer-1]!=0)
		    	 	{
		    	 		if(sched[timer-1]!=sched[timer-t[sched[timer-1]-1].T[execution]])
		    	 			{
		    	 				preempt[sched[timer-1]-1]++;
   						fprintf(filepointer2,"Task %d pre-empted\n", sched[timer-1]);}
   						if(sched[timer-1]==sched[timer-t[sched[timer-1]-1].T[execution]] && count[sched[timer-1]-1]%t[sched[timer-1]-1].T[execution]!=0)
		    	 			{
		    	 				preempt[sched[timer-1]-1]++;
   						fprintf(filepointer2,"Task %d pre-empted\n", sched[timer-1]);}
		    	 	}
		    	 }
		    	 	
		    	 	
		    	 if(t[active_task_id].T[execution_copy]==0)
		    	 	{
		    	 	t[active_task_id].instance++;
		    	 	t[active_task_id].alive = 0;
		    	 	exec_time_copy(t,active_task_id,CURRENT);
		    	 	abs_arr_new(t,active_task_id,t[active_task_id].instance,CURRENT);
		    	 	abs_dead_new(t,active_task_id,CURRENT);
		    	 	if(a_n_copy>0)
		    	 	{
		    	 	active_task_id = min(t,n,period);
				}
				else
				{
				active_task_id = min(t,n-1,period);
				}
		    	 	}


		     }
		    
		     ++timer;
		 }
free(t);
free(ap);
int i;
int totalpre=0;
int totaldrop=0;
for (i=0;i<n;i++)
{
fprintf(filepointer2,"%d times Task%d got pre-empted\n",preempt[i],i+1);
totalpre=totalpre+preempt[i];
}
for (i=0;i<n;i++)
{
fprintf(filepointer2,"%d times Task%d got dropped\n",drop[i],i+1);
totaldrop=totaldrop+drop[i];
}
fprintf(filepointer2,"%d total pre-emptions in the given Task set\n",totalpre);
fprintf(filepointer2,"%d total drops in the given Task set\n",totaldrop);
avg_resp_time=resp_time/a_n;
fprintf(filepointer2,"Average Response Time = %f\n",avg_resp_time);
fclose(filepointer2);

return 0;
}

