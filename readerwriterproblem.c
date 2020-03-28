#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
char shared_attribute[250]="Hello all welcome to readers writers problem\n";
int reader_count=0;
pthread_mutex_t rl,wl;
void *read_function()
{
	if(reader_count==0)
	{
		pthread_mutex_lock(&wl);
	}
	reader_count++;
	pthread_mutex_lock(&rl);
	sleep(2);
	printf("\n\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
	printf("The Data read by reader is:-");
	printf("%s",shared_attribute);
	printf("\n-----------------------------------------------------------------\n");
	printf("\n Number of readers in queue are:- %d\n",reader_count);
	printf("\n-----------------------------------------------------------------\n");
	printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n\n\n");
	reader_count--;
	if(reader_count>0)
	{
		pthread_mutex_unlock(&rl);
	}
	else
	{
		reader_count=0;
		pthread_mutex_unlock(&rl);
		pthread_mutex_unlock(&wl);
	}
}
void *write_function()
{
	pthread_mutex_lock(&wl);
	printf("\n\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
	printf("Enter the data of your wish\n");
	scanf("%s",shared_attribute);
	printf("\n-----------------------------------------------------------------\n");
	printf("Number of readers in queue are:- %d\n",reader_count);
	printf("\n-----------------------------------------------------------------\n");
	pthread_mutex_unlock(&wl);
	printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n\n\n");
	fflush(stdin);
}
int main()
{
	int instruction_count,i;
	//printf("Enter the number of instructions:-");
	//scanf("%d",&instruction_count);
	instruction_count=5;
	pthread_t threads[instruction_count];
	pthread_mutex_init(&rl,NULL);
	pthread_mutex_init(&wl,NULL);
	pthread_create(&(threads[0]),NULL,read_function,NULL);
	pthread_create(&(threads[1]),NULL,read_function,NULL);
	pthread_create(&(threads[2]),NULL,write_function,NULL);
	pthread_create(&(threads[3]),NULL,read_function,NULL);
	pthread_create(&(threads[4]),NULL,read_function,NULL);
	for(i=0;i<instruction_count;i++)
	{
		pthread_join(threads[i],NULL);
	}
	printf("FINAL DATA OF SHARED VARIABLE IS:-\t");
	printf("%s\n",shared_attribute);
	pthread_mutex_destroy(&rl);
	pthread_mutex_destroy(&wl);
	return 0;
}
