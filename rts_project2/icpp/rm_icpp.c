#include<stdio.h>
#include<stdlib.h>
#include"sched.h"


float timer=0;

int main()
{
task *t;
resource *r;
int n,hyper_period,active_task_id;
float cpu_utilization;
FILE* filepointer;
	char line[1025];
	char value[10];
	line[1024]='\0';
	int label;
	filepointer=fopen("question1_taskset.txt","r"); /*put the path to input file here*/
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
int simulation_time=task_inputs(t,n,filepointer);
cpu_utilization = utilization(t,n);
hyper_period=hyperperiod(t,n);
exec_time_copy(t,n,ALL);
abs_arr_new(t,n,0,ALL);
abs_dead_new(t,n,ALL);
int count[n];
int k;
int sched[(simulation_time*4)+1];
for(k=0;k<(simulation_time*4)+1;k++)
	sched[k]=0;
for(k=0;k<n;k++)
	count[k]=0;
int preempt[n];
for(k=0;k<n;k++)
	preempt[k]=0;
int drop[n];
for(k=0;k<n;k++)
	drop[k]=0;
int tasks[n];
for(k=0;k<n;k++)
	tasks[k]=k;
	
//for(k=0;k<n;k++)
	//printf("period %d is %d\n",k+1,t[k].T[period]);

int i=0,j=0,a=0;

for (i = 0; i < n; i++) 

        {
            for (j = i + 1 ; j < n; j++)

            {
                if (t[tasks[j]].T[period] < t[tasks[i]].T[period]) 

                {
                    a =  tasks[i];

                    tasks[i] = tasks[j];

                    tasks[j] = a;
                }
            }
        }
        
        //printf("%d %d %d %d %d\n",tasks[0],tasks[1],tasks[2],tasks[3],tasks[4]);
        
for (i = 0; i < n; i++)
	{
	t[tasks[i]].T[priority] = i;
	}


for (i = 0; i < n; i++)
	{
	t[i].T[priority_copy] = t[i].T[priority];
	}

	
/*for (i = 0; i < n; i++)
	{
	//printf("task %d has priority %d\n",i+1, t[i].T[priority]+1);
	}*/

FILE* filepointer1;
	int res=0;
	filepointer1=fopen("resource.txt","r"); /*put the path to input file here*/
if (filepointer1==NULL)
{
fprintf(stderr,"Error: input file cannot be opened - access denies\n");
exit(1);
}
if(fgets(line,1024,filepointer1)!=NULL)
{
	fgets(line,1024,filepointer1);
	int i=0;
	while(line[i]!='\n')
	{
	value[i]=line[i];
	i++;
	}
	value[i]='\0';
	res=atoi(value);
}

r=malloc(res*sizeof(resource));
resource_input(r,filepointer1,t,n);

int x,y;
for(x=0;x<res;x++)
{
	for(y=0;y<n;y++)
	{
		if(t[y].T[resource_used]==x && t[y].T[priority]<r[x].R[priority_ceiling])
		{
			r[x].R[priority_ceiling]=t[y].T[priority];
		}
	}
	//printf("Resource%d PC: %d\n",x,r[x].R[priority_ceiling]);
}




FILE* filepointer2;
filepointer2=fopen("schedule.txt","w"); /*put the path to output file here*/
if (filepointer2==NULL)
{
fprintf(stderr,"Error: output file cannot be opened - access denies\n");
exit(1);
}

FILE* filepointer3;
filepointer3=fopen("deadline_misses.txt","w"); /*put the path to output file here*/
if (filepointer3==NULL)
{
fprintf(stderr,"Error: output file cannot be opened - access denies\n");
exit(1);
}

FILE *opfiles[n];
for (int i = 0; i < n; i++)
{
    char filename[20];
    sprintf(filename, "output_%d.txt", i);
    opfiles[i] = fopen(filename, "w");
    fprintf(opfiles[i],"lock_instant, curr_pio, prio_inherit\n");
    if (opfiles[i]==NULL)
	{
	fprintf(stderr,"Error: output file cannot be opened - access denies\n");
	exit(1);
	}
}

int yeah=0,nx=0,ax=0,o=0;

fprintf(filepointer2,"CPU Utilization %f\n",cpu_utilization);

		if(cpu_utilization<1)
				fprintf(filepointer2,"Tasks can be scheduled\n");
			else
				fprintf(filepointer2,"Schedule is not feasible\n");

	while(timer<=simulation_time)
	  {


			 if(interrupt_check(t,timer,n))
			 {
		    	 active_task_id = min(t,n,priority);
			 }
			 
			 
			 if(t[active_task_id].T[critical_start]==1 && t[active_task_id].critical_execution_copy==t[active_task_id].critical_execution)
			 {
			 	if(r[t[active_task_id].T[resource_used]].lock==0)
				{
				int i,a=0,nx=0,ax=0;
					for(i=0;i<res;i++)
					{
						if(r[i].lock==1)
							ax++;
					}
					
					i=0;
	
					for(i=0;i<res;i++)
					{
						if(t[active_task_id].T[priority]<r[i].R[priority_ceiling] && r[i].lock==1)
							a++;
					}
					
					i=0;
	
					for(i=0;i<res;i++)
					{
						if(r[i].lock==0)
							nx++;
					}
	
					if(nx==res || a==ax)
					{
						o=0;
						o=r[t[active_task_id].T[resource_used]].R[priority_ceiling];
						t[tasks[o]].T[priority]=o+n;
						r[t[active_task_id].T[resource_used]].lock=1;
						r[t[active_task_id].T[resource_used]].task_exe = active_task_id;
						t[active_task_id].T[priority]=r[t[active_task_id].T[resource_used]].R[priority_ceiling];
						
						if(t[active_task_id].critical_execution_copy==t[active_task_id].critical_execution)
							fprintf(opfiles[active_task_id],"%f, %d, %d\n",timer,t[active_task_id].T[priority],tasks[o]);
					}
					else
					{
						active_task_id = min_sans(t,n,priority,active_task_id);
					}
				}
			 }


			 int i;
			 for(i=0;i<n;i++)
                     {
                     if(t[i].execution_copy>=t[i].T[abs_deadline]-timer&&timer!=t[i].T[abs_arrival]&&t[i].alive!=0&&i!=active_task_id)
                         {
                         drop[i]++;	
                         //fprintf(filepointer2,"Task %d dropped\n", i+1);
                         t[i].instance++;
                     t[i].alive = 0;
                     exec_time_copy(t,i,CURRENT);
                     abs_arr_new(t,i,t[i].instance,CURRENT);
                     abs_dead_new(t,i,CURRENT);
                     t[i].T[critical_start]=0;
		    r[t[i].T[resource_used]].lock=0;
		    t[i].critical_execution_copy=t[i].critical_execution;
                     
                         }
                     }



		     if(active_task_id==IDLE_TASK_ID)
		    {
		      fprintf(filepointer2,"%f  Idle\n", timer);
		      sched[(int)(timer*4)]=0;
		    }

		     if(active_task_id!=IDLE_TASK_ID)
		     {

		    	 if(t[active_task_id].execution_copy!=0)
		    	 	 {
		    	 	 	if(t[active_task_id].T[critical_start]==1)
		    	 	 	{
		    	 	 		fprintf(filepointer2,"%f  Critical %d\n", timer,active_task_id+1);
		    	 	 		t[active_task_id].critical_execution_copy-=0.25;
		    	 	 	}
		    	 	 	else
		    	 	 	{
		    	 	 	if (t[active_task_id].execution_copy==t[active_task_id].T[execution])
		    	 	 		fprintf(filepointer2,"%f  Task %d started\n", timer,active_task_id+1);	
		    	 	 	else
		    	 	 		fprintf(filepointer2,"%f  Task %d\n", timer,active_task_id+1);
		    	 	 	}
		    	 	 
		    	 	t[active_task_id].execution_copy-=0.25;
		    	 	 sched[(int)(timer*4)]=active_task_id+1;
		    	 	 int i;
		    	 	 for(i=0;i<n;i++)
		    	 	 {
		    	 	 	if (sched[(int)(timer*4)]==i+1)
		    	 	 		count[i]++;
		    	 	 }
		    	 	 }

		    	 	 if(timer>0)
		    	 {
		    	 if(sched[(int)(timer*4)-1]!=sched[(int)(timer*4)]&&sched[(int)(timer*4)]!=0&&sched[(int)(timer*4)-1]!=0)
		    	 	{
		    	 		if(sched[(int)(timer*4)-1]!=sched[(int)(timer*4)-t[sched[(int)(timer*4)-1]-1].T[execution]])
		    	 			{
		    	 				preempt[sched[(int)(timer*4)-1]-1]++;
   						//fprintf(filepointer2,"Task %d pre-empted\n", sched[(int)(timer*4)-1]);
   						}
   						if(sched[(int)(timer*4)-1]==sched[(int)(timer*4)-t[sched[(int)(timer*4)-1]-1].T[execution]] && count[sched[(int)(timer*4)-1]-1]%t[sched[(int)(timer*4)-1]-1].T[execution]!=0)
		    	 			{
		    	 				preempt[sched[(int)(timer*4)-1]-1]++;
   						//fprintf(filepointer2,"Task %d pre-empted\n", sched[(int)(timer*4)-1]);
   						}
		    	 	}
		    	 }

		    	if(t[active_task_id].execution_copy==0.75*(t[active_task_id].T[execution]))
		    	{
		    		t[active_task_id].T[critical_start]=1;
		    	}
		    	
		    	//fprintf(filepointer2,"at %f cricstart=%d timeleft:%f  %f\n",timer,t[active_task_id].T[critical_start],t[active_task_id].execution_copy,0.75*(t[active_task_id].T[execution]));
		    	
		    	if(t[active_task_id].critical_execution_copy==0)
		    	{
		    		if(t[active_task_id].critical_execution_copy==0)
		    		{
			    		t[active_task_id].T[critical_start]=0;
			    		r[t[active_task_id].T[resource_used]].lock=0;
			    		t[active_task_id].critical_execution_copy=t[active_task_id].critical_execution;
			    		r[t[active_task_id].T[resource_used]].task_exe=0;
			    		t[tasks[t[active_task_id].T[priority]]].T[priority]=t[active_task_id].T[priority];
			    		t[active_task_id].T[priority]=t[active_task_id].T[priority_copy];
		    		}
		    	}
		    	
		    	
		    	 if(t[active_task_id].execution_copy==0)
		    	 	{
		    	 	t[active_task_id].instance++;
		    	 	t[active_task_id].alive = 0;
		    	 	exec_time_copy(t,active_task_id,CURRENT);
		    	 	abs_arr_new(t,active_task_id,t[active_task_id].instance,CURRENT);
		    	 	abs_dead_new(t,active_task_id,CURRENT);
		    	 	active_task_id = min(t,n,priority);
				//cric_exec_copy(t,active_task_id);
		    	 	}


		     }
		     timer+=0.25;
		 }
free(t);
free(r);

int totalpre=0;
int totaldrop=0;
for (i=0;i<n;i++)
{
//fprintf(filepointer2,"%d times Task%d got pre-empted\n",preempt[i],i+1);
totalpre=totalpre+preempt[i];
}
for (i=0;i<n;i++)
{
fprintf(filepointer3,"%d %d\n",i,drop[i]);
totaldrop=totaldrop+drop[i];
}
for (i=0;i<n;i++)
{
//fprintf(filepointer2,"For %d time units Task%d occurred\n",count[i],i+1);
}
//fprintf(filepointer2,"%d total pre-emptions in the given Task set\n",totalpre);
fprintf(filepointer3,"%d total drops in the given Task set\n",totaldrop);
fclose(filepointer2);
fclose(filepointer3);
for(i=0;i<n;i++)
{
fclose(opfiles[i]);
}
return 0;
}

