/**
 *        @file: avl_tree.cpp
 *      @author: Ethan Dowalter
 *        @date: October 4, 2020
 *       @brief: AVL Tree implementation
 */

#include <iostream>
#include "avl_tree.h"
using namespace std;


void AVLTree::rotateToLeft(BinaryNode* &root){
	BinaryNode *p; //pointer to the root of the right subtree of root
	if (root == NULL)
		cerr << "Error in the tree" << endl;
	else if (root->right == NULL)
		cerr << "Error in the tree:" << " No right subtree to rotate." << endl;
	else
	{
		p = root->right;
		root->right = p->left; //the left subtree of p becomes the right subtree of root
		p->left = root;
		root = p; //make p the new root node
	}
}


void AVLTree::rotateToRight(BinaryNode* &root){
	BinaryNode *p; //pointer to the root of the left subtree of root
	if (root == NULL)
		cerr << "Error in the tree" << endl;
	else if (root->left == NULL)
		cerr << "Error in the tree:" << " No left subtree to rotate." << endl;
	else
	{
		p = root->left;
		root->left = p->right; //the right subtree of p becomes the left subtree of root
		p->right = root;
		root = p; //make p the new root node
	}
}


void AVLTree::balanceFromLeft(BinaryNode* &root){
	BinaryNode *p;
	BinaryNode *w;
	p = root->left; //p points to the left subtree of root
	switch (p->bfactor)
	{
		case -1:
			root->bfactor = 0;
			p->bfactor = 0;
			rotateToRight(root);
			break;
		case 0:
			root->bfactor = 1;
			p->bfactor = -1;
			rotateToRight(root);
			break;
		case 1:
			w = p->right;
			switch (w->bfactor) //adjust the balance factors
			{
				case -1:
				root->bfactor = 1;
				p->bfactor = 0;
				break;
				case 0:
				root->bfactor = 0;
				p->bfactor = 0;
				break;
				case 1:
				root->bfactor = 0;
				p->bfactor = -1;
			}
			w->bfactor = 0;
			rotateToLeft(p);
			root->left = p;
			rotateToRight(root);
	}
}


void AVLTree::balanceFromRight(BinaryNode* &root){
	BinaryNode *p;
	BinaryNode *w;
	p = root->right; 			//p points to the left subtree of root
	switch (p->bfactor)
	{
		case -1:
			w = p->left;
			switch (w->bfactor) //adjust the balance factors
			{
				case -1:
					root->bfactor = 0;
					p->bfactor = 1;
					break;
				case 0:
					root->bfactor = 0;
					p->bfactor = 0;
					break;
				case 1:
				root->bfactor = -1;
				p->bfactor = 0;
			}
			w->bfactor = 0;
			rotateToRight(p);
			root->right = p;
			rotateToLeft(root);
			break;
		case 0:
			root->bfactor = -1;
			p->bfactor = 1;
			rotateToLeft(root);
			break;
		case 1:
			root->bfactor = 0;
			p->bfactor = 0;
			rotateToLeft(root);
	}
}


void AVLTree::print(const char choice){
	if (choice == 'p')
	{
		inOrderKey(root);
	}
	else if (choice == 'h')
	{
		inOrderHeight(root);
	}
	cout << endl;
}


void AVLTree::inOrderHeight(BinaryNode* node){
	if (node != NULL)
	{
		inOrderHeight(node->left);
		cout << height(node) << ' ';	//print the height of the tree
		inOrderHeight(node->right);
	}
}


void AVLTree::inOrderKey(BinaryNode* node){
	if (node != NULL)
	{
		inOrderKey(node->left);
		cout << node->key << ' ';		//print the element inside the node
		inOrderKey(node->right);
	}
}


int AVLTree::height(BinaryNode* root){
	int h = 0;
	if (root != NULL)
	{
		int Lheight = height(root->left);
		int Rheight = height(root->right);
		int maxheight = max(Lheight, Rheight);
		h = maxheight + 1;	
	}
	return h;
}


