#include <stdio.h> 
#include <string.h> 
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>

struct Timer
{
	struct timeval time_start, time_end;
	short int running;
	long seconds;
};

void Start(struct Timer *t)
{
	(*t).seconds = 0.0;
	gettimeofday(&((*t).time_start), NULL);
	(*t).running = 1;
}

void Stop(struct Timer *t) //returns time in milli-secs
{
	if ((*t).running == 0) { (*t).seconds = 0.0; return; }
	gettimeofday(&((*t).time_end), NULL);
	long secs, uSecs;

	secs  = (*t).time_end.tv_sec  - (*t).time_start.tv_sec;
	uSecs = (*t).time_end.tv_usec - (*t).time_start.tv_usec;
	(*t).seconds =((secs) * 1000 + uSecs/1000.0) + 0.5;
	(*t).running = 0;
}

float Elapsed(struct Timer *t)
{
	if ((*t).running == 1) Stop(t);
	return (*t).seconds;
}




int main()
{

	int row1,col1,row2,col2,i=0,j=0,k=0;
	again:
	printf("Enter Dimensions for Matrix A:\n");
	printf("Enter Row=");
	scanf("%d",&row1);    
	printf("Enter Column=");
	scanf("%d",&col1);

	printf("Enter Dimensions for Matrix B:\n");
	printf("Enter Row=");
	scanf("%d",&row2);    
	printf("Enter Column=");
	scanf("%d",&col2);

	if(col1==row2)
	{
		int **a = (int **)malloc(row1 * sizeof(int *));
    		for (int i=0; i<row1; i++)
         		a[i] = (int *)malloc(col1 * sizeof(int));

		int **b = (int **)malloc(row2 * sizeof(int *));
    		for (int i=0; i<row2; i++)
         		b[i] = (int *)malloc(col2 * sizeof(int));

		int **mul = (int **)malloc(row1 * sizeof(int *));
    		for (int i=0; i<row1; i++)
         		mul[i] = (int *)malloc(col2 * sizeof(int));

		srand(time(0));

		for(i=0;i<row1;i++)
		{
			for(j=0;j<col1;j++)
			{
				a[i][j]=rand()%100;
			}
		}
		
		for(i=0;i<row2;i++)
		{
			for(j=0;j<col2;j++)
			{
				b[i][j]=rand()%100;
			}
		}

		for(i=0;i<row1;i++)
		{
			for(j=0;j<col2;j++)
			{
				mul[i][j]=0;
			}
		}


		//printf("enter the second matrix element=\n");
		//for(int i=0;i<row1;i++)
		//{
		//for(int j=0;j<col1;j++)
		//{
		//scanf("%d",&b[i][j]);
		//}
		//}    


		//starting the timer
		struct Timer timer;
		Start(&timer);

		//multiply of the matrix;
		for(i=0;i<row1;i++)    
		{
			for(j=0;j<col2;j++)    
			{
				for(k=0;k<row2;k++)
				{
					mul[i][j]+=a[i][k]*b[k][j];
				}
			}
		}

		//stop timer and print time in miliseconds
		Stop(&timer);
		printf("\nTime elapsed = %g ms\n", Elapsed(&timer));
	

		//for printing of matrix
		if(row1<10)
		{
			//Matrix a   
			printf("Matrix A\n"); 
			for(int i=0;i<row1;i++)    
			{    
				for(int j=0;j<col1;j++)    
				{    
					printf("%d\t",a[i][j]);    
				}    
				printf("\n");    
			}    

			//Matrix b   
			printf("Matrix B\n"); 
			for(int i=0;i<row2;i++)    
			{    
				for(int j=0;j<col2;j++)    
				{    
					printf("%d\t",b[i][j]);    
				}    
				printf("\n");    
			}    

			printf("\n");

			//for printing result
			printf("Resultant Matrix\n");
			for(int i=0;i<row1;i++)    
			{    
				for(int j=0;j<col2;j++)    
				{    
					printf("%d\t",mul[i][j]);
				}    
				printf("\n");    
			}    

		} 
	}
	else
	{
		system("clear");
		printf("Multiplication not Possible Due to Dimensions\n");
		printf("Try Again\n");
		goto again;

	}

return 0;

}
