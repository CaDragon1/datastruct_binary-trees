/*********************
* Author: Caleb Drake
* Class: COSC 2436 Data Structures
* Program: Binary Tree
* File: bintree.h
* Purpose: This program creates an effective binary tree with full functionality. 
*          This file contains the prototypes, definitions, and includes for the binary tree.
**********************/
#ifndef BINTREE_BINTREE_H
#define BINTREE_BINTREE_H

#include <iostream>
#include "data.h"

using std::cout;	// These will make programming easier on me
using std::endl;
using std::string;


class BinTree {
public:
	//constructor
	BinTree();
	//destructor
	~BinTree();

	// Tree functions
	bool isEmpty();
	int getCount();
	bool getRootData(Data*);
	void clear();
	bool addNode(int, string*);
	bool removeNode(int);
	bool getNode(Data*, int);
	bool contains(int);
	int getHeight();

	// Display functions
	void displayPreOrder();
	void displayPostOrder();
	void displayInOrder();
	void displayTree();		// This was not necessary in the final assignment, but it is useful for testing the values of each node.

private:
	// Private attributes
	DataNode* root;
	int count;

	// Tree functions (private overload)
	void clear(DataNode*);
	bool addNode(DataNode*, DataNode**);
	DataNode* removeNode(int, DataNode*);
	bool getNode(Data*, int, DataNode*);
	bool contains(int, DataNode*);
	int getHeight(DataNode*);
	DataNode* removeFullNode(DataNode*);
	DataNode* removePartNode(DataNode*, DataNode*);
	DataNode* minValueNode(DataNode*);

	// Display functions (private overload)
	void displayPreOrder(DataNode*);
	void displayPostOrder(DataNode*);
	void displayInOrder(DataNode*);
	void displayTree(DataNode*);		
};



#endif /* BINTREE_BINTREE_H */

