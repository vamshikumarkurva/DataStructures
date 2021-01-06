#include <iostream>
#include <stdlib.h>
#include "linear_data_structures.h"

using namespace std;

template <typename T>
struct NODE
{
	int data;
	struct NODE<T>* left;
	struct NODE<T>* right;

	NODE<T>(T val)
	{
		data = val;
		left = NULL;
		right = NULL;
	}
};

template <typename T>
class BinaryTree
{
	public:
	NODE<T>* root;

	BinaryTree<T>()
	{
		root = NULL;
	}

	void Insert(T );
	void DeleteTree(NODE<T>* );
	void PreOrderTraversal(NODE<T>*);
	void InOrderTraversal(NODE<T>*);
	void PostOrderTraversal(NODE<T>*);
	void LevelTraversal(NODE<T>*);
	void Deepest_right_node(NODE<T>** , NODE<T>** , bool* );
	void DeleteNode(T );
	int Size(NODE<T>*);
	int Height(NODE<T>*);
	NODE<T>* Search(T , NODE<T>**);

};


/* Inserting the node at the first position
   available in the level traversal. This
   keeps the tree close to complete, with
   minimum levels for given no of nodes. */

template <typename T>
void BinaryTree<T>::Insert(T new_data)
{
	if (root == NULL)
	{
		root = new NODE<T>(new_data);
		return;
	}

	struct NODE<T>* new_node = new NODE<T>(new_data);

	Queue<struct NODE<T>*> Q;
	Q.Enqueue(root);

	while (not Q.is_empty())
	{
		struct NODE<T>* node = Q.Dequeue();
		if (node->left != NULL)
		{
			Q.Enqueue(node->left);
		}
		else
		{
			node->left = new_node;
			return;
		}
		if (node->right != NULL)
		{
			Q.Enqueue(node->right);
		}
		else
		{
			node->right = new_node;
			return;
		}
	}
}

template <typename T>
void BinaryTree<T>::DeleteTree(NODE<T>* root)
{
	if (root == NULL)
	{
		return;
	}
	DeleteTree(root->left);
	DeleteTree(root->right);
	free(root);
}

template <typename T>
void BinaryTree<T>::InOrderTraversal(NODE<T>* root)
{
	if (root == NULL)
	{
		return;
	}

	InOrderTraversal(root->left);
	cout << root->data << " " ;
	InOrderTraversal(root->right);
}

template <typename T>
void BinaryTree<T>::PreOrderTraversal(NODE<T>* root)
{
	if (root == NULL)
	{
		return;
	}

	cout << root->data << " " ;
	PreOrderTraversal(root->left);
	PreOrderTraversal(root->right);
}

template <typename T>
void BinaryTree<T>::PostOrderTraversal(NODE<T>* root)
{
	if (root == NULL)
	{
		return;
	}

	PostOrderTraversal(root->left);
	PostOrderTraversal(root->right);
	cout << root->data << " " ;
}

template <typename T>
void BinaryTree<T>::LevelTraversal(NODE<T>* root)
{
	if (root == NULL)
	{
		return;
	}

	Queue<struct NODE<T>*> Q;
	Q.Enqueue(root);

	while (not Q.is_empty())
	{
		struct NODE<T>* node = Q.Dequeue();
		cout << node->data << " " ;
		if (node->left != NULL)
		{
			Q.Enqueue(node->left);
		}
		if (node->right != NULL)
		{
			Q.Enqueue(node->right);
		}
	}
}

template <typename T>
int BinaryTree<T>::Size(NODE<T>* root)
{
	if (root ==  NULL)
	{
		return 0;
	}

	return 1+Size(root->left)+Size(root->right);
}

template <typename T>
int BinaryTree<T>::Height(NODE<T>* root)
{
	if (root ==  NULL)
	{
		return 0;
	}

	int height_left = Height(root->left);
	int height_right = Height(root->right);

	if (height_left > height_right)
	{
		return 1+height_left;
	}
	else
	{
		return 1+height_right;
	}
}

