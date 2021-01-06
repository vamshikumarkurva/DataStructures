#include <iostream>
#include <stdlib.h>

using namespace std;

int MAX_SIZE = 10;

template <typename T>
class Node
{
public:
	T item;
	int priority;
};

template <typename T>
class priority_queue
{
public:
	Node<T>* Q = (Node<T>*) malloc(sizeof(Node<T>)*MAX_SIZE);
	int size;

	priority_queue<T>()
	{
		size = 0;
	}

	void insert(T, int);
	int getHighestIndex();
	T getHighestPriority();
	void deleteHighestPriority();
	void print_queue();

	~priority_queue<T>()
	{
		delete [] Q;
	}
};

template <typename T>
void priority_queue<T>::print_queue()
{
	if (size == 0)
	{
		cout << "Queue is empty!" << endl;
		return;
	}

	for (int i = 0; i < size; i++)
	{
		cout << "(" << (Q+i*sizeof(Node<T>))->item << "," << (Q+i*sizeof(Node<T>))->priority << ")";
	}

	cout << endl;
}

template <typename T>
void priority_queue<T>::insert(T data, int priority)
{
	if (size == MAX_SIZE)
	{
		cout << "No place for new elements!" << endl;
		return;
	}

	(Q+size*sizeof(Node<T>))->item = data;
	(Q+size*sizeof(Node<T>))->priority = priority;
	size += 1;
}

template <typename T>
int priority_queue<T>::getHighestIndex()
{
	if (size == 0)
	{
		cout << "Queue is empty!" << endl;
		return -1;
	}

	if (size == 1)
	{
		return 0;
	}

	int max_index = 0;
	int max_priority = (Q+0*sizeof(Node<T>))->priority;

	for (int i = 0; i < size; i++)
	{
		if ((Q+i*sizeof(Node<T>))->priority > max_priority)
		{
			max_priority = (Q+i*sizeof(Node<T>))->priority;
			max_index = i;
		}
	}

	return max_index;
}

template <typename T>
T priority_queue<T>::getHighestPriority()
{
	int max_index = getHighestIndex();
	if (max_index == -1)
	{
		cout << "Queue is empty!" << endl;
		return T(-1);
	}
	return (Q+max_index*sizeof(Node<T>))->item;
}

template <typename T>
void priority_queue<T>::deleteHighestPriority()
{
	int max_index = getHighestIndex();
	if (max_index == -1)
	{
		cout << "Queue is empty!" << endl;
		return;
	}
	if (max_index == 0 or max_index == size-1)
	{
		size = size-1;
		return;
	}

	for (int i = max_index; i < size; i++)
	{
		(Q+i*sizeof(Node<T>))->item =(Q+(i+1)*sizeof(Node<T>))->priority;
		(Q+i*sizeof(Node<T>))->priority = (Q+(i+1)*sizeof(Node<T>))->priority;
	}
}

int main()
{
	priority_queue<char> PQ;
	PQ.insert('a',2);
	PQ.insert('c',1);
	PQ.insert('b',3);
	PQ.print_queue();

	char x = PQ.getHighestPriority();
	cout << x << endl;

	PQ.deleteHighestPriority();
	PQ.print_queue();

	char y = PQ.getHighestPriority();
	cout << y << endl;

	PQ.deleteHighestPriority();
	PQ.print_queue();

	char z = PQ.getHighestPriority();
	cout << z << endl;

	PQ.deleteHighestPriority();
	PQ.print_queue();

	return 0;
}

