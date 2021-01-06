#include <iostream>
using namespace std;

class Node
{
	public:
	int data;
	Node* next;
	Node* prev;
};

class double_linked_list
{
	public:
	Node* head;
	Node* tail;

	double_linked_list()
	{
		head = NULL;
		tail = NULL;
	}

	void push_back(int );
	void push_front(int );
	void AddAfter(Node* , int );
	void AddBefore(Node* , int );
	int pop_back();
	int top_back();
	int pop_front();
	int top_front();
	void print_list();
	bool is_empty();

	~double_linked_list()
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

bool double_linked_list::is_empty()
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

void double_linked_list::print_list()
{
	if (is_empty())
	{
		cout << "List is empty!" << endl;
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

void double_linked_list::AddAfter(Node* prev_node, int new_data)
{
	Node* new_node = new Node();
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

void double_linked_list::AddBefore(Node* next_node, int new_data)
{
	if (next_node == NULL)
	{
		cout << "The given next node can not be NULL" << endl;
		return;
	}

	if (next_node == head)
	{
		push_front(new_data);
		return;
	}

	Node* new_node = new Node();
	new_node->data = new_data;
	new_node->next = next_node;
	new_node->prev = next_node->prev;
	next_node->prev = new_node;

	if (new_node->prev != NULL)
	{
		new_node->prev->next = new_node;
	}
}

int double_linked_list::pop_front()
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
		return -1;
	}

	int value = head->data;
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

int double_linked_list::top_front()
{
	if (tail==NULL)
	{
		cout << "List is empty !" << endl;
		return -1;
	}
	return head->data;
}

int double_linked_list::pop_back()
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
	return value;
}

int double_linked_list::top_back()
{
	if (is_empty())
	{
		cout << "List is empty !" << endl;
		return -1;
	}
	return tail->data;
}

void double_linked_list::push_back(int new_data)
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
}

void double_linked_list::push_front(int new_data)
{
	Node* new_node = new Node();
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


int main()
{
	double_linked_list LL;
	cout << LL.is_empty() << endl;

	LL.push_front(5);
	LL.push_front(6);
	LL.push_front(7);
	LL.print_list();

	int x = LL.pop_front();
	cout << x << endl;
	LL.print_list();

	LL.push_back(8);
	LL.print_list();

	int y = LL.pop_back();
	cout << y << endl;
	LL.print_list();

	Node *tmp1 = LL.head;
	LL.AddAfter(tmp1, 9);
	LL.print_list();

	Node*tmp2 = LL.head;
	LL.AddBefore(tmp2, 10);
	LL.print_list();

	int a = LL.top_front();
	cout << a << endl;
	LL.print_list();

	int b = LL.top_back();
	cout << b << endl;
	LL.print_list();

	return 0;

}
