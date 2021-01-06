#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "linear_data_structures.h"

using namespace std;

#define MAX 100

void print_array(int* ptr, int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << *(ptr+i) << " ";
	}
	cout << endl;
}

typedef BinaryMaxHeap<int> BMH;
int main()
{
	int *array = new int[MAX];
	int size = 50;

	for (int i = 0; i < size; i++)
	{
		array[i] = rand()%1000;
	}

	cout << "Original array elements: " << endl;
	print_array(array, size);

	BMH priority_queue;
	for (int i = 0; i < size; i++)
	{
		priority_queue.Insert(array[i]);
	}

	for (int  i = size-1; i >=0; i--)
	{
		array[i] = priority_queue.ExtractMax();
	}

	cout << "Elements after sorting: " << endl;
	print_array(array, size);
}


