#include <iostream>
#include <stdlib.h>
#include <stdio.h>

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

int Parent(int i)
{
	int parent = (i+1)/2 - 1;
	return parent;
}

int LeftChild(int i)
{
	int lchild = 2*i+1;
	return lchild;
}

int RightChild(int i)
{
	int rchild = 2*i+2;
	return rchild;
}

void Swap(int* array, int i, int j)
{
	int x = array[i];
	int y = array[j];
	array[j] = x;
	array[i] = y;
}

void SiftDown(int* array, int size, int i)
{
	try
	{
		if (i > size-1 or i < 0)
		{
			throw "Index can not be more than the heap size!";
		}
	}
	catch (const char* x)
	{
		cout << x << endl;
		return;
	}

	if (i == size-1)
	{
		return;
	}

	int max_index = i;
	int lchild = LeftChild(i);
	int rchild = RightChild(i);

	if (lchild < size and array[lchild] > array[max_index])
	{
		max_index = lchild;
	}
	if (rchild < size and array[rchild] > array[max_index])
	{
		max_index = rchild;
	}
	if (max_index != i)
	{
		Swap(array, i, max_index);
		SiftDown(array, size, max_index);
	}
}

/* One advantage of heap is it can be represented implicitly using an array.
 * Array can be converted into heap by Sifting Down of n/2 non-leaf nodes.
 * Each Sifting Down takes log(n) time
 * Total complexity: 0.5*n.log(n)
 */
void BuildHeap(int* array, int size)
{
	for (int i = size/2-1; i >= 0; i--)
	{
		SiftDown(array, size, i);
	}
}

/*
 * Each extraction of max element from heap is of O(log n) time.
 * Getting max - O(1)
 * Replace max with the bottom right leaf{Last element in the array} - O(1)
 * SiftDown the leaf to find it's right position (to satisfy the heap property)
 */
void HeapSort(int* array, int size)
{
	BuildHeap(array, size);

	cout << "After building heap elements are: " << endl;
	print_array(array, size);
	int temp_size = size;

	for (int i = 0; i < size-1; i++)
	{
		Swap(array, 0, temp_size-1);
		temp_size -= 1;
		SiftDown(array, temp_size, 0);
	}
}


int main()
{
	int *array = new int[MAX];
	int size = 30;

	for (int i = 0; i < size; i++)
	{
		array[i] = rand()%1000;
	}

	cout << "Original array elements: " << endl;
	print_array(array, size);

	HeapSort(array, size);

	cout << "Elements after sorting: " << endl;
	print_array(array, size);

	delete[] array;

	return 0;

}
