#include <iostream>
#include <iomanip>
#include <cstring>
#include "bst.h"

using namespace std;

// change the value of this variable to be your own name instead of "I. Forgot"
const char	BST::YOUR_NAME[]{"Julian Kaufman"};

// change the value of this variable to true if you're doing the Premium version
const bool	BST::PREMIUM_VERSION{true};

BST::BST(int capacity):
	items{new Item[capacity]},
	capacity{capacity}
{
}

BST::~BST()
{
	delete [] items;
}

// insert a new item into the BST
void BST::insert(const GCS& gcs)
{
	int idx = 0;
	bool inserted = false;

	/*
	//array full, grow it
	if (count == capacity)
	{
		capacity = 2 * capacity;
		Item* newArr = new Item[capacity];
		for(int i = 0; i < count; i++)
		{
			if (items[i].gcs.getName())
			{
				newArr[i].gcs = items[i].gcs;
				//delete items[i].gcs.getName();
			}
			items[i].gcs.setName("");
		}
		
		//capacity = 2 * capacity;
		delete [] items;
		items = newArr;

	}
	*/

	//array empty, insert GCS into root node
	if (items[idx].gcs.getName() == nullptr)
	{
		items[idx].gcs = gcs;
		count++;
		inserted = true;
	}
	
	while(!inserted)
	{
		//grow array if necessary
		//if(idx > capacity)
			//growArray();

		//left child insert
		if (gcs < items[idx].gcs)
		{	
			//if no left child, insert
			if (hasLeftChild(idx) == false) 
			{
				idx = 2 * idx + 1;
				if(idx > capacity)
					growArray();
				items[idx].gcs = gcs;
				count++;
				inserted = true;
			}
			else if (hasLeftChild(idx))
			//(items[2 * idx + 1].gcs.getName())
			{
				idx = 2 * idx + 1;
			}
		}
		
		//right child insert
		else if (items[idx].gcs < gcs)
		{
			if (hasRightChild(idx) == false) 
			//(items[(2 * idx + 2)].gcs.getName() == nullptr)
			{
				if(idx > capacity)
					growArray();
				items[2 * idx + 2].gcs = gcs;
				count++;
				inserted = true;
			}
			else if (hasRightChild(idx)) 
			//(items[2* idx + 1].gcs.getName())
			{
				idx = 2 * idx + 2;
			}
		}
	}
}

// retrieve item associated with key
// returns true if it finds key, false if it can't
bool BST::retrieve(const char* key, GCS const *& gcs) const
{
	int idx = 0;
	int checked = 0;

	while (checked < count && idx < capacity)
	{
		if (strcmp(key,items[idx].gcs.getName()) == 0)
		{
			gcs = &items[idx].gcs;
			return true;
		}
		else if (strcmp(key,items[idx].gcs.getName()) == -1)
		{
			idx = (2 * idx + 1);
			checked++;
			continue;
		}
		else if (strcmp(key,items[idx].gcs.getName()) == 1)
		{
			idx = (2 * idx + 2);
			checked++;
			continue;
		}
	}

	return false;
}

// remove item associated with key from BST
bool BST::remove(const char* key)
{
	int idx = 0;
	retrieveHelper(idx, key);
	if (idx == -1)
		return false;
	

	//remove leaf
	if (isLeaf(idx))
	{
		items[idx].gcs.setName("");
		count--;
		return true;
	}
	
	//has one child
	if(hasChildren(idx))
	{
		removeHelper(idx);
		count--;
		return true;
	}



	//has two children
	if(getLeftChild(idx) && getRightChild(idx))
	{
		int remove = findInorderSuccessor((2* idx + 2), key);
		//cout << "is this right?" << items[remove].gcs << endl;
		items[idx].gcs.setName(items[remove].gcs.getName());
		count--;
		if(hasChildren(remove))
			removeHelper(remove);
		else if (hasLeftChild(idx) && hasRightChild(idx))
		{
			//BST::remove(items[remove].gcs.getName());
			remove = findInorderSuccessor(remove, key);
			items[remove].gcs.setName("");
		}
		return true;
	}
	
	

	return false;
}

// return number of items contained in the BST
int BST::getSize(void) const
{
	return count;
}

// display items in the tree by traversing the array from beginning to end
void BST::displayArrayOrder(ostream& out) const
{
	BST::displayHeadings(out);
	for(int i = 0; i < capacity; i++)
	{
		if (items[i].gcs.getName())
		{
			printItem(i, out);

			//old print
			//out << left << setw(24) <<  items[i].gcs;
			//if (isLeaf(i))
				//out << setw(5) << left << "leaf";
			//else
				//out << setw(5) << "";
			//out <<  "  " << setw(5) << right << i << endl;
		}
	}

	out << left << setw(37) << ("(items printed)")
		<< "(" << count << ")" << endl;
}

// display items in the tree in preorder
void BST::displayPreOrder(ostream& out) const
{
	/*
	preorder(n)
		touch(n)
		preorder(left)
		preorder(right)
	*/
	displayHeadings(out);
	preOrder(0, out);
	out << left << setw(37) << ("(items printed)")
		<< "(" << count << ")" << endl;
}

