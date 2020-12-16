/**
 *        @file: avl_tree.h
 *      @author: Ethan Dowalter
 *        @date: October 4, 2020
 *       @brief: AVL Tree implementation
 */

#ifndef AVL_TREE_H
#define AVL_TREE_H

struct BinaryNode {
	BinaryNode(const int key) : key(key), left(NULL), right(NULL) {}

	~BinaryNode() {
		delete left;
		delete right;
		left = right = NULL;
	}

	void operator =(BinaryNode* other){
		key = other->key;
		bfactor = other->bfactor;
		left = other->left;
		right = other->right;
	}

	int key, bfactor;
	BinaryNode *left, *right;
};

class AVLTree {

	public:
		AVLTree() : root(NULL) {}
		~AVLTree() { 
			delete root;
		}

		void insert(const int key);
		void remove(const int key);
		void print(const char choice);

	private:
		// BinaryNode* insert(const int key, BinaryNode* node);
		void insertIntoAVL(BinaryNode* &root, BinaryNode* newNode, bool &isTaller);
		void removeFromAVL(BinaryNode* &root, int target, bool &isShorter);
		int findMax(BinaryNode* root);
		void rotateToLeft(BinaryNode* &root);
		void rotateToRight(BinaryNode* &root);
		void balanceFromLeft(BinaryNode* &root);		
		void balanceFromRight(BinaryNode* &root);
		void inOrderHeight(BinaryNode* node);
		void inOrderKey(BinaryNode* node);
		int height(BinaryNode* root);
		BinaryNode* root;
};

#endif
