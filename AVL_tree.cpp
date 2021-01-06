#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "linear_data_structures.h"

using namespace std;

class AVLNode
{
public:
	int key;
	int height;
	AVLNode* parent;
	AVLNode* left;
	AVLNode* right;

	AVLNode(int data)
	{
		key = data;
		parent = NULL;
		left = NULL;
		right = NULL;
		height = 1;
	}
};

AVLNode* Find(int data, AVLNode* root)
{
	if (root == NULL)
	{
		cout << "Search tree is empty!" << endl;
		AVLNode* tmp = NULL;
		return tmp;
	}

	if (root->key == data)
	{
//		cout << "Key found!" << endl;
		return root;
	}
	if (data > root->key)
	{
		if (root->right !=  NULL)
		{
			return Find(data, root->right);
		}
			return root;
	}
	else
	{
		if (root->left != NULL)
		{
			return Find(data, root->left);
		}
		return root;
	}
}

AVLNode* LeftDescendant(AVLNode* N)
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

AVLNode* RightAncestor(AVLNode* N)
{
	if (N->parent == NULL)
	{
		AVLNode* temp = NULL;
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

AVLNode* Next(AVLNode* N)
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

int UpdateHeight(AVLNode** root)
{
	AVLNode* tmp = *root;
	if (*root ==  NULL)
	{
		return 0;
	}
	else
	{
		if (tmp->left == NULL and tmp->right == NULL)
		{
			tmp->height = 1;
			return 1;
		}
	}

	int height_left = UpdateHeight(&(tmp->left));
	int height_right = UpdateHeight(&(tmp->right));

	if (height_left > height_right)
	{
		tmp->height = 1+height_left;
		return 1+height_left;
	}
	else
	{
		tmp->height = 1+height_right;
		return 1+height_right;
	}
}


void Insert(int data, AVLNode** root)
{
	if (*root == NULL)
	{
		*root = new AVLNode(data);
		UpdateHeight(root);
		return;
	}
	AVLNode* newnode = new AVLNode(data);
	AVLNode* position = Find(data, *root);
	if (data >= position->key)
	{
		if (position->right == NULL)
		{
			position->right = newnode;
			newnode->parent = position;
			UpdateHeight(root);
			return;
		}
		newnode->right = position->right;
		position->right->parent = newnode;
		position->right = newnode;
		newnode->parent = position;
		UpdateHeight(root);
		return;
	}
	if (data < position->key)
	{
		if (position->left == NULL)
		{
			position->left = newnode;
			newnode->parent = position;
			UpdateHeight(root);
			return;
		}
		newnode->left = position->left;
		position->left->parent = newnode;
		position->left = newnode;
		newnode->parent = position;
		UpdateHeight(root);
		return;
	}
}

void Delete(AVLNode* node, AVLNode** root)
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
			UpdateHeight(root);
			return;
		}
		if (node->parent->key < node->key)
		{
			node->right->left = NULL;
			free(node);
			UpdateHeight(root);
			return;
		}
	}

	if (node->right == NULL)
	{
		if (node == *root)
		{
			AVLNode* tmp = *root;
			*root = tmp->left;
			tmp->parent = NULL;
			free(node);
			UpdateHeight(root);
			return;
		}
		node->left->parent = node->parent;
		node->parent->left = node->left;
		free(node);
		UpdateHeight(root);
		return;
	}

	AVLNode* next = Next(node);
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
	UpdateHeight(root);
	return;
}

