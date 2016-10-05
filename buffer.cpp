#include"buffer.h"
#include<iostream>
using namespace std;

//constructor
buffer::buffer()
{
	element_num=-1;
	enter_point=0;
	exit_point=0;
	
	
}

int buffer::insert_item(int item)
{
	if(element_num>=5)
	{
		return -1;
	}
	data[enter_point]=item;
	element_num++;
	enter_point++;
	if(enter_point>=5)
	{
		enter_point=0;
	}
	return 0;
}

int buffer::remove_item()
{
	if(element_num<0)
	{
		return -1;
	}
	cout<<data[exit_point];
	exit_point++;
	element_num--;
	if(exit_point>=5)
	{
		exit_point=0;
	}
	return 0;
} 
