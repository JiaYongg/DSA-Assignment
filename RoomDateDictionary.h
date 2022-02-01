#pragma once

#include "BST.h"
#include "List.h"
#include<iostream>
using namespace std;

const int MAX_SIZE = 181;
typedef string KeyType;


class RoomDateDictionary
{
private:
	//max number of available rooms
	int MaxRoom;
	//[3,[roomInfo,roomInfo,roomInfo]]
	List items[MAX_SIZE];

public:

	// constructor
	// set maxroom, items array to occupiedNumber to null
	RoomDateDictionary(int maxRoom);

	// destructor
	~RoomDateDictionary();

	//hash date based off unix time
	int hash(KeyType key);

	// add a new item with the specified key to the RoomDateDictionary
	// pre : none
	// post: new item is added to the RoomDateDictionary
	//       size of RoomDateDictionary is increased by 1
	// 
	// hash, check if null, add info to list
	bool add(KeyType newKey);

	// remove an item with the specified key in the RoomDateDictionary
	// pre : key must exist in the RoomDateDictionary
	// post: item is removed from the RoomDateDictionary
	//       size of RoomDateDictionary is decreased by 1
	//
	//hash, check if null, remove info to list
	void remove(KeyType key);


	// get an item with the specified key in the RoomDateDictionary (retrieve)
	// pre : key must exist in the RoomDateDictionary
	// post: none
	// return the item with the specified key from the RoomDateDictionary
	//
	//hash, check if null, get MaxValue - list.size
	ItemType getAvailableRoomNumber(KeyType key);

	//hash, get list of stayees and the room they are in
	List getRoomDateInfo(KeyType key);


	// check if the RoomDateDictionary is empty
	// pre : none
	// post: none
	// return true if the RoomDateDictionary is empty; otherwise returns false
	bool isEmpty();

};