void RangeSearch(int left_limit, int right_limit, AVLNode* root)
{
	AVLNode* leftnode = Find(left_limit, root);
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

void LevelTraversal(AVLNode* root)
{
	if (root == NULL)
	{
		return;
	}

	Queue<AVLNode*> Q;
	Q.Enqueue(root);

	while (not Q.is_empty())
	{
		AVLNode* node = Q.Dequeue();
		cout << node->key << " " << node->height << " ";
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

void DeleteTree(AVLNode** root)
{
	AVLNode* temp = *root;
	if (temp == NULL)
	{
		return;
	}
	DeleteTree(&temp->left);
	DeleteTree(&temp->right);
	free(temp);
}

void InOrderTraversal(AVLNode* root)
{
	if (root == NULL)
	{
		return;
	}
	InOrderTraversal(root->left);
	cout << root->key << " " ;
	InOrderTraversal(root->right);
}

int Size(AVLNode* root)
{
	if (root ==  NULL)
	{
		return 0;
	}

	return 1+Size(root->left)+Size(root->right);
}

void AdjustHeight(AVLNode** node)
{
	AVLNode* tmp = *node;

	if (tmp->left == NULL and tmp->right == NULL)
	{
		tmp->height = 1;
		return;
	}

	if (tmp->right != NULL and tmp->left != NULL)
	{
		if (tmp->left->height >= tmp->right->height)
		{
			tmp->height = 1+tmp->left->height;
			return;
		}
		else
		{
			tmp->height = 1+tmp->right->height;
			return;
		}
	}

	if (tmp->left != NULL and tmp->right == NULL)
	{
		tmp->height = 1+tmp->left->height;
		return;
	}

	if (tmp->right != NULL and tmp->left == NULL)
	{
		tmp->height = 1+tmp->right->height;
		return;
	}
}

void RotateRight(AVLNode** X, AVLNode** root)
{
	AVLNode* tmp = *X;
	AVLNode *P = tmp->parent;
	AVLNode* Y = tmp->left;
	AVLNode* B = Y->right;

	Y->parent = P;
	if (P != NULL)
	{
		if (tmp->key > P->key)
		{
			P->right = Y;
		}
		else
		{
			P->left = Y;
		}
	}

	tmp->parent = Y;
	Y->right = *X;

	if (B != NULL)
	{
		B->parent = *X;
	}
	tmp->left = B;

	AdjustHeight(X);
	AdjustHeight(&Y);
	if (P != NULL)
	{
		AdjustHeight(&P);
	}
	else
	{
		*root = Y;
	}
}

/*************************************************************
 *                /                            /             *
 *               X                            Y              *
 *              / \     RightRotate          / \             *
 *             Y   C    ---------->         A   X            *
 *            / \       <----------            / \           *
 *           A   B      LeftRotate            B   C          *
 *                                                           *
 *************************************************************/

void RotateLeft(AVLNode** Y, AVLNode** root)
{
	AVLNode* tmp = *Y;
	AVLNode* P = tmp->parent;
	AVLNode* X = tmp->right;
	AVLNode* B = X->left;

	X->parent = P;

	if (P != NULL)
	{
		if (tmp->key > P->key)
		{
			P->right = X;
		}
		else
		{
			P->left = X;
		}
	}

	tmp->parent = X;
	X->left = *Y;

	if (B != NULL)
	{
		B->parent = *Y;
	}

	tmp->right = B;

	AdjustHeight(Y);
	AdjustHeight(&X);

	if (P != NULL)
	{
		AdjustHeight(&P);
	}
	else
	{
		*root = X;
	}

}


void RebalanceRight(AVLNode** N, AVLNode** root)
{
	AVLNode* tmp = *N;
	AVLNode* M = tmp->left;

	if(M == NULL)
	{
		RotateRight(N, root);
		return;
	}

	if (M->left == NULL and M->right == NULL)
	{
		RotateRight(N, root);
		return;
	}

	if (M->right != NULL and M->left == NULL)
	{
		RotateLeft(&M, root);
		RotateRight(N, root);
		return;
	}

	if (M->right == NULL and M->left != NULL)
	{
		RotateRight(N, root);
		return;
	}

	if (M->left != NULL and M->right != NULL)
	{
		if (M->right->height > M->left->height)
		{
			RotateLeft(&M, root);
		}
		RotateRight(N, root);
		return;
	}

}

void RebalanceLeft(AVLNode** N, AVLNode** root)
{
	AVLNode* tmp = *N;
	AVLNode* M = tmp->right;

	if(M == NULL)
	{
		RotateLeft(N, root);
		return;
	}

	if (M->left == NULL and M->right == NULL)
	{
		RotateLeft(N, root);
		return;
	}

	if (M->right != NULL and M->left == NULL)
	{
		RotateLeft(N, root);
		return;
	}

	if (M->right == NULL and M->left != NULL)
	{
		RotateRight(&M, root);
		RotateLeft(N, root);
		return;
	}

	if (M->left != NULL and M->right != NULL)
	{
		if (M->left->height > M->right->height)
		{
			RotateRight(&M, root);
		}
		RotateLeft(N, root);
		return;
	}

}

void Rebalance(AVLNode** N, AVLNode** root)
{
	AVLNode* tmp = *N;
	AVLNode* P = tmp->parent;
	AVLNode* left = tmp->left;
	AVLNode* right = tmp->right;

	if (left != NULL and right != NULL)
	{
		if (left->height > right->height+1)
		{
			RebalanceRight(N, root);
		}

		if(right->height > left->height+1)
		{
			RebalanceLeft(N, root);
		}
	}

	if (left == NULL and right != NULL)
	{
		if (right->height > 1)
		{
			RebalanceLeft(N, root);
		}
	}

	if (right == NULL and left != NULL)
	{
		if (left->height > 1)
		{
			RebalanceRight(N, root);
		}
	}

	AdjustHeight(N);

	if (P != NULL)
	{
		Rebalance(&P, root);
	}
}

void AVLInsert(int data, AVLNode** root)
{
	Insert(data, root);
	AVLNode* newnode = Find(data, *root);
	Rebalance(&newnode, root);
}

void AVLDelete(AVLNode* node, AVLNode** root)
{
	AVLNode* M = node->parent;
	Delete(node, root);
	LevelTraversal(*root);
	cout << endl;
	Rebalance(&M, root);
}

int main()
{
	AVLNode* root = NULL;
	AVLInsert(30, &root);
	AVLInsert(40, &root);
	AVLInsert(50, &root);
	AVLInsert(60, &root);
	AVLInsert(70, &root);
	AVLInsert(80, &root);
	AVLInsert(90, &root);
	LevelTraversal(root);
	cout << endl;

	AVLInsert(100, &root);
	AVLInsert(110, &root);
	AVLInsert(120, &root);
	AVLInsert(130, &root);
	LevelTraversal(root);
	cout << endl;

	AVLDelete(root->right->left, &root);
	LevelTraversal(root);
	cout << endl;

	DeleteTree(&root);

}










