#pragma once

#include "BST.h"
#include<iostream>
using namespace std;

const int MAX_SIZE = 181;
typedef string KeyType;


class RoomDateDictionary
{
private:

	int MaxRoom;
	int items[MAX_SIZE];
public:

	// constructor
	// set maxroom, items array to all null
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
	//hash, increment value
	bool add(KeyType newKey);

	// remove an item with the specified key in the RoomDateDictionary
	// pre : key must exist in the RoomDateDictionary
	// post: item is removed from the RoomDateDictionary
	//       size of RoomDateDictionary is decreased by 1
	//
	//hash, decrement values
	void remove(KeyType key);


	// get an item with the specified key in the RoomDateDictionary (retrieve)
	// pre : key must exist in the RoomDateDictionary
	// post: none
	// return the item with the specified key from the RoomDateDictionary
	ItemType get(KeyType key);

	// get an item with the specified key in the RoomDateDictionary (retrieve)
	// pre : key must exist in the RoomDateDictionary
	// post: none
	// return the item with the specified key from the RoomDateDictionary
	bool checkIn(KeyType key);

	// check if the RoomDateDictionary is empty
	// pre : none
	// post: none
	// return true if the RoomDateDictionary is empty; otherwise returns false
	bool isEmpty();

	// check the size of the RoomDateDictionary
	// pre : none
	// post: none
	// return the number of items in the RoomDateDictionary
	int getLength();

	//------------------- Other useful functions -----------------

	// display the items in the RoomDateDictionary
	void print();

	void printDate(/*date*/);

	void printMonth(/*month*/);

	void printRange(/*date,date*/);

	void printPopular(/*month*/);
	// void replace(KeyType key, ItemType item);
	// bool contains(KeyType key);
};
