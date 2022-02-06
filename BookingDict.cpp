// Group 12
// Poh Jia Yong, S10202579J
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

// hash unix time from checkInDate, returns an integer that can be used as the index of the array
int BookingDict::hash(KeyType key)
{
	if (!(key.tm_year < 1000)) {
		key.tm_year -= 1900;
		key.tm_mon -= 1;
		key.tm_min = 0;
		key.tm_sec = 0;
		key.tm_hour = 0;
	}
	time_t time = mktime(&key) / 86400;
	if (firstHash == NULL)
		firstHash = (int) time;
	return time - firstHash;
};

// called from main method and hash the checkInDate provided
// once hashed, check if that specific index on the hash table is NULL
// if not NULL, call the checkIn method from the BST
bool BookingDict::checkIn(KeyType key, string guestName, string roomType, map<string, RoomScheduleDictionary> &roomScheduleDictMap, Room roomArray[20])
{
	int index = hash(key);

	if (items[index] != NULL)
	{
		return items[index]->checkIn(key, guestName, roomType,  roomScheduleDictMap, roomArray);
	}
	return false;
}

// called from main method and hash the checkInDate provided
// once hashed, check if that specific index on the hash table is NULL
// if NULL, add the Booking to the tree as the first node
// else add the booking to the tree
// hash, add to tree
bool BookingDict::add(Booking b, map<string, RoomScheduleDictionary> &roomScheduleDictMap)
{
	int index = hash(b.checkinDate);
	if (!(b.checkinDate.tm_year < 1000)) {
		b.checkinDate.tm_year -= 1900;
		b.checkinDate.tm_mon -= 1;
		b.checkinDate.tm_min = 0;
		b.checkinDate.tm_sec = 0;
		b.checkinDate.tm_hour = 0;
	}
	if (!(b.checkOutDate.tm_year < 1000)) {
		b.checkOutDate.tm_year -= 1900;
		b.checkOutDate.tm_mon -= 1;
		b.checkOutDate.tm_min = 0;
		b.checkOutDate.tm_sec = 0;
		b.checkOutDate.tm_hour = 0;
	}

	if (items[index] == NULL)
	{
		items[index] = new BST(); // instantiate a new BST for the index
		items[index]->insert(b,roomScheduleDictMap);
	}
	else
		items[index]->insert(b,roomScheduleDictMap);

	return true;
};

// called from main method and hash the checkInDate provided
// once hashed, check if that specific index on the hash table is NULL
// if not NULL, call the search method from the BST to search for the specific Booking object to delete
// once found, free up the bookingRoomNumber from the Booking by removing from the RoomScheduleDictionary object
// remove the Booking object from the tree after free-ing up the room
// hash, remove from tree, remove from room date dict
void BookingDict::remove(KeyType key, string guestName, string roomType, map<string, RoomScheduleDictionary> &roomScheduleDictMap)
{
	int index = hash(key);

	if (items[index] != NULL)
	{
		Booking b = items[index]->search(key, guestName, roomType)->item;
		string roomNum = b.bookingRoomNumber;
		roomScheduleDictMap[b.bookingRoomType].remove(b.checkinDate,b.checkOutDate, guestName, roomNum);
		items[index]->remove(key, guestName, roomType);

		BinaryNode* bNode = items[index]->search(key, guestName, roomType);

		if (bNode == NULL)
		{
			cout << "--------------------------------------\n";
			cout << "Booking deleted successfully!\n";
		}
		else
		{
			cout << "--------------------------------------\n";
			cout << "Failed to delete booking.\n";
		}
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
		BinaryNode* b = items[index]->search(key, guestName, roomType);
		if (b == NULL) {
			Booking c;
			//make some values to tell the program its null
			c.bookingGuestName = "Not Found";
			return c;
		}
		return b->item;
	}
	else
	{
		// current index in hash table is null
		Booking c;
		//make some values to tell the program its null
		c.bookingGuestName = "Not Found";
		return c;
	}
}

//loop through all booking, add to linkedlist, print most popular
void BookingDict::printPopular(map<string, int> &roomTypeMap)
{
	for (int i = 0; i < MAX_SIZE; i++)
	{
		if (items[i] != NULL)
		{
			items[i]->printPopular(roomTypeMap);
		}
	}
}

// loop through all booking in that range and prints all the bookings in that range
// check every index of the array, if not empty, loop through the BST and print out the Booking ID and Guest Name.
void BookingDict::printRange(tm start, tm end)
{
	start.tm_year -= 1900;
	start.tm_mon -= 1;
	start.tm_min = 0;
	start.tm_sec = 0;
	start.tm_hour = 0;
	end.tm_year -= 1900;
	end.tm_mon -= 1;
	end.tm_min = 0;
	end.tm_sec = 0;
	end.tm_hour = 0;
	for (int i = 0; i < MAX_SIZE; i++)
	{
		if (items[i] != NULL)
		{
			items[i]->printRange(start, end);
		}
	}
}

void BookingDict::checkOverdue(tm currentDate, map<string, RoomScheduleDictionary>& roomScheduleDictMap)
{
	currentDate.tm_year -= 1900;
	currentDate.tm_mon -= 1;
	currentDate.tm_min = 0;
	currentDate.tm_sec = 0;
	currentDate.tm_hour = 0;

	for (int i = 0; i < MAX_SIZE; i++)
	{
		if (items[i] != NULL)
		{
			items[i]->inorderoverdue(currentDate, roomScheduleDictMap);
		}
	}
}