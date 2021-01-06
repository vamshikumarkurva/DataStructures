#include <iostream>
using namespace std;

class Node
{
	public:
	int data;
	Node* next;
	Node* prev;
};

class stack
{
	public:
	Node* head;
	Node* tail;
	int size;

	stack()
	{
		head = NULL;
		tail = NULL;
		size = 0;
	}

	void push(int new_data);
	int pop();
	int top();
	bool is_empty();
	int Size();
	void print_stack();

	~stack()
	{
		Node* current = head;
		Node* next;

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

void stack::push(int new_data)
{
	Node* new_node = new Node();
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

int stack::pop()
{
	try
	{
		if (is_empty())
		{
			throw "Stack is empty!";
		}
	}
	catch (const char* x)
	{
		cout << x << endl;
		return -1;
	}
	int value = tail->data;
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

int stack::top()
{
	if (is_empty())
	{
		cout << "stack is empty!" << endl;
		return -1;
	}
	return tail->data;
}

bool stack::is_empty()
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

int stack::Size()
{
	return size;
}

void stack::print_stack()
{
	if (is_empty())
	{
		cout << "stack is empty!" << endl;
		return;
	}
	Node* ptr = head;
	while (ptr!=tail)
	{
		cout << ptr->data << " " ;
		ptr = ptr->next;
	}
	cout << tail->data << endl ;
}

int main()
{
	stack S;
	S.pop();

	S.push(1);
	S.push(2);
	S.push(3);
	S.push(4);
	S.push(5);
	S.print_stack();

	int x = S.pop();
	cout << x << endl;
	S.print_stack();

	int y = S.top();
	cout << y << endl;
	S.print_stack();

	int size = S.Size();
	cout << "Size = " << size << endl;

	return 0;
}
