/*********************
* Author: Caleb Drake
* Class: COSC 2436 Data Structures
* Program: Binary Tree
* File: bintree.cpp
* Purpose: This program creates an effective binary tree with full functionality.
*          This file contains the methods and necessary functions for creating, managing, navigating, and deleting a binary tree.
**********************/
#include "bintree.h"

// Constructor and destructor
BinTree::BinTree() {
	count = 0;
}

BinTree::~BinTree() {
	clear(root);
}


/* ---------- PUBLIC METHODS -----------
    - Tree methods */
bool BinTree::isEmpty() {
	bool empty = true;
	if (count > 0) {
		empty = false;
	}
	return empty;
}

int BinTree::getCount() {
	return count;
}

bool BinTree::getRootData(Data* node) {
	bool got = false;
	if (root) {
		node->id = root->data.id;
		node->information = root->data.information;
		got = true;
	}
	else {
		node->id = -1;
		node->information = "";
	}
	return got;
}

void BinTree::clear() {
	clear(root);
	count = 0;
	root = NULL;
}

bool BinTree::addNode(int id, string* data) {
	bool added = false;
	if (id > 0 && *data != "") {
		DataNode* newNode = new DataNode;
		newNode->data.id = id;
		newNode->data.information = *data;
		newNode->left = NULL;
		newNode->right = NULL;
		added = addNode(newNode, &root);
		if (added) {
			count++;
		}
	}
	return added;
}

bool BinTree::removeNode(int id) {
	bool removed = false;
	int tempCount = count;

	if (id > 0) {
		root = removeNode(id, root);
	}
	
	if (tempCount > count) {
		removed = true;
	}
	return removed;
}

bool BinTree::getNode(Data* node, int id) {
	bool got = false;
	if (id > 0 && root) {
		got = getNode(node, id, root);
	}
	return got;
}

bool BinTree::contains(int id) {
	cout << "    CHECKING ID " << id << endl;
	bool has = false;
	if (id > 0 && root) {
		has = contains(id, root);
	}
	return has;
}

int BinTree::getHeight() {
	return getHeight(root);
}


/* Public methods
	- Display methods */
void BinTree::displayPreOrder() {
	displayPreOrder(root);
}
void BinTree::displayPostOrder() {
	displayPostOrder(root);
}
void BinTree::displayInOrder() {
	displayInOrder(root);
}
void BinTree::displayTree() {
	displayTree(root);
}


/* ---------- PRIVATE METHOD OVERLOADS ----------
	- Tree methods */
void BinTree::clear(DataNode* tempRoot) {
	if (tempRoot) {
		clear(tempRoot->left);
		clear(tempRoot->right);
		tempRoot->left = NULL;
		tempRoot->right = NULL;
		delete tempRoot;
	}
	return;
}

bool BinTree::addNode(DataNode* newNode, DataNode** localRoot) {
	bool added = false;
	if (!(*localRoot)) {												// If the given root is null, create a new root and add the data to it.
		*localRoot = newNode;
		added = true;
	}
	else {																// If the new data's id is less than the given root's id, recurse left.
		if (newNode->data.id < (*localRoot)->data.id) {					// If greater, recurse right.	
			localRoot = &(*localRoot)->left;							// If equal, it's a repeat and will not be added to the tree.
			added = addNode(newNode, localRoot);
		}
		else if (newNode->data.id > (*localRoot)->data.id) {
			localRoot = &(*localRoot)->right;
			added = addNode(newNode, localRoot);
		}
	}
	return added;
}

DataNode* BinTree::removeNode(int id, DataNode* localRoot) {
	if (localRoot) {
		if (id < localRoot->data.id){						// Recurse until we find the needed node
			localRoot->left = removeNode(id, localRoot->left);
		}
		else if (id > localRoot->data.id) {
			localRoot->right = removeNode(id, localRoot->right);
		}

		else {	// The localRoot is the node we need to remove
			if (!localRoot->left) {											// If the localRoot is a node with only a right child:
				localRoot = removePartNode(localRoot, localRoot->right);	// Call the removePartNode function with the localRoot and its right branch
			}
			else if (!localRoot->right) {									// Do the same if the localRoot only has a left child
				localRoot = removePartNode(localRoot, localRoot->left);
			}
			else {															// If it has a left AND right child:
				localRoot = removeFullNode(localRoot);						// Call the removeFullNode function.
			}
		}
	}
	return localRoot;
}

