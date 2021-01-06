#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "linear_data_structures.h"

using namespace std;

class BSTNode
{
public:
	int key;
	BSTNode* parent;
	BSTNode* left;
	BSTNode* right;

	BSTNode(int data)
	{
		key = data;
		parent = NULL;
		left = NULL;
		right = NULL;
	}
};

BSTNode* Find(int data, BSTNode* root)
{
	if (root == NULL)
	{
		cout << "Search tree is empty!" << endl;
		BSTNode* tmp = NULL;
		return tmp;
	}

	if (root->key == data)
	{
		cout << "Key found!" << endl;
		return root;
	}
	if (data > root->key)
	{
		if (root->right !=  NULL)
		{
			return Find(data, root->right);
		}
		else
		{
//			cout << "Key not found! Nearest node where it should have been is.." << endl;
			return root;
		}

	}
	else
	{
		if (root->left != NULL)
		{
			return Find(data, root->left);
		}
		else
		{
//			cout << "Key not found! Nearest node where it should have been is.." << endl;
			return root;
		}

	}
}

BSTNode* LeftDescendant(BSTNode* N)
{
	if (N->left == NULL)
	{
		return N;
	}
	else
	{
		return LeftDescendant(N->left);
	}
}

BSTNode* RightAncestor(BSTNode* N)
{
	if (N->parent == NULL)
	{
		BSTNode* temp = NULL;
		return temp;
	}
	if (N->parent->key > N->key)
	{
		return N->parent;
	}
	else
	{
		return RightAncestor(N->parent);
	}
}

BSTNode* Next(BSTNode* N)
{
	if (N->right != NULL)
	{
		return LeftDescendant(N->right);
	}
	else
	{
		return RightAncestor(N);
	}
}

void Insert(int data, BSTNode** root)
{
	if (*root == NULL)
	{
		*root = new BSTNode(data);
		return;
	}
	BSTNode* newnode = new BSTNode(data);
	BSTNode* position = Find(data, *root);
	if (data >= position->key)
	{
		if (position->right == NULL)
		{
			position->right = newnode;
			newnode->parent = position;
			return;
		}
		newnode->right = position->right;
		position->right->parent = newnode;
		position->right = newnode;
		newnode->parent = position;
		return;
	}
	if (data < position->key)
	{
		if (position->left == NULL)
		{
			position->left = newnode;
			newnode->parent = position;
			return;
		}
		newnode->left = position->left;
		position->left->parent = newnode;
		position->left = newnode;
		newnode->parent = position;
		return;
	}
}

void Delete(BSTNode* node, BSTNode** root)
{
	if (*root == NULL)
	{
		cout << "Tree is empty!" << endl;
		return;
	}

	if (node->left == NULL and node->right == NULL)
	{
		if (node->parent == NULL)
		{
			*root = NULL;
			return;
		}
		if (node->parent->key > node->key)
		{
			node->parent->left = NULL;
			free(node);
			return;
		}
		if (node->parent->key < node->key)
		{
			node->right->left = NULL;
			free(node);
			return;
		}
	}

	if (node->right == NULL)
	{
		if (node == *root)
		{
			BSTNode* tmp = *root;
			*root = tmp->left;
			tmp->parent = NULL;
			free(node);
			return;
		}
		node->left->parent = node->parent;
		node->parent->left = node->left;
		free(node);
		return;
	}

	BSTNode* next = Next(node);
	cout << next->key << endl;
	node->key = next->key;
	if (next->right != NULL)
	{
		next->right->parent = next->parent;
		next->parent->left = next->right;
	}
	else
	{
		if (next->parent->key > next->key)
		{
			next->parent->left = NULL;
		}
		else
		{
			next->parent->right = NULL;
		}
	}
	free(next);

	return;

}

