// C program to implement Round Robin CPU Scheduling Algorithm 
#include<stdio.h>
#include<stdbool.h>  //for bool datatype
struct process_struct
{
  int pid;
  int at;
  int bt;
  int ct,wt,tat,rt,start_time;
  int bt_remaining;
}ps[100];

int findmax(int a, int b)
{
    return a>b?a:b;
}
void sortart(struct process_struct *p,int n)
{
       int i,j;
       struct process_struct temp;
       for(i=0;i<n;i++)
       {
              for(j=i+1;j<n;j++)
              {
                     if(p[i].at > p[j].at)
                     {
                           temp = p[i];
                           p[i] = p[j];
                           p[j] = temp;
                     }
              }
       }
       return;
}
int main()
{
    
    int n,index;
    bool visited[100]={false};
    int current_time = 0;
    int completed = 0,tq;
    printf("Enter total number of processes: ");
    scanf("%d",&n);    
    int queue[100],front=-1,rear=-1;
    float sum_tat=0,sum_wt=0,sum_rt=0;
    for(int i=0;i<n;i++)
    {
        printf("\nEnter Process %d Arrival Time: ",i);
        scanf("%d",&ps[i].at);
        ps[i].pid=i;
    }
    
    for(int i=0;i<n;i++)
    {
       printf("\nEnter Process %d Burst Time: ",i); 
       scanf("%d",&ps[i].bt);
       ps[i].bt_remaining= ps[i].bt;
    }
    
    printf("\nEnter time quantum: ");
    scanf("%d",&tq);
    
    //sort structure on the basis of Arrival time in increasing order
     sortart(ps,n);
    front=rear=0;
    queue[rear]=0; //initialize the queue with the first process  index  
    visited[0] = true;

    while(completed != n) 
    {
      index = queue[front];//taking out the index of process from queue which is present in the front      
      front++;
      
      if(ps[index].bt_remaining == ps[index].bt)// to check if the process is arriving for the first time
      {

            ps[index].start_time = findmax(current_time,ps[index].at);
            current_time =  ps[index].start_time;
      }

      if(ps[index].bt_remaining-tq > 0)//to check if process is not going to finish in current time quantum ie. bt_remaining is greater than time quantum
      {    
         
            ps[index].bt_remaining -= tq;
            current_time += tq;
      }
      else                        // the process will enter into else if process bt_remaining is less than the time quantum
      
          
            current_time += ps[index].bt_remaining;
            //  printf(" %d P%d  ",current_time,index);
            ps[index].bt_remaining = 0;
            completed++;

            ps[index].ct = current_time;
            ps[index].tat = ps[index].ct - ps[index].at;
            ps[index].wt = ps[index].tat - ps[index].bt;
            ps[index].rt = ps[index].start_time - ps[index].at;

            sum_tat += ps[index].tat;
            sum_wt += ps[index].wt;
            sum_rt += ps[index].rt;
             
      }
       //check which new Processes needs to be pushed to Ready Queue from Input list
      for(int i = 1; i < n; i++) 
      {
          if(ps[i].bt_remaining > 0 && ps[i].at <= current_time && visited[i] == false) 
          {
           queue[++rear]=i;
            visited[i] = true;
          }
      }
      //check if Process on CPU needs to be pushed to Ready Queue
      if( ps[index].bt_remaining> 0) 
          queue[++rear]=index;
    
            
      //if queue is empty, just add one process from list, whose remaining burst time > 0
      if(front>rear)
      {
          for(int i = 1; i < n; i++)
          {
            if(ps[i].bt_remaining > 0)
            {
              queue[rear++]=i;
              visited[i] = true;
              break;
            }
          }
      }
   } //end of while
   
  //sort so that process ID in output comes in Original order (just for interactivity- Not needed otherwise)  
  //Output
  printf("\nProcess No.\tAT\tCPU Burst Time\tStart Time\tCT\tTAT\tWT\tRT\n");
  for(int i=0;i<n;i++)
    printf("%d\t\t%d\t%d\t\t%d\t\t%d\t%d\t%d\t%d\n",i,ps[i].at,ps[i].bt,ps[i].start_time,ps[i].ct,ps[i].tat,ps[i].wt,ps[i].rt);
  printf("\n");    

  printf("\nAverage Turn Around time= %.2f",(float)sum_tat/n);
  printf("\nAverage Waiting Time= %.2f",(float)sum_wt/n);
  printf("\nAverage Response Time= %.2f",(float)sum_rt/n);    
  return 0;
}