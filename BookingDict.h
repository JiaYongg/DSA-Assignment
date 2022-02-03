#pragma once

#include "BST.h"
#include "Booking.h"
#include "RoomScheduleDictionary.h"
#include<iostream>
using namespace std;

typedef tm KeyType;
static int firstHash = 18686;



class BookingDict
{
private:
	struct BinaryNode
	{
		Booking item;
		BinaryNode* left;	// pointer pointing to left subtree
		BinaryNode* right;	// pointer pointing to right subtree
	};
	BST *items[MAX_SIZE];
	int  size;			// number of items in the Dictionary

public:

	// constructor
	//set to null
	BookingDict();

	// destructor
	~BookingDict();

	//hash unix time from checkInDate
	int hash(KeyType key);

	// get an item with the specified key in the Dictionary (retrieve)
	// pre : key must exist in the dictionary
	// post: none
	// return the item with the specified key from the Dictionary
	//
	// change status from booked to checked in
	bool checkIn(KeyType key, string guestName, string roomType);

	// add a new item with the specified key to the Dictionary
	// pre : none
	// post: new item is added to the Dictionary
	//       size of Dictionary is increased by 1
	//
	// hash, add to tree
	bool add(Booking b);

	// remove an item with the specified key in the Dictionary
	// pre : key must exist in the Dictionary
	// post: item is removed from the Dictionary
	//       size of Dictionary is decreased by 1
	//
	// hash, remove from tree, remove from room date dict
	void remove(KeyType key, string guestName, string roomType, RoomScheduleDictionary rsd);


	// get an item with the specified key in the Dictionary (retrieve)
	// pre : key must exist in the dictionary
	// post: none
	// return the item with the specified key from the Dictionary
	//
	//hash, return booking
	Booking get(KeyType key, string guestName, string roomType);


	//hash, check yesterday overdue
	void checkYtdOverdue(tm currentDate);

	// check if the Dictionary is empty
	// pre : none
	// post: none
	// return true if the Dictionary is empty; otherwise returns false
	bool isEmpty();

	// check the size of the Dictionary
	// pre : none
	// post: none
	// return the number of items in the Dictionary
	int getLength();
	

	//loop through all booking, add to linkedlist, print most popular
	void printPopular();
	//------------------- Other useful functions -----------------

	//// display the items in the Dictionary
	//void print();


	//loop through all booking in that range, print
	void printRange(tm start, tm end);

};
