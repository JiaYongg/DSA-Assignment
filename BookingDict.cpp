#pragma once
#include "BookingDict.h"
#include <string>
// constructor
BookingDict::BookingDict() 
{
	for (int i = 0; i < MAX_SIZE; i++)
	{
		items[i] = NULL;
	}
	size = NULL;
};



// destructor is to remove dynamic memory
// static memory is destroyed when program ends. But not dynamic memory
// auto called by program, programmer does not call this destructor
BookingDict::~BookingDict()
{

};

//hash unix time from checkInDate
int BookingDict::hash(KeyType key)
{

	key.tm_year -= 1900;
	key.tm_mon -= 1;
	key.tm_min = 0;
	key.tm_sec = 0;
	key.tm_hour = 0;
	//printf("tm_hour:  %d\n", key.tm_hour);
	//printf("tm_min:  %d\n", key.tm_min);
	//printf("tm_sec:  %d\n", key.tm_sec);
	//printf("tm_mday:  %d\n", key.tm_mday);
	//printf("tm_mon:  %d\n", key.tm_mon);
	//printf("tm_year:  %d\n", key.tm_year);
	time_t time = mktime(&key) / 86400;
	if (firstHash == NULL)
		firstHash = (int) time;
	return time - firstHash;
};

// called from main method and hash the checkInDate provided
// once hashed, check if that specific index on the hash table is NULL
// if not NULL, call the checkIn method from the BST
bool BookingDict::checkIn(KeyType key, string guestName, string roomType)
{
	int index = hash(key);

	if (items[index] != NULL)
	{
		items[index]->checkIn(key, guestName, roomType);
	}
	return true;
}

// called from main method and hash the checkInDate provided
// once hashed, check if that specific index on the hash table is NULL
// if NULL, add the Booking to the tree as the first node
// else add the booking to the tree
//hash, add to tree
bool BookingDict::add(Booking b)
{
	int index = hash(b.checkinDate);
	//cout << index << endl;
	if (items[index] == NULL)
	{
		items[index] = new BST(); // instantiate a new BST for the index
		BinaryNode* newBinaryNode = new BinaryNode();
		newBinaryNode->item = b;
		items[index]->insert(b);
	}
	else
		items[index]->insert(b);

	return true;
};

// called from main method and hash the checkInDate provided
// once hashed, check if that specific index on the hash table is NULL
// if not NULL, call the search method from the BST to search for the specific Booking object to delete
// once found, free up the bookingRoomNumber from the Booking by removing from the RoomScheduleDictionary object
// remove the Booking object from the tree after free-ing up the room
// hash, remove from tree, remove from room date dict
void BookingDict::remove(KeyType key, string guestName, string roomType, RoomScheduleDictionary rsd)
{
	int index = hash(key);

	if (items[index] != NULL)
	{
		Booking b = items[index]->search(key, guestName, roomType)->item;
		string roomNum = b.bookingRoomNumber;
		rsd.remove(key, guestName, roomNum);
		items[index]->remove(key, guestName, roomType);
	}
};

// called from main method and hash the checkInDate provided
// once hashed, check if that specific index on the hash table is NULL
// if not NULL, search for the booking in the BST and return the Booking object
// hash, return booking
Booking BookingDict::get(KeyType key, string guestName, string roomType)
{
	int index = hash(key);

	if (items[index] != NULL)
	{
		// remove booking > get that removed booking = error - need to handle/fix
		Booking b = items[index]->search(key, guestName, roomType)->item;
		return b;
	}
}

//hash, check yesterday overdue
void BookingDict::checkYtdOverdue(tm currentDate)
{

}

// check if the Dictionary is empty
// pre : none
// post: none
// return true if the Dictionary is empty; otherwise returns false
bool BookingDict::isEmpty()
{
	return size == 0;
};

// check the size of the Dictionary
// pre : none
// post: none
// return the number of items in the Dictionary
int BookingDict::getLength(){
	return size;
};

//------------------- Other useful functions -----------------

//loop through all booking, add to linkedlist, print most popular
void BookingDict::printPopular()
{

}

//loop through all booking in that range, print
void BookingDict::printRange(tm start, tm end)
{

}