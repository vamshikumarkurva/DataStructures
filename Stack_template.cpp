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

	void push(T new_data);
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
			return -1;
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
	size -= 1;
	return value;
}

template <typename T>
T stack<T>::top()
{
	if (is_empty())
	{
		cout << "stack is empty!" << endl;
		return -1;
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
	stack<char> S;
	S.pop();

	S.push('a');
	S.push('b');
	S.push('c');
	S.push('d');
	S.push('e');
	S.print_stack();

	char x = S.pop();
	cout << x << endl;
	S.print_stack();

	char y = S.top();
	cout << y << endl;
	S.print_stack();

	int size = S.Size();
	cout << "Size = " << size << endl;

	return 0;
}
