#pragma once

#include "BST.h"
#include "List.h"
#include<iostream>
using namespace std;

const int MAX_SIZE = 181;
typedef string KeyType;


class RoomScheduleDictionary
{
private:
	//max number of available rooms
	int MaxRoom;
	//[3,[roomInfo,roomInfo,roomInfo]]
	List items[MAX_SIZE];

public:

	// constructor
	// set maxroom, items array to occupiedNumber to null
	RoomScheduleDictionary(int maxRoom);

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
	bool add(KeyType newKey);

	// remove an item with the specified key in the RoomScheduleDictionary
	// pre : key must exist in the RoomScheduleDictionary
	// post: item is removed from the RoomScheduleDictionary
	//       size of RoomScheduleDictionary is decreased by 1
	//
	//hash, check if null, remove info to list
	void remove(KeyType key);


	// get an item with the specified key in the RoomScheduleDictionary (retrieve)
	// pre : key must exist in the RoomScheduleDictionary
	// post: none
	// return the item with the specified key from the RoomScheduleDictionary
	//
	//hash, check if null, get MaxValue - list.size
	ItemType getAvailableRoomNumber(KeyType key);

	//hash, get list of stayees and the room they are in
	List getRoomDateInfo(KeyType key);


	// check if the RoomScheduleDictionary is empty
	// pre : none
	// post: none
	// return true if the RoomScheduleDictionary is empty; otherwise returns false
	bool isEmpty();

};
