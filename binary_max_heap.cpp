#include <iostream>
#include <stdlib.h>
using namespace std;

#define MAX_SIZE 100

template <typename T>
class BinaryMaxHeap
{
public:
	T *array = new T[MAX_SIZE];
	int size;

	int Size();
	void Insert(T );
	T GetMax();
	void SiftUp(int );
	void SiftDown(int );
	void Swap(int, int);
	T ExtractMax();
	void Remove(int );
	void ChangePriority(int , T);
	void PrintHeap();

	BinaryMaxHeap<T>()
	{
		size = 0;
	}

	~BinaryMaxHeap<T>()
	{
		delete [] array;
	}
};

template <typename T>
void BinaryMaxHeap<T>::Swap(int i, int j)
{
	T x = array[i];
	T y = array[j];
	array[j] = x;
	array[i] = y;
}


template <typename T>
T BinaryMaxHeap<T>::GetMax()
{
	try
	{
		if (size == 0)
		{
			throw "Heap is empty!";
		}
	}
	catch (const char* x)
	{
		cout << x << endl;
		return T(-1);
	}
	return array[0];
}

template <typename T>
int BinaryMaxHeap<T>::Size()
{
	return size;
}

template <typename T>
void BinaryMaxHeap<T>::Insert(T data)
{
	if (size == MAX_SIZE)
	{
		cout << "Can not insert new data! Full Occupancy" << endl;
		return;
	}
	array[size] = data;
	size += 1;
	SiftUp(size-1);

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

template <typename T>
void BinaryMaxHeap<T>::SiftUp(int i)
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

	if (i == 0)
	{
		return;
	}

	int parent = Parent(i);

	if (parent >= 0 and array[parent] < array[i])
	{
		Swap(i, parent);
		SiftUp(parent);
	}
}

template <typename T>
void BinaryMaxHeap<T>::SiftDown(int i)
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
		Swap(i, max_index);
		SiftDown(max_index);
	}
}

template <typename T>
T BinaryMaxHeap<T>::ExtractMax()
{
	if (size == 0)
	{
		cout << "Heap is empty!" << endl;
		return T(-1);
	}

	if (size == 1)
	{
		size -= 1;
		return array[size];
	}

	T result = array[0];
	array[0] = array[size-1];
	size -= 1;
	SiftDown(0);
	return result;
}

template <typename T>
void BinaryMaxHeap<T>::Remove(int i)
{
	T max = GetMax();
	array[i] = max+T(10);
	SiftUp(i);
	ExtractMax();
}

template <typename T>
void BinaryMaxHeap<T>::ChangePriority(int i, T new_priority)
{
	if (i < 0 or i > size-1)
	{
		cout << "Index out of range!" << endl;
		return;
	}

	T old_priority = array[i];
	array[i] = new_priority;
	if (new_priority > old_priority)
	{
		SiftUp(i);
	}
	else
	{
		SiftDown(i);
	}
}

template <typename T>
void BinaryMaxHeap<T>::PrintHeap()
{
	if (size == 0)
	{
		cout << "Heap is empty!" << endl;
		return;
	}

	for (int i = 0; i < size; i++)
	{
		cout << array[i] << " ";
	}
	cout << endl;
}

typedef BinaryMaxHeap<int> BMH;
int main()
{
	BMH heap;
	heap.Insert(10);
	heap.Insert(5);
	heap.Insert(20);
	heap.Insert(100);
	heap.PrintHeap();

	int x = heap.ExtractMax();
	cout << x << endl;
	heap.PrintHeap();

	int y = heap.ExtractMax();
	cout << y << endl;

	int z = heap.ExtractMax();
	cout << z << endl;

	return 0;
}
