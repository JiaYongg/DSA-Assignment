#pragma once

#include "BST.h"
#include "RoomScheduleLinkedList.h"
#include<iostream>
#include "Booking.h"
#include <string.h>
using namespace std;

const int MAX_SIZE = 181;
int firstHash;
typedef tm KeyType;


class RoomScheduleDictionary
{
private:
	//struct Node
	//{
	//	ItemType guestName;	// data item
	//	ItemType roomNumber;
	//	tm date;
	//	Node* next;
	//};

	//max number of available rooms
	int MaxRoom;
	//[3,[roomInfo,roomInfo,roomInfo]]
	RoomScheduleLinkedList *items[MAX_SIZE];
	//Name of roomtype
	string roomTypeName;

public:

	// constructor
	// set maxroom, items array to occupiedNumber to null
	RoomScheduleDictionary(int maxRoom,string roomType);

	// destructor
	~RoomScheduleDictionary();

	//hash date based off unix time
	int hash(KeyType key);

	// add a new item with the specified key to the RoomScheduleDictionary
	// pre : none
	// post: new item is added to the RoomScheduleDictionary
	//       size of RoomScheduleDictionary is increased by 1
	// 
	// hash, check if null, add info to list
	bool add(KeyType newKey, ItemType guestName, ItemType roomNumber);

	// remove an item with the specified key in the RoomScheduleDictionary
	// pre : key must exist in the RoomScheduleDictionary
	// post: item is removed from the RoomScheduleDictionary
	//       size of RoomScheduleDictionary is decreased by 1
	//
	//hash, check if null, remove info to list
	void remove(KeyType newKey, ItemType guestName, ItemType roomNumber);


	// get an item with the specified key in the RoomScheduleDictionary (retrieve)
	// pre : key must exist in the RoomScheduleDictionary
	// post: none
	// return the item with the specified key from the RoomScheduleDictionary
	//
	//hash, check if null, get MaxValue - list.size
	int getAvailableRoomNumber(KeyType key);

	//hash, get list of stayees and the room they are in
	RoomScheduleLinkedList getRoomDateInfo(KeyType key);


	// check if the RoomScheduleDictionary is empty
	// pre : none
	// post: none
	// return true if the RoomScheduleDictionary is empty; otherwise returns false
	/*bool isEmpty();*/

};
