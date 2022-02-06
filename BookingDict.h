// Group 12
// Chua Dong En, S10202623A
// Poh Jia Yong, S10202579J
#pragma once
#include "BST.h"
#include "Booking.h"
#include "RoomScheduleDictionary.h"
#include<iostream>
#include "BinaryNode.h"
#include "Room.h"

using namespace std;

typedef tm KeyType;
static int firstHash = 18686;



class BookingDict
{
private:
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

	// change status from booked to checked in
	bool checkIn(KeyType key, string guestName, string roomType, map<string, RoomScheduleDictionary> &roomScheduleDictMap, Room roomArray[20]);


	// hash, add to tree
	bool add(Booking b, map<string, RoomScheduleDictionary> &roomScheduleDictMap);

	// hash, remove from tree, remove from room date dict
	void remove(KeyType key, string guestName, string roomType, map<string,RoomScheduleDictionary> &roomScheduleDictMap);

	//hash, return booking
	Booking get(KeyType key, string guestName, string roomType);

	//loop through all booking, add to linkedlist, print most popular
	void printPopular(map<string, int> &roomTypeMap);

	//loop through all booking in that range, print
	void printRange(tm start, tm end);

	// check yesterday overdue
	void checkOverdue(tm currentDate, map<string, RoomScheduleDictionary>& roomScheduleDictMap);
};
