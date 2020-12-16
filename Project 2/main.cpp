/**
 *        @file: main.cpp
 *      @author: Ethan Dowalter
 *        @date: October 4, 2020
 *       @brief: AVL Tree implementation
 */

#include <iostream>
#include "avl_tree.h"
using namespace std;


void printMenu();


int main(int argc, char** argv) {

	AVLTree tree;

	char option;
	int key;

	do {
		printMenu();
		cin >> option;
		switch(option) {
		case 'i':
			cin >> key;
			tree.insert(key);
			break;
		case 'r':
			cin >> key;
			tree.remove(key);
			break;
		case 'h':
			tree.print('h');
			break;
		case 'p':
			tree.print('p');
			break;
		default:
			break;
		}
	} while(option != 'q');
}


void printMenu(){
	cout << "i k : Insert node with key value k into AVL tree." << endl;
	cout << "r k : Remove node with key value k from AVL tree." << endl;
	cout << "h : Print the height of each node using an inorder traversal." << endl;
	cout << "p : Print the key value of each node using an inorder traversal." << endl;
	cout << "q : Quit the program." << endl;
	cout << "Choose an option : ";
}