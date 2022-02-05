// BST.h - Specification of Binary Search Tree
#pragma once
#include<iostream>
#include <map>
using namespace std;

#include "BinaryNode.h"
#include "AVL_Tree.h"		// AVL Tree functions
#include "RoomScheduleDictionary.h"

class BST
{
private:
	BinaryNode* root;		// root of the BST

public:

	// constructor
	BST();

	// search an item in the binary search tree
	BinaryNode* search(tm date, string guestName, string roomType);
	BinaryNode* search(BinaryNode* t, tm date, string guestName, string roomType);

	// insert an item to the binary search tree
	void insert(Booking b);
	void insert(BinaryNode* &root, Booking b);

	// delete an item from the binary search tree
	void remove(tm date, string guestName, string roomType);
	void remove(BinaryNode* &root, tm date, string guestName, string roomType);

	//// traverse the binary search tree in inorder
	void inorder(tm start, tm end);
	void inorder(BinaryNode* t, tm start, tm end);

	// traverse through the bst to check for overdue bookings
	//void inorderoverdue(tm current, RoomScheduleDictionary &rsd);
	//void inorderoverdue(BinaryNode* t, tm current, RoomScheduleDictionary& rsd);

	// traverse through the bst to check for most popular room type
	void inorderpopular(map<string, int> roomTypeMap);
	void inorderpopular(BinaryNode* t, map<string, int> roomTypeMap);

	//// traverse the binary search tree in preorder
	//void preorder();
	//void preorder(BinaryNode* t);

	//// traverse the binary search tree in postorder
	//void postorder();
	//void postorder(BinaryNode* t);

	// check if the binary search tree is empty
	bool isEmpty();

	// count the number of nodes in the binary search tree
	//int countNodes();
	//int countNodes(BinaryNode* t);

	//// compute the height of the binary search tree
	//int getHeight();
	//int getHeight(BinaryNode* t);

	//// check if the binary search tree is balanced
	//bool isBalanced();
	//bool isBalanced(BinaryNode *t);

	// change status from booked to checked in
	bool checkIn(tm key, string guestName, string roomType);

	//loop through all booking, add to linkedlist, print most popular
	void printPopular(map<string, int> roomTypeMap);

	// print all bookings in range
	void printRange(tm start, tm end);

	//void checkOverDue(tm current, RoomScheduleDictionary &rsd);
};

