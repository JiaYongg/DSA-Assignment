// BST.cpp - Implementation of Binary Search Tree
#include "BST.h"
#include <time.h>

#define max(x,y) ((x > y)? x : y)

// constructor
BST::BST()
{
	root = NULL;
}

// search an item in the binary search tree
BinaryNode* BST::search(tm date, string guestName, string roomType)
{
	return search(root, date, guestName, roomType);
}

BinaryNode* BST::search(BinaryNode* t, tm date, string guestName, string roomType)
{
	if (t == NULL)	// item not found
		return NULL;
	else
	{
		time_t checkindate = mktime(&t->item.checkinDate);
		time_t inputdate = mktime(&date);
		double diff = difftime(checkindate, inputdate);
		// use difftime to find the difference between the input date and the current iteration date
		if (diff == 0 && t->item.bookingGuestName == guestName && t->item.bookingRoomType == roomType)// item found
			return t;
		else
			if (diff < 0)	// search in left subtree
				return search(t->left, date, guestName, roomType);
			else					// search in right subtree
				return search(t->right, date, guestName, roomType);
	}
}


// insert an item to the binary search tree
void BST::insert(Booking b)
{
	insert(root, b);
}

void BST::insert(BinaryNode* &t, Booking b)
{
	if (t == NULL)
	{
		BinaryNode *newNode = new BinaryNode;
		newNode->item = b;
		newNode->left = NULL;
		newNode->right = NULL;
		t = newNode;
	}
	else 
	{
		time_t checkindate = mktime(&t->item.checkinDate);
		time_t inputdate = mktime(&b.checkinDate);
		double diff = difftime(checkindate, inputdate);

		if (diff < 0)
			insert(t->left, b);  // insert in left subtree
		else
			insert(t->right, b); // insert in right subtree	
	}


	t = balance(t);				// balance the tree (AVL Tree function)
}


//// traverse the binary search tree in inorder
//void BST::inorder()
//{
//	if (isEmpty())
//		cout << "No item found" << endl;
//	else
//		inorder(root);
//}
//
//void BST::inorder(BinaryNode* t)
//{
//	if (t != NULL)
//	{
//		inorder(t->left);
//		cout << t->item << endl;
//		inorder(t->right);
//	}
//}
//// traverse the binary search tree in preorder
//void BST::preorder()
//{
//	if (isEmpty())
//		cout << "No item found" << endl;
//	else
//		preorder(root);
//}
//
//void BST::preorder(BinaryNode* t)
//{
//	if (t != NULL)
//	{
//		cout << t->item << endl;
//		preorder(t->left);
//		preorder(t->right);
//	}
//}
//
//// traverse the binary search tree in postorder
//void BST::postorder()
//{
//	if (isEmpty())
//		cout << "No item found" << endl;
//	else
//		postorder(root);
//}
//
//void BST::postorder(BinaryNode* t)
//{
//	if (t != NULL)
//	{
//		postorder(t->left);
//		postorder(t->right);
//		cout << t->item << endl;
//	}
//}

// check if the binary search tree is empty
bool BST::isEmpty()
{
	return (root == NULL);
}

// count the number of nodes in the binary search tree
int BST::countNodes()
{
	return countNodes(root);
}

int BST::countNodes(BinaryNode* t)
{
	if (t == NULL)
		return 0;
	else
		return 1 + countNodes(t->left) + countNodes(t->right);
}

// compute the height of the binary search tree
int BST::getHeight()
{
	return getHeight(root);
}

int BST::getHeight(BinaryNode* t)
{
	if (t == NULL)
		return 0;
	else
	{
		// return 1 + max(getHeight(t->left), getHeight(t->right));
		int leftHeight = getHeight(t->left);
		int rightHeight = getHeight(t->right);
		return 1 + max(leftHeight, rightHeight);
	}
}

// check if the binary search tree is balanced
bool BST::isBalanced()
{
	return isBalanced(root);
}

bool BST::isBalanced(BinaryNode *t)
{
	if (t == NULL)
		return true;
	else
	{
		int leftHeight = getHeight(t->left);	// height of left sub-tree
		int rightHeight = getHeight(t->right);	// height of right sub-tree
		bool isBalancedNode = (abs(leftHeight - rightHeight) <= 1);
		bool isBalancedLeft = isBalanced(t->left);
		bool isBalancedRight = isBalanced(t->right);
		return (isBalancedNode && isBalancedLeft && isBalancedRight);
	}
}

// delete an item from the binary search tree
void BST::remove(tm date, string guestName, string roomType)
{
	remove(root, date, guestName, roomType);
	balanceTree(root);			// AVL Tree function
}

void BST::remove(BinaryNode* &t, tm date, string guestName, string roomType)
{
	if (t != NULL)
	{
		time_t checkindate = mktime(&t->item.checkinDate);
		time_t inputdate = mktime(&date);
		double diff = difftime(checkindate, inputdate);
		if (diff < 0)			// search in left subtree
			remove(t->left, date, guestName, roomType);
		else if (diff > 0)	// search in right subtree
			remove(t->right, date, guestName, roomType);
		else						// item == t->item (found) - base case
		{
			if (t->left == NULL && t->right == NULL) // case 1 : node has 0 child
			{
				BinaryNode* temp = t;	// to be deleted
				t = NULL;
				delete temp;			// delete the node
			}
			else if (t->left == NULL)	// case 2 : node has 1 child
			{
				BinaryNode* temp = t;	// node to be deleted

				if (t == root)			// current node is root
					root = t->right;
				else
					t = t->right;

				delete temp;			// delete the node
			}
			else if (t->right == NULL)	// case 2 : node has 1 child
			{
				BinaryNode* temp = t;	// node to be deleted

				if (t == root)			// current node is root
					root = t->left;
				else
					t = t->left;

				delete temp;			// delete the node
			}
			else // case 3 : node has 2 children
			{
				BinaryNode* successor = t->left;
				while (successor->right != NULL)	// search for right most node in left sub-tree
					successor = successor->right;

				ItemType item = successor->item;	
				remove(t->left, item.checkinDate, item.bookingGuestName, item.bookingRoomType);  // delete the successor (either case 1 or case 2)
				t->item = item;					// replace the node’s item with that of the successor
			}
		}
	}
}

// change status from booked to checked in
bool BST::checkIn(tm date, string guestName, string roomType)
{
	BinaryNode* b = search(date, guestName, roomType);
	b->item.bookingStatus = "Checked In";
	// need to assign room to the guest who just checked in also need to check if the room is avail.
	return true;
}
