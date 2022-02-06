// Group 12
// Chua Dong En, S10202623A
#pragma once
#include "BST.h"
#include "RoomScheduleLinkedList.h"
#include<iostream>
#include "Booking.h"
#include <string.h>
#include <vector>
using namespace std;
#include<map>

//6 months worth of days
const int MAX_SIZE = 181;
typedef tm KeyType;
//first hash is unix day of 01/03/2021 relative to 1900 Jan 1
static int firstHashRoom = 18686;

class RoomScheduleDictionary
{
private:


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

	//default constructor
	RoomScheduleDictionary();

	// destructor
	~RoomScheduleDictionary();

	//hash date for index
	int hash(KeyType key);

	//add new room schedules within date range
	bool add(tm checkInDate, tm checkOutDate, string guestName, string roomNumber, int bid);

	//remove room schedules from dict within a date range
	void remove(tm startDate, tm endDate, string guestName, string roomNumber);

	//get no. of avail rooms within date range
	int getAvailableRoomNumber(tm checkInDate, tm checkOutDate);

	//print guests which are staying on that date
	void printDateGuests(tm key);

	//return map of room no. and occupied dates
	void getOccupiedDatesFromMonth(map<string, string> &roomOccupiedDates, tm month);

	//return map of occupied rooms
	map<string, int> getOccupiedRooms(tm checkInDate, tm checkOutDate);
};
