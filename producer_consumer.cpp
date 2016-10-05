#include"buffer.h"
#include<iostream>
#include<string>
#include<cstdlib>
#include<unistd.h>
#include<csignal>
#include<pthread.h>
#include<semaphore.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
using namespace std;
//the buffer
buffer my_buffer;
const int VALUE_MAX=1000;
const int RAND_MAX_VALUE=10;
int run_time, pro, con;
pthread_mutex_t mutex;
sem_t full;
sem_t empty;

//this is what a thread runs
void* run (void* parameters)
{
	//always run
	while(true)
	{
		int args=*(int*)parameters;
		//is a producer
		if(args<pro)
		{
			int input=rand()%VALUE_MAX;
			
			sem_wait(&empty);
			pthread_mutex_lock(&mutex);
			
			//critical section
			my_buffer.insert_item(input);
			cout<<"thread "<<pthread_self()<<" put in "<<input<<endl; 
			
			pthread_mutex_unlock(&mutex);
			sem_post(&full);
			
		}
		//is a consumer
		else
		{
			sem_wait(&full);
			pthread_mutex_lock(&mutex);
			
			//critical section
			cout<<"thread "<<pthread_self()<<" took out ";
			my_buffer.remove_item(); 
			cout<<endl;
			
			pthread_mutex_unlock(&mutex);
			sem_post(&empty);
		}
	}
}

int main(int argc, char** argv)
{
	//extract args
	run_time=atoi(argv[1]);
	pro=atoi(argv[2]);
	con=atoi(argv[3]);
	//set up random number maker
	srand(time(NULL));
	//init mutex and semaphore
	pthread_mutex_init(&mutex, NULL);
	sem_init(&full, 0, 0);
	sem_init(&empty, 0, 5);
	
	//the array of pthread_t
	pthread_t *thread_id=new pthread_t[pro+con];
	//the array of pthread_attr_t
	pthread_attr_t *attr=new pthread_attr_t[pro+con];
	//array of arguments 
	int *args=new int[pro+con];
	
	//set args
	for(int i=0; i<pro+con; i++)
	{
		args[i]=i;
	}
	//get default attributes
	for(int i=0; i<pro+con; i++)
	{
		pthread_attr_init(&attr[i]);
	}
	//make threads
	for(int i=0; i<pro+con; i++)
	{
		pthread_create(&thread_id[i], &attr[i], run, &args[i]);
	}
	//main thread sleeps
	sleep(run_time);
	//free memory
	delete[] thread_id;
	delete[] attr;
	delete[] args;
	
	return 0;
}