// display items in the tree in inorder
void BST::displayInOrder(ostream& out) const
{
	displayHeadings(out);
	inOrder(0, out);
	out << left << setw(37) << ("(items printed)")
		<< "(" << count << ")" << endl;

}

// display items in the tree in postorder
void BST::displayPostOrder(ostream& out) const
{
	/*
	postorder(n)
		postorder(left)
		postorder(right)
		touch(n)
	*/
	displayHeadings(out);
	postOrder(0, out);
	out << left << setw(37) << ("(items printed)")
		<< "(" << count << ")" << endl;

	
}

void BST::displayHeadings(ostream& out) const
{
	out << setw(24) << left << "name"
		<< setw(5) << "leaf?" << "  " 
		<< setw(5) << "index" << endl
		<< setw(4) << setfill('-') << ""
		<< setw(20) << setfill(' ') << ""
		<< setw(5) << setfill('-') << "" << "  "
		<< setw(5) << "" << setfill(' ') << endl;

}

void BST::printItem(int i, ostream& out) const
{
	out << left << setw(24) <<  items[i].gcs;
		if (isLeaf(i))
			out << setw(5) << left << "leaf";
		else
			out << setw(5) << "";
		out <<  "  " << setw(5) << right << i << endl;

}

bool BST::hasChildren(int idx) const
{
	if (hasLeftChild(idx) && hasRightChild(idx))
		return false;
	else if (hasLeftChild(idx) || hasRightChild(idx))
		return true;
	else
		return false;
}

bool BST::hasLeftChild(int idx) const
{
	if((2 * idx + 1) > capacity)
		return false;
	else if (items[2 * idx + 1].gcs.getName())
		return true;
	else
		return false;
}

bool BST::hasRightChild(int idx) const
{
	if ((2 * idx + 1) > capacity)
		return false;
	else if (items[2 * idx + 2].gcs.getName())
		return true;
	else
		return false;
}

bool BST::isLeaf(int idx) const
{
	if (BST::hasLeftChild(idx) == false && BST::hasRightChild(idx) == false)
		return true;
	else
		return false;
}

int BST::getLeftChild(int idx)
{
	return (2 * idx + 1);
}

int BST::getRightChild(int idx)
{
	return (2 * idx + 2);
}

int BST::preOrder(int idx, ostream& out) const
{
	/*
	preorder(n)
		touch(n)
		preorder(left)
		preorder(right)
	*/
	printItem(idx, out);
	if (hasLeftChild(idx))
		preOrder(2 * idx + 1, out);
	if (hasRightChild(idx))
		preOrder(2 * idx + 2, out);
	//else
		return -1;
	

}


int BST::postOrder(int idx, ostream& out) const
{
	/*
	postorder(n)
		postorder(left)
		postorder(right)
		touch(n)
	*/
	if (hasLeftChild(idx))
		postOrder(2 * idx + 1, out);
	if (hasRightChild(idx))
		postOrder(2 * idx + 2, out);
	printItem(idx, out);
	
	return -1;

}

int BST::inOrder(int idx, ostream& out) const
{
	/*
	inorder(n)
		inorder(left)
		touch(n)
		inorder(right)
	*/

	if (hasLeftChild(idx))
		inOrder(2 * idx + 1, out);
	printItem(idx, out);
	if (hasRightChild(idx))
		inOrder(2 * idx + 2, out);
	
	return -1;
}

int BST::findInorderSuccessor(int idx, const char* key)
{
	
	if (hasLeftChild(idx))
	{
		idx = 2 * idx +1;
		findInorderSuccessor((idx), key);
	}
	
	return idx;
}

int BST::removeHelper(int idx)
{
	//if ((hasLeftChild(idx) || hasRightChild(idx) == true) 
	//&& (hasLeftChild(idx) && hasRightChild(idx) == false))
	//{
		if(hasLeftChild(idx))
		{
			items[idx].gcs.setName(items[2*idx+1].gcs.getName());
			items[2*idx+1].gcs.setName("");
			
		}
		else
		{
			items[idx].gcs.setName(items[2*idx+2].gcs.getName());
			items[2 * idx + 2].gcs.setName("");
		}
	//}
		return 0;
}

void BST::retrieveHelper(int& idx, const char* key) const
{
	if (idx < capacity && items[idx].gcs.getName())
	{
		if (strcmp(key,items[idx].gcs.getName()) == 0)
		{
			return;
		}
		else if (strcmp(key,items[idx].gcs.getName()) == -1)
		{
			idx = (2 * idx + 1);
			retrieveHelper(idx, key);
		}
		else if (strcmp(key,items[idx].gcs.getName()) == 1)
		{
			idx = (2 * idx + 2);
			retrieveHelper(idx, key);
		}
	}
	else
		idx = -1;

	
}

void BST::growArray()
{
	int oldCapacity = capacity;
		capacity = 2 * capacity;
		Item* newArr = new Item[capacity];
		for(int i = 0; i < oldCapacity; i++)
		{
			if (items[i].gcs.getName())
			{
				newArr[i].gcs = items[i].gcs;
				//delete items[i].gcs.getName();
			}
			items[i].gcs.setName("");
		}
		
		//capacity = 2 * capacity;
		delete [] items;
		items = newArr;


}
