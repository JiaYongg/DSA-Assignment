// Group 12
// Poh Jia Yong, S10202579J
#include "AVL_Tree.h"
#define max(x,y) ((x > y)? x : y)

// Group 12
// Poh Jia Yong, S10202579J
// balance a BST in postorder sequence
void balanceTree(BinaryNode* &t)
{
	if (t != NULL)
	{
		balanceTree(t->left);
		balanceTree(t->right);
		t = balance(t);			// AVL Tree function
	}
}

// --------------------------- AVL Tree functions ----------------------------------


// Group 12
// Poh Jia Yong, S10202579J
// balance a node
BinaryNode* balance(BinaryNode* t)
{
	int bal_factor = diff(t);

	if (bal_factor > 1) 			// tree is left heavy
	{
		// cout << "Tree is left heavy -> do balancing" << endl;
		if (diff(t->left) >= 0)		// left sub-tree is NOT right heavy
			t = rotateRight(t);
		else
			t = rotateLeftRight(t);
	}
	else if (bal_factor < -1) 		// tree is right heavy
	{
		// cout << "Tree is right heavy -> do balancing" << endl;
		if (diff(t->right) <= 0) 	// right sub-tree is NOT left heavy
			t = rotateLeft(t);
		else
			t = rotateRightLeft(t);
	}

	return t;
}

// Group 12
// Poh Jia Yong, S10202579J
// left_rotation 
BinaryNode* rotateLeft(BinaryNode* node)	// left rotation 
{
	// cout << "Rotate left" << endl;
	BinaryNode *temp = node->right;
	node->right = temp->left;
	temp->left = node;
	return temp;
}

// Group 12
// Poh Jia Yong, S10202579J
// right_rotation 
BinaryNode* rotateRight(BinaryNode* node)	// right rotation
{
	// cout << "Rotate right" << endl;
	BinaryNode *temp = node->left;
	node->left = temp->right;
	temp->right = node;
	return temp;
}

// Group 12
// Poh Jia Yong, S10202579J
// left_right_rotation 
BinaryNode* rotateLeftRight(BinaryNode* node)  // left-right rotation
{
	BinaryNode *temp = node->left;
	node->left = rotateLeft(temp);
	return rotateRight(node);
}

// Group 12
// Poh Jia Yong, S10202579J
// right_left_rotation
BinaryNode* rotateRightLeft(BinaryNode* node)  // right-left rotation
{
	BinaryNode *temp = node->right;
	node->right = rotateRight(temp);
	return rotateLeft(node);
}

// Group 12
// Poh Jia Yong, S10202579J
// check the difference in number of nodes in left and right subtrees
// left heavy  : diff > +1
// right heavy : diff < -1
int diff(BinaryNode* t)
{
	int l_height = getHeight(t->left);
	int r_height = getHeight(t->right);
	int b_factor = l_height - r_height;
	return b_factor;
}

// Group 12
// Poh Jia Yong, S10202579J
int getHeight(BinaryNode* t)
{
	if (t == NULL)
		return 0;
	else
	{
		int leftHeight = getHeight(t->left);
		int rightHeight = getHeight(t->right);
		return 1 + max(leftHeight, rightHeight);
	}
}






