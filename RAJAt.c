#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

struct Pro{ //structure to hold attributes of processes i.e Arrivaltime,Burst-time,Wait_time,TurnAround-time
	int Arrival_time,Burst_time,Wait_time,Turnaround_time;
	char name[4];
};
struct Pro initialize(int Arrival_time,int Burst_time,int name){ //Function to intialize the processes attributes
	struct Pro obj;//object of Pro
	obj.Burst_time = Burst_time;
	obj.Arrival_time = Arrival_time;
	sprintf(obj.name,"P%d",name+1);//defining name of Process by iteration using sprintf(string print)
	return obj;
}
int main(){
	//self improvement in the question 
	//Asking user for burst time and storing that in a file named CPU_BURST.txt
	FILE *fp = fopen("CPU_BURST.txt","w+");//open the file in update mode
	printf("Enter 5 burst time(integer) with a space \n ");
	rewind(fp);//bringing all the file pointer back to position 0
	char Burst[50];
	gets(Burst);
	fprintf(fp,"%s",Burst);//putting string in file
	fclose(fp);
	FILE *f = fopen("CPU_BURST.txt","r");//opening file in Read mode
	if(!f)//failsafe if file doesnt exist
		return -1*printf("FILE OPEN ERROR!\n");

    int d,i,j,Counter=0;//iterative counter for loops
    int *list = (int*)malloc(sizeof(int));//dyamically allocating interger type Array
    //inputs are space separated integers on a single line of a txt file located in the same directory
    while(EOF != fscanf(f,"%d ",&d ))//reading and storing burst time seprated by spaces
	{
    	list = (int*)realloc(list,(Counter+1)*sizeof(int));//reallocating Array size after each burst time
    	list[Counter++] = d;//counter=number of process
    }
    fclose(f);

	struct Pro P[Counter];//intializing Array of Pro for storing process
	for(i=0; i<Counter; i++)
		P[i] = initialize(0,list[i],i);
	//sorting the process according to their burst time
	//as all arrived at same time
	for(i=1; i<Counter; i++){
		for(j=0; j<Counter-i; j++){
			if(P[j].Burst_time>P[j+1].Burst_time){
				struct Pro temp = P[j];
				P[j] = P[j+1];
				P[j+1] = temp;
			}
		}
	}
	//after sorting we can apply FCFS which will result in SJF]
	printf("\nOrder : ");
	int elapsed_time=0;//counter to to maintain record of total time and dispatcher time switch
	for(i=0; i<Counter; i++){
		P[i].Wait_time = elapsed_time;//dispatcher switch time stored
		P[i].Turnaround_time= P[i].Wait_time+P[i].Burst_time;//calculating turnAround time
		elapsed_time += P[i].Burst_time;
		printf("%s ",P[i].name);
	}//printing process in sequence of their execution	
	printf("\n\n%7s|%8s|%6s|%5s|%s\n","PROCESS","ARRIVAL","BURST","WAIT","TURNAROUND");//pretty formatting output
	int ToTaL_WaitTime=0,ToTaL_TurnAroundTime=0;
	for(i=0; i<Counter; i++){//printing all the process in serial order with their Attributes
		ToTaL_WaitTime+=P[i].Wait_time;
		ToTaL_TurnAroundTime+=P[i].Turnaround_time;
		printf("%7s|%8d|%6d|%5d|%9d\n",P[i].name,P[i].Arrival_time,P[i].Burst_time,P[i].Wait_time,P[i].Turnaround_time);
	}
	printf("\nAverage Waiting Time     : %.2f\n",ToTaL_WaitTime*1.0/Counter);//Average waiting time
	printf("\nAverage Turn Around Time : %.2f\n",ToTaL_TurnAroundTime*1.0/Counter);//TurnAround Time
	return 0;
}
