#include <stdio.h>
#include <stdlib.h>

//ýt updates the size but ýt doesn't work because when I create the new arrat he program enters in a loop and doesn't stop
typedef struct hash
{
	int key;
	void *data;
}HASH_TABLE;

int size_checker=1;

int insert(HASH_TABLE value,HASH_TABLE array[],int size);
void print_hash(HASH_TABLE array[],int size);
void shrink_rehash(HASH_TABLE array[],int size);
void extend_rehash(HASH_TABLE array[],int size);
int hash_func(int x,int size);

int hash_func(int x,int size)
{
	return x%size;
}

void extend_rehash(HASH_TABLE array[],int size)
{
	printf("extend rehash\n");
	int new_size=2*size+1;
	HASH_TABLE array2[new_size];
	int i;
	for(i=0;i<new_size;i++)
	{
		if(array[i].key!=-1)
		{
			//printf("to check whether it goes to insert again\n");
			insert(array[i],array2,new_size);
			//printf("acaba sorun nerede\n");
		}
	}
}

void shrink_rehash(HASH_TABLE array[],int size)
{
	int new_size=(size-1)/2;
	HASH_TABLE array2[new_size];
	int i;
	for(i=0;i<size;i++)
	{
		if(array[i].key!=-1)
		{
			insert(array[i],array2,new_size);
		}
	}
}

int insert(HASH_TABLE value,HASH_TABLE array[],int size)
{
	int index;
	if(array[hash_func(value.key,size)].key == -1)
	{
		array[hash_func(value.key,size)] = value;
		
		if(size_checker>=(size*73)/100)
		{
			extend_rehash(array,size);
		}
		size_checker++;
	}
	else 
	{
		if(size_checker>=(size*73)/100)
		{
			extend_rehash(array,size);
		}
		index = hash_func(value.key,size);
		while(array[index].data != value.data && array[index].key!=-1)
		{
		//problem is here
			index ++;
			index = index %size;
		//	printf("collision\n");
		}	
		array[index].data = value.data;
		array[index].key = value.key;
		size_checker++;
	}
	printf("%d is the size\n",size);
	printf("%d - size_checker\n",size_checker);
	return size_checker;
}


void print_hash(HASH_TABLE array[],int size)
{
	int i;
	for(i = 0;i<size;i++)
	{
		printf("key:%d data:%d\n",array[i].key,array[i].data);
	}
}
int main()
{
	int i;
	int size=11;
	HASH_TABLE array[size];
	for(i = 0;i<size;i++)
	{
		array[i].key=-1;
		array[i].data=0;
	}
	HASH_TABLE value;

	value.key=1;
	value.data=66666;
	insert(value,array,size);
	
	value.key=100;
	value.data=77777;
	insert(value,array,size);
	
	value.key=28;
	value.data=99999;
	insert(value,array,size);
	
	value.key=38;
	value.data=65246;
	insert(value,array,size);
	
	value.key=20;
	value.data=75254;
	insert(value,array,size);
	
	value.key=22;
	value.data=24786;
	insert(value,array,size);
	
	value.key=26;
	value.data=27528;
	insert(value,array,size);

	value.key=18;
	value.data=25268;
	insert(value,array,size); 
	
	print_hash(array,size);

	return 0;
}
