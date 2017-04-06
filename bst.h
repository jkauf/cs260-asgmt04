#ifndef _BST_H_
#define _BST_H_

// do not change this file except within the private section of the BST class,
// where you can declare variables and/or functions

#include "gcs.h"

class BST								// a Binary Search Tree (BST)
{
public:
	static const char	YOUR_NAME[];		// used for printing out programmer's name
	static const bool	PREMIUM_VERSION;	// used to designate Regular vs. Premium

	BST(int capacity = 5);				// constructor (default if no argument supplied)
	~BST();								// destructor

	void insert(const GCS& gcs);		// insert a new item into BST
	bool remove(const char* key);		// remove item associated with key from BST
	bool retrieve(const char* key, GCS const *& gcs) const;	// retrieve item associated with key, if any
	int getSize(void) const;			// return number of items contained in the BST

	// see comments in bst.cpp for what these member functions do
	void displayArrayOrder(std::ostream& out) const;
	void displayPreOrder(std::ostream& out) const;
	void displayInOrder(std::ostream& out) const;
	void displayPostOrder(std::ostream& out) const;

private:
	// specify what is stored at each position in the array
	// (you can add additional items to this struct)
	struct Item
	{
		GCS		gcs;		// the GCS instance must be specified this way, NOT as a pointer
	};

	// pointer to the array
	Item*	items;
	int		count = 0;
	int		capacity;

	int getLeftChild(int idx);
	int getRightChild(int idx);
	bool hasChildren(int idx) const;
	bool hasLeftChild(int idx) const;
	bool hasRightChild(int idx) const;
	void displayHeadings(std::ostream& out) const;
	void printItem(int i, std::ostream& out) const;
	int preOrder(int idx, std::ostream& out) const;
	int postOrder(int idx, std::ostream& out) const;
	int inOrder(int idx, std::ostream& out) const;
	bool isLeaf(int idx) const;
	int findInorderSuccessor(int idx, const char* key);
	void retrieveHelper(int& idx, const char* key) const;
	int removeHelper(int idx);
	void growArray();
};

#endif
