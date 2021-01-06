#ifndef LINEAR_DATA_STRUCTURES_H_
#define LINEAR_DATA_STRUCTURES_H_

#include <iostream>
#include <stdlib.h>
using namespace std;

#define MAX_SIZE 1000

template <typename T>
class Node
{
	public:
	T data;
	Node<T>* next;
	Node<T>* prev;
};

template <typename T>
class stack
{
	public:
	Node<T>* head;
	Node<T>* tail;
	int size;

	stack<T>()
	{
		head = NULL;
		tail = NULL;
		size = 0;
	}

	void push(T );
	T pop();
	T top();
	bool is_empty();
	int Size();
	void print_stack();

	~stack<T>()
	{
		Node<T>* current = head;
		Node<T>* next;

		while (current != NULL)
		{
			next = current->next;
			free(current);
			current = next;
		}

		head = NULL;
		tail = NULL;
	}

};

template <typename T>
void stack<T>::push(T new_data)
{
	Node<T>* new_node = new Node<T>();
	new_node->data = new_data;
	new_node->next = NULL;
	if (tail==NULL)
	{
		new_node->prev = NULL;
		head = new_node;
		tail = new_node;
	}
	else
	{
		tail->next = new_node;
		new_node->prev = tail;
		tail = new_node;
	}
	size += 1;
}

template <typename T>
T stack<T>::pop()
{
	try
	{
		if (is_empty())
		{
			throw "Stack is empty!";
			return T(-1);
		}
	}
	catch (const char* x)
	{
		cout << x << endl;
		return -1;
	}
	T value = tail->data;
	tail = tail->prev;
	if (tail == NULL)
	{
		head = NULL;
	}
	else
	{
		tail->next = NULL;
	}
	size -= 1;
	return value;
}

template <typename T>
T stack<T>::top()
{
	if (is_empty())
	{
		cout << "stack is empty!" << endl;
		return T(-1);
	}
	return tail->data;
}

