#include <iostream>
using namespace std;

class Node
{
	public:
	int data;
	Node* next;
};

class linked_list
{
	public:
	Node* head;
	Node* tail;

	linked_list()
	{
		head = NULL;
		tail = NULL;
	}

	void push_front(int );
	void push_back(int );
	void AddAfter(Node* , int );
	void AddBefore(Node* , int );
	int pop_front();
	int top_front();
	int pop_back();
	int top_back();
	void print_list();
	bool is_empty();

	~linked_list()
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
	}

};

bool linked_list::is_empty()
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

void linked_list::push_front(int new_data)
{
	Node* new_node = new Node();
	new_node->data = new_data;
	new_node->next = head;
	head = new_node;

	if (tail==NULL)
	{
		tail = new_node;
	}

}

void linked_list::push_back(int new_data)
{
	Node* new_node = new Node();
	new_node->data = new_data;
	new_node->next = NULL;

	if (tail == NULL)
	{
		head = new_node;
		tail = new_node;
	}
	else
	{
		tail->next = new_node;
		tail = new_node;
	}

}

void linked_list::AddAfter(Node* prev_node, int new_data)
{
	Node* new_node = new Node();
	new_node->data = new_data;
	new_node->next = prev_node->next;
	prev_node->next = new_node;
}

void linked_list::AddBefore(Node* next_node, int new_data)
{
	Node* new_node = new Node();
	new_node->data = new_data;

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

	Node *tmp = head;
	while (tmp->next != next_node)
	{
		tmp = tmp->next;
	}
	new_node->next = next_node;
	tmp->next = new_node;
}

int linked_list::pop_front()
{
	if (head==NULL)
	{
		cout << "List is empty!" << endl;
		return -1;
	}
	else
	{
		int value = head->data;
		head = head->next;
		if (head == NULL)
		{
			tail = NULL;
		}
		return value;
	}
}

int linked_list::top_front()
{
	if (head==NULL)
	{
		cout << "List is empty !" << endl;
		return -1;
	}
	else
	{
		return head->data;
	}
}

int linked_list::pop_back()
{
	if (head == NULL)
	{
		cout << "List is empty!" << endl;
		return -1;
	}
	if (head == tail)
	{
		head = NULL;
		tail = NULL;
		return head->data;
	}
	else
	{
		Node* tmp = head;
		while (tmp->next != tail)
		{
			tmp = tmp->next;
		}
		int value = tmp->next->data;
		tmp->next = NULL;
		tail = tmp;
		return value;
	}
}

int linked_list::top_back()
{
	if (head == NULL)
	{
		cout << "List is empty!" << endl;
		return -1;
	}
	return tail->data;
}

void linked_list::print_list()
{
	Node* ptr = head;
	if (ptr==NULL)
	{
		cout << "List is empty!" << endl;
		return;
	}

	while (ptr!=NULL)
	{
		cout << ptr->data << " ";
		ptr = ptr->next;
	}
	cout << endl;
}


int main()
{
	linked_list LL;

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
