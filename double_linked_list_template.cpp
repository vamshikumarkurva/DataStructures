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


int main()
{
	double_linked_list<char> LL;
	cout << LL.is_empty() << endl;

	LL.push_front('a');
	LL.push_front('b');
	LL.push_front('c');
	LL.print_list();

	char x = LL.pop_front();
	cout << x << endl;
	LL.print_list();

	LL.push_back(8);
	LL.print_list();

	char y = LL.pop_back();
	cout << y << endl;
	LL.print_list();

	Node<char>* tmp1 = LL.head;
	LL.AddAfter(tmp1, 'd');
	LL.print_list();

	Node<char>* tmp2 = LL.head;
	LL.AddBefore(tmp2, 'e');
	LL.print_list();

	char a = LL.top_front();
	cout << a << endl;
	LL.print_list();

	char b = LL.top_back();
	cout << b << endl;
	LL.print_list();

	return 0;

}