void AVLTree::remove(const int key){
	bool isShorter = false;
	removeFromAVL(root, key, isShorter);
}


void AVLTree::removeFromAVL(BinaryNode* &root, int target, bool &isShorter){
	if (root == NULL)
	{
		cerr << "Number not found." << endl;
		return;
	}
	else if (target < root->key)		//target is maybe in the left subtree
	{
		removeFromAVL(root->left, target, isShorter);
		if (isShorter)
		{
			switch (root->bfactor)
			{
				case -1:
					root->bfactor = 0;
					isShorter = true;
					break;
				case 0:
					root->bfactor = 1;
					isShorter = false;
					break;
				case 1:
					if (root->right->bfactor == 0)
					{
						isShorter = false;
					}
					else
					{
						isShorter = true;
					}
					balanceFromRight(root);
			}
		}		
	}
	else if (target > root->key)		//target is maybe in the right subtree
	{
		removeFromAVL(root->right, target, isShorter);
		if (isShorter)
		{
			switch (root->bfactor)
			{
				case -1:
					if (root->left->bfactor == 0)
					{
						isShorter = false;
					}
					else
					{
						isShorter = true;
					}
					balanceFromLeft(root);
					break;
				case 0:
					root->bfactor = -1;
					isShorter = false;
					break;
				case 1:
					root->bfactor = 0;
					isShorter = true;
					break;
			}
		}	
	}
	else
	{
		/// Case 1 - no children
		if (root->left == NULL && root->right == NULL)
		{
			root = NULL;
			isShorter = true;
			return;
		}
		
		/// Case 2 - left child only
		else if (root->right == NULL)
		{
			root = root->left;
			isShorter = true;
			return;
		}
		
		/// Case 3 - right child only
		else if (root->left == NULL)
		{
			root = root->right;
			isShorter = true;
			return;
		}
		
		/// Case 4 - two children
		else
		{
			root->key = findMax(root->left);
			removeFromAVL(root->left, root->key, isShorter);

			int bfactor = height(root->right) - height(root->left);			//handle the special case for when rotation is needed
			if (bfactor > 1)
			{
				balanceFromRight(root);
			}
			
			return;
		}
	}	
}


int AVLTree::findMax(BinaryNode* root){
	while (root->right != NULL)
	{
		root = root->right;
	}
	return root->key;
}


void AVLTree::insert(const int key){
	bool isTaller = false;
	BinaryNode *newNode = new BinaryNode(key);		//create new node with the key in it
	newNode->bfactor = 0;							//default bfactor is 0 because insertion will happen at a leaf node
	insertIntoAVL(root, newNode, isTaller);
}


void AVLTree::insertIntoAVL(BinaryNode* &root, BinaryNode* newNode, bool &isTaller){
	if (root == NULL)
	{
		root = newNode;			//create new node if tree is empty
		isTaller = true;		//height increases
	}
	else if (root->key == newNode->key)
		cerr << "No duplicates are allowed." << endl;
	else if (root->key > newNode->key) //newItem goes in the left subtree
	{
		insertIntoAVL(root->left, newNode, isTaller);
		if (isTaller) //after insertion, the subtree grew in height
			switch (root->bfactor)
			{
				case -1:
					balanceFromLeft(root);
					isTaller = false;
					break;
				case 0:
					root->bfactor = -1;
					isTaller = true;
					break;
				case 1:
					root->bfactor = 0;
					isTaller = false;
			}
	}
	else
	{
		insertIntoAVL(root->right, newNode, isTaller);
		if (isTaller) //after insertion, the subtree grew in height
			switch (root->bfactor)
			{
				case -1:
					root->bfactor = 0;
					isTaller = false;
					break;
				case 0:
					root->bfactor = 1;
					isTaller = true;
					break;
				case 1:
					balanceFromRight(root);
					isTaller = false;
			}
	}
}