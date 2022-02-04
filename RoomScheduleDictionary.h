#pragma once

#include "BST.h"
#include "RoomScheduleLinkedList.h"
#include<iostream>
#include "Booking.h"
#include <string.h>
using namespace std;
#include<map>

const int MAX_SIZE = 181;
typedef tm KeyType;
static int firstHashRoom = 18686;

class RoomScheduleDictionary
{
private:
	//struct Node
	//{
	//	string guestName;	// data item
	//	string roomNumber;
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

	RoomScheduleDictionary();
	// destructor
	~RoomScheduleDictionary();

	//hash date based off unix time
	int hash(KeyType key);

	// add a new item with the specified key to the RoomScheduleDictionary
	// pre : none
	// post: new item is added to the RoomScheduleDictionary
	//       size of RoomScheduleDictionary is increased by 1
	// 
	// add entry for every date from checkin to checkout exclusive, check if null, add info to list
	bool add(tm checkInDate, tm checkOutDate, string guestName, string roomNumber);

	// remove an item with the specified key in the RoomScheduleDictionary
	// pre : key must exist in the RoomScheduleDictionary
	// post: item is removed from the RoomScheduleDictionary
	//       size of RoomScheduleDictionary is decreased by 1
	//
	//hash, check if null, remove info to list
	void remove(KeyType newKey, string guestName, string roomNumber);


	// get an item with the specified key in the RoomScheduleDictionary (retrieve)
	// pre : key must exist in the RoomScheduleDictionary
	// post: none
	// return the item with the specified key from the RoomScheduleDictionary
	//
	//hash, check if null, get MaxValue - list.size
	int getAvailableRoomNumber(KeyType key);

	//hash, get list of stayees and the room they are in
	RoomScheduleLinkedList getRoomDateInfo(KeyType key);

	//print guests which are staying on that date
	void printDateGuests(tm key);
	// check if the RoomScheduleDictionary is empty
	// pre : none
	// post: none
	// return true if the RoomScheduleDictionary is empty; otherwise returns false
	/*bool isEmpty();*/

	//return map of room no. and occupied dates
	void getOccupiedDatesFromMonth(map<string, string> &roomOccupiedDates, tm month);

};
