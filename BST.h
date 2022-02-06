// Group 12
// Poh Jia Yong, S10202579J
#pragma once
#include<iostream>
#include <string>
#include <map>
#include "BinaryNode.h"
#include "RoomScheduleDictionary.h"
#include "AVL_Tree.h"		// AVL Tree functions
#include <string.h>
#include "Room.h"
using namespace std;

class RoomScheduleDictionary;

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
	void insert(Booking b, map<string, RoomScheduleDictionary> &roomScheduleDictMap);
	void insert(BinaryNode* &root, Booking b);

	// delete an item from the binary search tree
	void remove(tm date, string guestName, string roomType);
	void remove(BinaryNode* &root, tm date, string guestName, string roomType);

	//// traverse the binary search tree in inorder
	void inorder(tm start, tm end);
	void inorder(BinaryNode* t, tm start, tm end);

	// traverse through the bst to check for overdue bookings
	void inorderoverdue(tm current, map<string, RoomScheduleDictionary>& roomScheduleDictMap);
	void inorderoverdue(BinaryNode* t, tm current, map<string, RoomScheduleDictionary>& roomScheduleDictMap);

	// traverse through the bst to check for most popular room type
	void inorderpopular(map<string, int> &roomTypeMap);
	void inorderpopular(BinaryNode* t, map<string, int> &roomTypeMap);

	// check if the binary search tree is empty
	bool isEmpty();

	// change status from booked to checked in
	bool checkIn(tm key, string guestName, string roomType, map<string, RoomScheduleDictionary> &roomScheduleDictMap, Room roomArray[20]);

	//loop through all booking, add to linkedlist, print most popular
	void printPopular(map<string, int> &roomTypeMap);

	// print all bookings in range
	void printRange(tm start, tm end);

	// check if booking is overdue, if overdue, change booking status to "Overdue"
	void checkOverDue(tm current, map<string, RoomScheduleDictionary>& roomScheduleDictMap);
};

