#include <iostream>
using namespace std;

class Node
{
	public:
	int data;
	Node* next;
};

void push_front(Node** head, int new_data)
{
	Node* new_node = new Node();
	new_node->data = new_data;
	new_node->next = *head;
	*head = new_node;
}

void push_back(Node** head, int new_data)
{
	Node* new_node = new Node();
	new_node->data = new_data;
	new_node->next = NULL;

	Node* tmp = *head;
	while (tmp->next != NULL){
		tmp = tmp->next;
	}
	tmp->next = new_node;
}

void AddAfter(Node* prev_node, int new_data)
{
	Node* new_node = new Node();
	new_node->data = new_data;
	new_node->next = prev_node->next;
	prev_node->next = new_node;
}

void AddBefore(Node** head, Node* next_node, int new_data)
{
	Node* new_node = new Node();
	new_node->data = new_data;

	if (next_node == NULL)
	{
		cout << "The given next node can not be NULL" << endl;
		return;
	}

	if (next_node == *head)
	{
		push_front(head, new_data);
		return;
	}

	Node *tmp = *head;
	while (tmp->next != next_node)
	{
		tmp = tmp->next;
	}
	new_node->next = next_node;
	tmp->next = new_node;
}

int pop_front(Node** head)
{
	Node* tmp = *head;
	if (tmp==NULL)
	{
		cout << "List is empty!" << endl;
		return -1;
	}
	else
	{
		int value = tmp->data;
		*head = tmp->next;
		return value;
	}

}

int top_front(Node **head)
{
	Node* tmp = *head;
	if (tmp==NULL)
	{
		cout << "List is empty !" << endl;
		return -1;
	}
	else
	{
		return tmp->data;
	}
}

int pop_back(Node** head)
{
	Node* tmp = *head;
	if (tmp == NULL)
	{
		cout << "List is empty!" << endl;
		return -1;
	}
	if (tmp->next == NULL)
	{
		*head = NULL;
		return tmp->data;
	}
	else
	{
		while (tmp->next->next != NULL)
		{
			tmp = tmp->next;
		}
		int value = tmp->next->data;
		tmp->next = NULL;
		return value;
	}
}

int top_back(Node** head)
{
	Node* tmp = *head;
	if (tmp == NULL)
	{
		cout << "List is empty!" << endl;
		return -1;
	}
	if (tmp->next == NULL)
	{
		return tmp->data;
	}
	else
	{
		while (tmp->next != NULL)
		{
			tmp = tmp->next;
		}
		return tmp->data;
	}
}

void print_list(Node* head)
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

void delete_list(Node** head)
{
	Node* current = *head;
	Node* next;

	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}

	*head = NULL;
}

int main()
{
	Node* head = NULL;

	push_front(&head, 5);
	push_front(&head, 6);
	push_front(&head, 7);
	print_list(head);

	int x = pop_front(&head);
	cout << x << endl;
	print_list(head);

	push_back(&head, 8);
	print_list(head);

	int y = pop_back(&head);
	cout << y << endl;
	print_list(head);

	Node *tmp1 = head;
	AddAfter(tmp1, 9);
	print_list(head);

	Node*tmp2 = head;
	AddBefore(&head, tmp2, 10);
	print_list(head);

	int a = top_front(&head);
	cout << a << endl;
	print_list(head);

	int b = top_back(&head);
	cout << b << endl;
	print_list(head);

	delete_list(&head);
	print_list(head);

	return 0;
}
