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

void Swap(int* array, int i, int j)
{
	int x = array[i];
	int y = array[j];
	array[i] = y;
	array[j] = x;
}

void merge(int* array, int l, int m, int r)
{
	int size = r-l+1;
	int n1 = m-l+1;
	int n2 = r-m;

	int *a = new int[n1];
	int *b = new int[n2];

	for (int i = 0; i < n1; i++)
	{
		a[i] = array[l+i];
	}

	for (int j = 0; j < n2; j++)
	{
		b[j] = array[j+m+1];
	}

	int i = 0, j = 0, k = l;

	while (i < n1 && j < n2)
	{
		if (a[i] < b[j])
		{
			array[k] = a[i];
			i++;
		}
		else
		{
			array[k] = b[j];
			j++;
		}
		k++;
	}

	if (i == n1)
	{
		while(j < n2)
		{
			array[k] = b[j];
			k++;
			j++;
		}
	}
	else if (j == n2)
	{
		while(i < n1)
		{
			array[k] = a[i];
			k++;
			i++;
		}
	}

	delete [] a;
	delete [] b;
}

/*
 * Recursively splits the array into 1 element arrays and merges them.
 * Complexity: n.log(n)
 * Each merge : O(n) (n comparisons)
 * Total levels: log(n)
 * for level j: array size: n/2^j
 * 			  : computing components: 2^j
 */
void merge_sort_list(int* array, int start, int end)
{
	if (start >= end)
	{
		return;
	}

	int size = end+start-1;
	int middle = size/2;

	merge_sort_list(array, start, middle);
	merge_sort_list(array, middle+1, end);
	merge(array, start, middle, end);

}

void MergeSort(int* array, int size)
{
	merge_sort_list(array, 0, size-1);
}

/*
 * Compares the adjacent elements and swaps them if the order is wrong.
 * At the end of one sweep, maximum reaches the end of array.
 * Complexity: n^2 as there will be n sweeps in the worst case.
 */
void BubbleSort(int* array, int size)
{
	bool flag = false;;
	for (int j = 0; j < size-1; j++)
	{
		flag = false;
		for (int i = 0; i < size-1-j; i++)
		{
			if (array[i] > array[i+1])
			{
				Swap(array, i, i+1);
				flag = true;
			}
		}
		if (not flag)
		{
			return;
		}
	}
	return;
}

/*
 * At the end of every sweep, max element reaches the end of array.
 * Sort the remaining (n-1) elements in the same way
 * Each swap: n comparisons
 * Complexity: n^2
 */
void SelectionSort(int* array, int size)
{
	for ( int i = 0; i < size-1; i++)
	{
		int max_index = 0;
		for (int j = 1; j < size-i; j++)
		{
			if (array[j] > array[max_index])
			{
				max_index = j;
			}
		}
		Swap(array, max_index, size-1-i);
	}
}

int Partition(int* array, int pivot, int l, int r)
{
	int i = l+1;
	for(int j = l+1; j <= r; j++)
	{
		if (array[j]  < pivot)
		{
			if (i != j)
			{
				Swap(array, i, j);
			}
			i += 1;
		}
	}
	Swap(array, l, i-1);
	return i-1;
}


/* Uses no extra memory, unlike merge sort.
 * Complexity depends on the quality of the pivot.
 * If the pivot divides the array into equal partitions -> good (log n levels)
 * We can choose random pivots. even 25:75 split give n.log(n) complexity.
 * Pivot is the first element and Partitions around the pivot.
 * After the partition: |<P|P|>P
 */
void quick_sort_list(int* array, int l, int r)
{
	int size = r-l+1;
	if (size==1)
	{
		return ;
	}

	// rand() % size --> produces an integer between [0, size] randomly.
	int rand_pivot_index = l + rand() % (size) ;
	Swap(array, rand_pivot_index, l);
	int pivot = array[l];
	int position = Partition(array, pivot, l, r);
	if (position-1 > l)
	{
		quick_sort_list(array, l, position-1);
	}
	if (position+1 < r)
	{
		quick_sort_list(array, position+1, r);
	}
}

void QuickSort(int* array, int size)
{
	if (size==1)
	{
		return;
	}
	quick_sort_list(array, 0, size-1);
	return;
}

int main()
{
	int *array = new int[MAX];
	int size = 90;

	for (int i = 0; i < size; i++)
	{
		array[i] = rand()%1000;
	}

	cout << "Original array elements: " << endl;
	print_array(array, size);

//	MergeSort(array, size);
//	BubbleSort(array, size);
//	SelectionSort(array, size);
	QuickSort(array, size);

	cout << "Elements after sorting: " << endl;
	print_array(array, size);

}
