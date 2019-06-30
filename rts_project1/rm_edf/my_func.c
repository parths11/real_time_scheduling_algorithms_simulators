#include<stdio.h>
#include<stdlib.h>
#include"sched.h"

int task_inputs(task *t1,int n,FILE* fp)
{
	int result=0;
	char line[1025];
	char value[10];
	line[1024]='\0';
	int label;
while(fgets(line,1024,fp)!=NULL)
{
int success=0;
if (line[1024]!='\0')
{
fprintf(stderr,"Error: Line in file exceeding length\n");
exit(1);
}
else
{
int i=0;
while(line[i]!='\n')
{
if(success==0)
{
	if (line[0]=='s')
	{
		int p=0;
		i=i+2;
		while (line[i]!=32)
	{value[p]=line[i];
	i++;
	p++;}
	value[p]='\0';
	result=atoi(value);
	break;	
	}
int p=0;
while(line[i]!=32)
{
value[p]=line[i];
i++;
p++;
}
value[p]='\0';
label=atoi(value);
success++;
i++;}

if(success==1 || success==3 || success==5)
{
while(line[i]==32)
i++;
success++;
}

if(success==2)
{int s=0;
while(line[i]!=32)
{
value[s]=line[i];
i++;
s++;
}
value[s]='\0';
t1->T[execution]=atoi(value);
success++;
i++;}

if(success==4)
{int u=0;
while(line[i]!=32)
{
value[u]=line[i];
i++;
u++;
}
value[u]='\0';
t1->T[period]=atoi(value);
success++;
i++;}

if(success==6)
{int u=0;
while(line[i]!=32)
{
value[u]=line[i];
i++;
u++;
}
value[u]='\0';
t1->T[deadline]=atoi(value);
success++;
i++;
}
if (success==7)
{
	t1->T[arrival]=0;
	t1->T[abs_arrival]=0;
	t1->T[execution_copy]=0;
	t1->T[abs_deadline]=0;
	t1->instance =0;
	t1->alive = 0;
	t1++;
	break;
}
}
}
}
fclose(fp);
return result;
}

int hyperperiod(task *t1,int n)
{
	int i=0,ht,a[10];
	while(i<n)

		{
		a[i]=t1->T[period];
		t1++;
		i++;
		}
	ht=lcm(a,n);

	return ht;
}

int gcd(int a, int b)
{
  if (b == 0)
	  return a;
  else
  return gcd(b, a%b);
}

int lcm(int *a, int n)
{
  int res = 1, i;
  for (i = 0; i < n; i++)
  {
    res = res*a[i]/gcd(res, a[i]);
  }
  return res;
}



int interrupt_check(task *t1,int tmr,int n)
{
int i=0,n1=0,a=0;
task *t1_copy;
t1_copy=t1;
	while(i<n)
	{
		if(tmr == t1->T[abs_arrival])
			{
			t1->alive = 1;
			a++;
			}
		t1++;
		i++;
	}

	t1 =t1_copy;
	i=0;

	while(i<n)
	{
		if(t1->alive==0)
			n1++;
			t1++;
			i++;
	}

	if(n1==n || a!=0)
	{
		return 1;
	}

	return 0;
}

void abs_dead_new(task *t1,int n,int all)
{
int i=0;
		if(all)
		{
			while(i<n)
			{
				t1->T[abs_deadline] = t1->T[deadline] + t1->T[abs_arrival];
				t1++;
				i++;
			}
		}
		else
		{
		t1+=n;
		t1->T[abs_deadline] = t1->T[deadline] + t1->T[abs_arrival];
		}

}

void abs_arr_new(task *t1,int n,int k,int all)
{
int i=0;
		if(all)
		{
			while(i<n)
			{
				t1->T[abs_arrival] = t1->T[arrival] + k*(t1->T[period]);
				t1++;
				i++;
			}
		}
		else
		{
		t1+=n;
		t1->T[abs_arrival] = t1->T[arrival] + k* (t1->T[period]);
		}

}

void exec_time_copy(task *t1,int n,int all)
{
	int i=0;
	if(all)
	{
		while(i<n)
		{
			t1->T[execution_copy] = t1->T[execution];
			t1++;
			i++;
		}
	}
	else
	{
		t1+=n;
		t1->T[execution_copy] = t1->T[execution];
	}
}


int min(task *t1,int n,int p)
{
	int i=0,min=0x7FFF,task_id=IDLE_TASK_ID;
	while(i<n)
	{
		if(min>t1->T[p] && t1->alive==1)
		{
			min=t1->T[p];
			task_id=i;
		}
		t1++;
		i++;
	}
	return task_id;
}


float utilization(task *t1,int n)
{
	int i=0;
	float cu=0;
	while(i<n)
	{
		cu = cu + (float)t1->T[execution]/(float)t1->T[deadline];
		t1++;
		i++;
	}
	return cu;

}

