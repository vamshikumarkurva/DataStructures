#include <iostream>
using namespace std;

template <typename T>
class Node
{
	public:
	T data;
	Node<T>* next;
	Node<T>* prev;
};

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
		cout << "Queue is empty !" << endl;;
		return;
	}
	Node<T>* ptr = head;
	while (ptr!=tail)
	{
		cout << ptr->data << " " ;
		ptr = ptr->next;
	}
	cout << tail->data << endl ;
}

int main()
{
	Queue<int> Q;
	Q.Dequeue();

	Q.Enqueue(1);
	Q.Enqueue(2);
	Q.Enqueue(3);
	Q.Enqueue(4);
	Q.print_queue();

	int x = Q.Dequeue();
	cout << x << endl;
	Q.print_queue();

	int size = Q.Size();
	cout << "Size = " << size << endl;

	return 0;
}