template <typename T>
void BinaryTree<T>::Deepest_right_node(NODE<T>** DeepestNode, NODE<T>** ParentNode, bool* left)
{
	if (Size(root) == 0)
	{
		cout << "Tree is empty!" << endl;
		return;
	}

	Queue<struct NODE<T>*> Q;
	Q.Enqueue(root);

	while (not Q.is_empty())
	{
		struct NODE<T>* node = Q.Dequeue();
		if (node->left != NULL)
		{
			*ParentNode = node;
			*left = true;
			Q.Enqueue(node->left);
		}
		if (node->right != NULL)
		{
			*ParentNode = node;
			*left = false;
			Q.Enqueue(node->right);
		}
		if (node->left == NULL and node->right == NULL)
		{
			*DeepestNode = node;
		}
	}
}

template <typename T>
NODE<T>* BinaryTree<T>::Search(T new_data, NODE<T>** parent_node)
{
	if (Size(root) == 0)
	{
		cout << "Tree is empty!" << endl;
		NODE<T>* temp = NULL;
		return temp;
	}

	Queue<struct NODE<T>*> Q;
	Q.Enqueue(root);

	Queue<struct NODE<T>*> ParentQ;
	NODE<T>* tmp = NULL;
	ParentQ.Enqueue(tmp);

	while (not Q.is_empty())
	{
		struct NODE<T>* node = Q.Dequeue();
		*parent_node = ParentQ.Dequeue();

		if (node->data == new_data)
		{
			return node;
		}
		if (node->left != NULL)
		{
			ParentQ.Enqueue(node);
			Q.Enqueue(node->left);
		}
		if (node->right != NULL)
		{
			ParentQ.Enqueue(node);
			Q.Enqueue(node->right);
		}
	}

	cout << "Element not found in Tree!" << endl;
	return tmp;

}

/* Delete the node and replace it with the
   Deepest rightmost node */
template <typename T>
void BinaryTree<T>::DeleteNode(T data)
{
	if (Size(root) == 0)
	{
		cout << "Tree is empty!" << endl;
		return;
	}

	NODE<T>* search_parent_node = NULL;
	NODE<T>* search_node = Search(data, &search_parent_node);
	if (search_node == NULL)
	{
		cout << "Can not delete data which does not exists!" << endl;
		return;
	}

	NODE<T>* deepest_node = NULL;
	NODE<T>* parent_node = NULL;
	bool left=true;

	Deepest_right_node(&deepest_node, &parent_node, &left);

	if (parent_node == NULL)
	{
		root = NULL;
		cout << "Now the tree is empty!" << endl;
		return;
	}

	int search_data = search_node->data;
	int deepest_data = deepest_node->data;

	search_node->data = deepest_data;
	deepest_node->data = search_data;

	if (left)
	{
		parent_node->left = NULL;
	}
	else
	{
		parent_node->right = NULL;
	}

}


int main()
{
	BinaryTree<int> BT;

	BT.Insert(1);
	BT.Insert(2);
	BT.Insert(3);
	BT.Insert(4);
	BT.Insert(5);
	BT.Insert(6);

	BT.LevelTraversal(BT.root);
	cout << endl;

	BT.InOrderTraversal(BT.root);
	cout << endl;

	BT.PreOrderTraversal(BT.root);
	cout << endl;

	BT.PostOrderTraversal(BT.root);
	cout << endl;

	int size = BT.Size(BT.root);
	cout << size << endl;

	int height = BT.Height(BT.root);
	cout << height << endl;

	NODE<int>* parent_node = NULL;
	int search_data = 2;

	NODE<int>* node = BT.Search(search_data, &parent_node);

	if (node != NULL)
	{
		cout << "Element found! " << search_data << endl;

		if (parent_node == NULL)
		{
			cout << "Element is the root node, no parent" << endl;
		}
		else
		{
			cout << "Element's parent node is " << parent_node->data << endl;
			if (parent_node->left->data == search_data)
			{
				cout << "Element's right sibling is " << parent_node->right->data << endl;
			}
			else
			{
				cout << "Element's left sibling is " << parent_node->left->data << endl;
			}
		}

		if (node->left == NULL and node->right == NULL)
		{
			cout << "Element has no children!" << endl;
		}

		if (node->left != NULL)
		{
			cout << "left child is: " << node->left->data << ", ";
		}
		if (node->right != NULL)
		{
			cout << "right child is: " << node->right->data << " ";
		}
		cout << endl;
	}

	BT.DeleteNode(2);
	BT.LevelTraversal(BT.root);
	cout << endl;

	BT.DeleteTree(BT.root);

	return 0;
}