bool BinTree::getNode(Data* node, int id, DataNode* localRoot) {
	bool has = false;
	if (localRoot) {
		if (id == localRoot->data.id) {
			node->id = localRoot->data.id;
			node->information = localRoot->data.information;
			has = true;
		}
		else if (id < localRoot->data.id) {
			has = getNode(node, id, localRoot->left);
		}
		else {
			has = getNode(node, id, localRoot->right);
		}
	}
	return has;
}

bool BinTree::contains(int id, DataNode* localRoot) {
	bool has = false;
	if (localRoot) {
		if (id == localRoot->data.id) {
			has = true;
		}
		else if (id < localRoot->data.id) {
			has = contains(id, localRoot->left);
		}
		else {
			has = contains(id, localRoot->right);
		}
	}
	return has;
}

int BinTree::getHeight(DataNode* localRoot) {
	int lHeight = 0;		// Left height
	int rHeight = 0;		// Right height
	int returnHeight = 0;	// Final height to return

	if (localRoot) {
		if (localRoot->left) {
			lHeight = getHeight(localRoot->left);
		}
		if (localRoot->right) {
		    rHeight = getHeight(localRoot->right);
		}

		if (lHeight > rHeight) {
			returnHeight = lHeight + 1;
		}
		else {
			returnHeight = rHeight + 1;
		}
	}
	return returnHeight;
}

DataNode* BinTree::removePartNode(DataNode* localRoot, DataNode* childNode) {
	delete localRoot;				// Delete the localRoot (the one we want removed)
	localRoot = childNode;			// Set the new localRoot pointer to the childRoot pointer to keep the root connected above
	count--;

	return localRoot;
}

DataNode* BinTree::removeFullNode(DataNode* localRoot) {																
	DataNode* tempRoot = minValueNode(localRoot);							// Set a tempRoot to the child node with the lowest id.
	localRoot->data.id = tempRoot->data.id;									// The localRoot's data is set to the lowest id child, effectively moving it up
	localRoot->data.information = tempRoot->data.information;				//		to the localRoot's position in the tree.
	localRoot->right = removeNode(tempRoot->data.id, localRoot->right);		// We then want to remove the lowest id child node to prevent duplicates.
	count--;

	return localRoot;
}

DataNode* BinTree::minValueNode(DataNode* localRoot) {
	DataNode* current = localRoot;
	while (current && current->left) {
		current = current->left;
	}
	return current;
}

/* Private method overloads
	- Display methods */
void BinTree::displayPreOrder(DataNode* localRoot) {
	if (localRoot) {
		cout << localRoot->data.id << " " << localRoot->data.information << endl;

		if (localRoot->left) {
			displayPreOrder(localRoot->left);
		}
		if (localRoot->right) {
			displayPreOrder(localRoot->right);
		}
	}
}
void BinTree::displayPostOrder(DataNode* localRoot) {
	if (localRoot) {
		if (localRoot->left) {
			displayPostOrder(localRoot->left);
		}
		if (localRoot->right) {
			displayPostOrder(localRoot->right);
		}
		cout << localRoot->data.id << " " << localRoot->data.information << endl;
	}
}
void BinTree::displayInOrder(DataNode* localRoot) {
	if (localRoot) {
		if (localRoot->left) {
			displayInOrder(localRoot->left);
		}
		cout << localRoot->data.id << " " << localRoot->data.information << endl;

		if (localRoot->right) {
			displayInOrder(localRoot->right);
		}
	}
}

void BinTree::displayTree(DataNode* localRoot) {
	cout << "DISPLAY TREE" << endl;
	cout << "==============================================" << endl;
	cout << "Tree is ";
	if (count > 0) {
		cout << "NOT ";
	}
	cout << "empty" << endl;

	cout << "Height " << getHeight() << endl;
	cout << "Node count: " << count << endl << endl;

	cout << "Pre-Order Traversal" << endl;
	displayPreOrder(root);
	cout << endl;
	cout << "In-Order Traversal" << endl;
	displayInOrder(root);
	cout << endl;
	cout << "Post-Order Traversal" << endl;
	displayPostOrder(root);
	cout << "==============================================" << endl << endl;
}