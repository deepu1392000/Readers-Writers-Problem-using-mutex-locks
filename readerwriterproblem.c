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
	printf("\n\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n\n");
	printf("The Data read by reader is:-");
	printf("%s",shared_attribute);
	printf("\n-----------------------------------------------------------------\n");
	printf("\n Number of readers in queue are:- %d\n",(reader_count-1));
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
	sleep(10);
	printf("\n\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n\n");
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
	int i;
	pthread_t threads[20];
	pthread_mutex_init(&rl,NULL);
	pthread_mutex_init(&wl,NULL);
	for(i=0;i<5;i++)
	{
		pthread_create(&(threads[i]),NULL,read_function,NULL);
	}
	for(i=5;i<10;i++)
	{
		pthread_create(&(threads[5]),NULL,write_function,NULL);
	}
	for(i=10;i<15;i++)
	{
		pthread_create(&(threads[i]),NULL,read_function,NULL);
	}
	for(i=15;i<20;i++)
	{
		pthread_create(&(threads[5]),NULL,write_function,NULL);
	}
	for(i=0;i<20;i++)
	{
		pthread_join(threads[i],NULL);
	}
	printf("FINAL DATA OF SHARED VARIABLE IS:-\t");
	printf("%s\n",shared_attribute);
	pthread_mutex_destroy(&rl);
	pthread_mutex_destroy(&wl);
	return 0;
}