template <typename T>
bool stack<T>::is_empty()
{
	if (Size()==0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

template <typename T>
int stack<T>::Size()
{
	return size;
}

template <typename T>
void stack<T>::print_stack()
{
	if (is_empty())
	{
		cout << "stack is empty!" << endl;
	}
	Node<T>* ptr = head;
	while (ptr!=tail)
	{
		cout << ptr->data << " " ;
		ptr = ptr->next;
	}
	cout << tail->data << endl ;
}

template <typename T>
class Queue
{
	public:
	Node<T>* head;
	Node<T>* tail;
	int size;

	Queue<T>()
	{
		head = NULL;
		tail = NULL;
		size = 0;
	}

	void Enqueue(T new_data);
	T Dequeue();
	bool is_empty();
	int Size();
	void print_queue();

	~Queue<T>()
	{
		Node<T>* current = head;
		Node<T>* next;

		while (current != NULL)
		{
			next = current->next;
			free(current);
			current = next;
		}

		head = NULL;
		tail = NULL;
	}

};

template <typename T>
void Queue<T>::Enqueue(T new_data)
{
	Node<T>* new_node = new Node<T>();
	new_node->data = new_data;
	new_node->next = NULL;
	if (tail==NULL)
	{
		new_node->prev = NULL;
		head = new_node;
		tail = new_node;
	}
	else
	{
		tail->next = new_node;
		new_node->prev = tail;
		tail = new_node;
	}
	size += 1;
}

template <typename T>
T Queue<T>::Dequeue()
{
	try
	{
		if (is_empty())
		{
			throw "Queue is empty!";
		}
	}
	catch (const char* x)
	{
		cout << x << endl;
		return T(-1);
	}
	T value = head->data;
	head = head->next;

	if (head == NULL)
	{
		tail = NULL;
	}
	else
	{
		head->prev = NULL;
	}
	size -= 1;
	return value;
}

template <typename T>
int Queue<T>::Size()
{
	return size;
}

template <typename T>
bool Queue<T>::is_empty()
{
	if (Size()==0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

template <typename T>
void Queue<T>::print_queue()
{
	if (is_empty())
	{
		cout << "Queue is empty!" << endl;
	}
	Node<T>* ptr = head;
	while (ptr!=tail)
	{
		cout << ptr->data << " " ;
		ptr = ptr->next;
	}
	cout << tail->data << endl ;
}

template <typename T>
class double_linked_list
{
	public:
	Node<T>* head;
	Node<T>* tail;

	double_linked_list<T>()
	{
		head = NULL;
		tail = NULL;
	}

	void push_back(T );
	void push_front(T );
	void AddAfter(Node<T>* , T );
	void AddBefore(Node<T>* , T );
	T pop_back();
	T top_back();
	T pop_front();
	T top_front();
	void print_list();
	bool is_empty();

	~double_linked_list<T>()
	{
		Node<T>* current = head;
		Node<T>* next;

		while (current != NULL)
		{
			next = current->next;
			free(current);
			current = next;
		}

		head = NULL;
		tail = NULL;
	}
};

template <typename T>
bool double_linked_list<T>::is_empty()
{
	if (tail==NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

template <typename T>
void double_linked_list<T>::print_list()
{
	if (is_empty())
	{
		cout << "List is empty!" << endl;
	}

	Node<T>* ptr = head;
	while (ptr!=tail)
	{
		cout << ptr->data << " " ;
		ptr = ptr->next;
	}
	cout << tail->data << endl ;
}

template <typename T>
void double_linked_list<T>::AddAfter(Node<T>* prev_node, T new_data)
{
	Node<T>* new_node = new Node<T>();
	new_node->data = new_data;
	new_node->prev = prev_node;
	new_node->next = prev_node->next;
	prev_node->next = new_node;

	if (new_node->next != NULL)
	{
		new_node->next->prev = new_node;
	}

	if (prev_node == tail)
	{
		tail = new_node;
	}
}

template <typename T>
void double_linked_list<T>::AddBefore(Node<T>* next_node, T new_data)
{
	if (next_node == NULL)
	{
		cout << "Given next node can not be NULL!" << endl;
		return;
	}

	if (next_node == head)
	{
		push_front(new_data);
		return;
	}

	Node<T>* new_node = new Node<T>();
	new_node->data = new_data;
	new_node->next = next_node;
	new_node->prev = next_node->prev;
	next_node->prev = new_node;

	if (new_node->prev != NULL)
	{
		new_node->prev->next = new_node;
	}
}

template <typename T>
T double_linked_list<T>::pop_front()
{
	try
	{
		if (is_empty())
		{
			throw "List is empty!";
		}
	}
	catch (const char* x)
	{
		cout << x << endl;
		return T(-1);
	}

	T value = head->data;
	head = head->next;

	if (head == NULL)
	{
		tail = NULL;
	}
	else
	{
		head->prev = NULL;
	}
	return value;
}

template <typename T>
T double_linked_list<T>::top_front()
{
	if (tail==NULL)
	{
		cout << "List is empty!" << endl;
	}
	return head->data;
}

template <typename T>
T double_linked_list<T>::pop_back()
{
	try
	{
		if (is_empty())
		{
			throw "List is empty!";
		}
	}
	catch (const char* x)
	{
		cout << x << endl;
		return T(-1);
	}

	T value = tail->data;
	tail = tail->prev;
	if (tail == NULL)
	{
		head = NULL;
	}
	else
	{
		tail->next = NULL;
	}
	return value;
}

template <typename T>
T double_linked_list<T>::top_back()
{
	if (is_empty())
	{
		cout << "List is empty!" << endl;
	}
	return tail->data;
}

template <typename T>
void double_linked_list<T>::push_back(T new_data)
{
	Node<T>* new_node = new Node<T>();
	new_node->data = new_data;
	new_node->next = NULL;
	if (tail==NULL)
	{
		new_node->prev = NULL;
		head = new_node;
		tail = new_node;
	}
	else
	{
		tail->next = new_node;
		new_node->prev = tail;
		tail = new_node;
	}
}

template <typename T>
void double_linked_list<T>::push_front(T new_data)
{
	Node<T>* new_node = new Node<T>();
	new_node->data = new_data;
	new_node->prev = NULL;
	new_node->next = head;

	if (head == NULL)
	{
		tail = new_node;
		head = new_node;
	}
	else
	{
		head->prev = new_node;
		head = new_node;
	}
}

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

#endif /* LINEAR_DATA_STRUCTURES_H_ */