void RangeSearch(int left_limit, int right_limit, BSTNode* root)
{
	BSTNode* leftnode = Find(left_limit, root);
	if (leftnode == NULL)
	{
		return;
	}
	if (leftnode->key > right_limit)
	{
		cout << "No element in the given range!" << endl;
		return;
	}
	while (leftnode != NULL and leftnode->key <= right_limit)
	{
		if (leftnode->key > left_limit)
		{
			cout << leftnode->key << " " ;
		}
		leftnode = Next(leftnode);
	}
	cout << endl;
}

void LevelTraversal(BSTNode* root)
{
	if (root == NULL)
	{
		return;
	}

	Queue<BSTNode*> Q;
	Q.Enqueue(root);

	while (not Q.is_empty())
	{
		BSTNode* node = Q.Dequeue();
		cout << node->key << " " ;
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

void DeleteTree(BSTNode** root)
{
	BSTNode* temp = *root;
	if (temp == NULL)
	{
		return;
	}
	DeleteTree(&temp->left);
	DeleteTree(&temp->right);
	free(temp);
}

void InOrderTraversal(BSTNode* root)
{
	if (root == NULL)
	{
		return;
	}
	InOrderTraversal(root->left);
	cout << root->key << " " ;
	InOrderTraversal(root->right);
}

int Height(BSTNode* root)
{
	if (root ==  NULL)
	{
		return 0;
	}
	else
	{
		if (root->left == NULL and root->right == NULL)
		{
			return 1;
		}
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

int Size(BSTNode* root)
{
	if (root ==  NULL)
	{
		return 0;
	}

	return 1+Size(root->left)+Size(root->right);
}

void InOrder(BSTNode* root, int* elements, int* index)
{
	if (root == NULL)
	{
		return;
	}

	InOrder(root->left, elements, index);
	*(elements+*index) = root->key;
	*index += 1;
	InOrder(root->right, elements, index);

}

void SortedArraytoBST(BSTNode** root, int* elements, int start, int end)
{
	if (end == start+1)
	{
		Insert(elements[end], root);
		Insert(elements[start], root);
		return;
	}

	if (start == end)
	{
		Insert(elements[start], root);
		return;
	}

	int size = end-start+1;
	int middle = size/2;
	Insert(elements[start+middle], root);

	if (start+middle-1 >= start)
	{
		SortedArraytoBST(root, elements, start, start+middle-1);
	}

	if (start+middle+1 <=  end)
	{
		SortedArraytoBST(root, elements, start+middle+1, end);
	}

}

BSTNode* BalanceBST(BSTNode* root)
{
	if (root == NULL)
	{
		BSTNode* tmp = NULL;
		return tmp;
	}

	int size = Size(root);
	int *elements = new int[size];
	int index = 0;
	InOrder(root, elements, &index);

	BSTNode* newroot = NULL;

	SortedArraytoBST(&newroot, elements, 0, size-1);

	return newroot;
}


int main()
{
	BSTNode* Root = NULL;
	Insert(60, &Root);
	Insert(50, &Root);
	Insert(40, &Root);
	Insert(30, &Root);
	Insert(20, &Root);
	Insert(25, &Root);
	Insert(27, &Root);
	LevelTraversal(Root);
	cout << endl;

	BSTNode* node = Find(20, Root);
	cout << node->key << endl;

	BSTNode* next = Next(node);
	if (next != NULL)
	{
		cout << "Next element is: " << endl;
		cout << next->key << endl;
	}
	else
	{
		cout << "Given key is the maximum in the tree! Can not find next big element" << endl;
	}

	cout << "Elements in given range are: " << endl;
	RangeSearch(5, 30, Root);

	Delete(Root->left, &Root);
	cout << "Elements after Deletion are: " << endl;
	LevelTraversal(Root);
	cout << endl;

	cout << "Elements in sorted order are: " << endl;
	InOrderTraversal(Root);
	cout << endl;

	cout << "Height of the tree: " << endl;
	int height = Height(Root);
	cout << height << endl;

	BSTNode* newroot = BalanceBST(Root);

	DeleteTree(&Root);

	LevelTraversal(newroot);
	cout << endl;

	cout << "Height of the new tree: " << endl;
	int height1 = Height(newroot);
	cout << height1 << endl;

	return 0;
}


