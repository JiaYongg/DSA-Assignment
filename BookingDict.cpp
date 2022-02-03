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

// change status from booked to checked in
bool BookingDict::checkIn(KeyType key, string guestName, string roomType)
{
	int index = hash(key);

	if (items[index] != NULL)
	{
		// handle error if the guy is alr checked in
		items[index]->checkIn(key, guestName, roomType);
	}
	return true;
}

// hash, add to tree
bool BookingDict::add(Booking b)
{
	int index = hash(b.checkinDate);
	cout << index << endl;
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

//hash, remove from tree, remove from room date dict
void BookingDict::remove(KeyType key, string guestName, string roomType, RoomScheduleDictionary rsd)
{
	int index = hash(key);

	if (items[index] != NULL)
	{
		BinaryNode* newBinaryNode = items[index]->search(key, guestName, roomType);
		string roomNum = newBinaryNode->item.bookingRoomNumber;
		rsd.remove(key, guestName, roomNum);
		items[index]->remove(key, guestName, roomType);
	}
};


//hash, return booking
Booking BookingDict::get(KeyType key, string guestName, string roomType)
{
	int index = hash(key);

	if (items[index] != NULL)
	{
		// handle error if the guy is alr checked in
		BinaryNode* newBinaryNode = items[index]->search(key, guestName, roomType);
		return newBinaryNode->item;
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