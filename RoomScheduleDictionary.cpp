// Group 12
// Chua Dong En, S10202623A
#include "RoomScheduleDictionary.h"
#include <string>
#include<map>

// Group 12
// Chua Dong En, S10202623A
// constructor
RoomScheduleDictionary::RoomScheduleDictionary(int maxRoom, string roomType) {
	MaxRoom = maxRoom;
	roomTypeName = roomType;
	for (int i = 0; i < MAX_SIZE;i++)
	{
		items[i] = NULL;
	}
};

// Group 12
// Chua Dong En, S10202623A
//default constructor
RoomScheduleDictionary::RoomScheduleDictionary() {
	for (int i = 0; i < MAX_SIZE; i++)
	{
		items[i] = NULL;
	}
};

// Group 12
// Chua Dong En, S10202623A
//destructor
RoomScheduleDictionary::~RoomScheduleDictionary(){
	for (int i = 0; i < MAX_SIZE; i++)
	{
		if (items[i] != NULL)
		{
			RoomScheduleLinkedList*  temp = items[i];
			while (temp != NULL)
			{
				delete temp;
				items[i] = NULL;
			}
		}
};

// Group 12
// Chua Dong En, S10202623A
//hash date for index
int RoomScheduleDictionary::hash(KeyType key){
	//if date is not formatted yet ,format
	if (!(key.tm_year < 1000)) {
		key.tm_year -= 1900;
		key.tm_mon -= 1;
		key.tm_min = 0;
		key.tm_sec = 0;
		key.tm_hour = 0;
	}
	//convert to unix days
	time_t time = mktime(&key) / 86400;
	//set first hash (used to make it dynamic but in this case its hard coded)
	if (firstHashRoom == NULL) {
		firstHashRoom = (int) time;
	}
	//return index
	return time-firstHashRoom;
};

// Group 12
// Chua Dong En, S10202623A
//add new room schedules within date range
bool RoomScheduleDictionary::add(tm checkInDate, tm checkOutDate, string guestName, string roomNumber,int bid){
	//if date is not formatted yet ,format
	if (!(checkInDate.tm_year < 1000)) {
		checkInDate.tm_year -= 1900;
		checkInDate.tm_mon -= 1;
		checkInDate.tm_min = 0;
		checkInDate.tm_sec = 0;
		checkInDate.tm_hour = 0;
	}
	//if date is not formatted yet ,format
	if (!(checkOutDate.tm_year < 1000)) {
		checkOutDate.tm_year -= 1900;
		checkOutDate.tm_mon -= 1;
		checkOutDate.tm_min = 0;
		checkOutDate.tm_sec = 0;
		checkOutDate.tm_hour = 0;
	}
	//convert to unix time
	time_t checkInTime = mktime(&checkInDate);
	time_t checkOutTime = mktime(&checkOutDate);
	//change checkInDate back to original date to be hashed later
	checkInDate.tm_year += 1900;
	checkInDate.tm_mon += 1;
	tm currentDate = checkInDate;
	//add for all dates from checkInDate to checkOutDate
	while (checkInTime < checkOutTime) {
		//hash date for index
		int index = hash(currentDate);
		//if no linkedlist available, intialize and add
		if (items[index] == NULL) {
			items[index] = new RoomScheduleLinkedList();
			items[index]->add(guestName, roomNumber, currentDate,bid);
		}
		//else add to exisitng 
		else {
			items[index]->add(guestName, roomNumber, currentDate,bid);
		}
		//increment current date and checkInTime to move to next iteration in loop
		currentDate.tm_mday += 1;
		checkInTime += 86400;
	}
	//no data validation hahaha
	return true;
};

// Group 12
// Chua Dong En, S10202623A
//remove room schedules from dict within a date range
void RoomScheduleDictionary::remove(tm checkInDate, tm checkOutDate, string guestName, string roomNumber){
	//if date is not formatted yet ,format
	if (!(checkInDate.tm_year < 1000)) {
		checkInDate.tm_year -= 1900;
		checkInDate.tm_mon -= 1;
		checkInDate.tm_min = 0;
		checkInDate.tm_sec = 0;
		checkInDate.tm_hour = 0;
	}
	//if date is not formatted yet ,format
	if (!(checkOutDate.tm_year < 1000)) {
		checkOutDate.tm_year -= 1900;
		checkOutDate.tm_mon -= 1;
		checkOutDate.tm_min = 0;
		checkOutDate.tm_sec = 0;
		checkOutDate.tm_hour = 0;
	}
	//convert to unix time
	time_t checkInTime = mktime(&checkInDate);
	time_t checkOutTime = mktime(&checkOutDate);
	//change checkInDate back to original date to be hashed later
	checkInDate.tm_year += 1900;
	checkInDate.tm_mon += 1;
	tm currentDate = checkInDate;
	//add for all dates from checkInDate to checkOutDate
	while (checkInTime < checkOutTime) {
		//hash for index
		int index = hash(currentDate);
		//if linked list exists, remove room schedule
		if (items[index] != NULL) {
			items[index]->remove(guestName, roomNumber, currentDate);
		}
		//increment current date and checkInTime to move to next iteration in loop
		currentDate.tm_mday += 1;
		checkInTime += 86400;
	}
	return;
};

// Group 12
// Chua Dong En, S10202623A
//get no. of avail rooms within date range
int RoomScheduleDictionary::getAvailableRoomNumber(tm checkInDate, tm checkOutDate) {
	//if date is not formatted yet ,format
	if (!(checkInDate.tm_year < 1000)) {
		checkInDate.tm_year -= 1900;
		checkInDate.tm_mon -= 1;
		checkInDate.tm_min = 0;
		checkInDate.tm_sec = 0;
		checkInDate.tm_hour = 0;
	}
	//if date is not formatted yet ,format
	if (!(checkOutDate.tm_year < 1000)) {
		checkOutDate.tm_year -= 1900;
		checkOutDate.tm_mon -= 1;
		checkOutDate.tm_min = 0;
		checkOutDate.tm_sec = 0;
		checkOutDate.tm_hour = 0;
	}
	//convert to unix time
	time_t checkInTime = mktime(&checkInDate);
	time_t checkOutTime = mktime(&checkOutDate);
	//change checkInDate back to original date to be hashed later
	checkInDate.tm_year += 1900;
	checkInDate.tm_mon += 1;
	tm currentDate = checkInDate;
	//map contains all booking id as key
	map<int, int> occupiedRoomsMap;
	//add for all dates from checkInDate to checkOutDate
	while (checkInTime < checkOutTime) {
		//hash date to index
		int index = hash(currentDate);
		//if not null, get booked rooms from linked list
		if (items[index] != NULL) {
			items[index]->getBookedRooms(occupiedRoomsMap);
		}
		//increment current date and checkInTime to move to next iteration in loop
		currentDate.tm_mday += 1;
		checkInTime += 86400;
	}
	//if occupied, return max - occupied room  no.
	if (occupiedRoomsMap.size() < MaxRoom) {
		return MaxRoom - occupiedRoomsMap.size();
	}
	//else, return maxroom
	return MaxRoom;
};

// Group 12
// Chua Dong En, S10202623A
//print guests which are staying on that date
void RoomScheduleDictionary::printDateGuests(tm key) {
	//hash date for index
	int index = hash(key);
	//if not null
	if (items[index] != NULL) {
		//print guests on that date
		items[index]->printDateGuests();
	}
};

// Group 12
// Chua Dong En, S10202623A
//return map of room no. and occupied dates
void RoomScheduleDictionary::getOccupiedDatesFromMonth(map<string, string> &roomOccupiedDates, tm month) {
	//change to time_t for comparsion and looping
	tm endOfMonth;
	endOfMonth = month;
	//get first date of month
	month.tm_year -= 1900;
	month.tm_mon -= 1;
	month.tm_mday = 1;
	month.tm_min = 0;
	month.tm_sec = 0;
	month.tm_hour = 0;
	//get last date of month by going to next month and minusing 1 day
	endOfMonth.tm_year -= 1900;
	endOfMonth.tm_mday = 0;
	endOfMonth.tm_min = 0;
	endOfMonth.tm_sec = 0;
	endOfMonth.tm_hour = 0;
	time_t startMonthTime = mktime(&month);
	//time_t endMonthTime = mktime(&endOfMonth) - 86400;
	time_t endMonthTime = mktime(&endOfMonth);
	//change checkInDate back to original date to be hashed later
	month.tm_year += 1900;
	month.tm_mon += 1;
	tm currentDate = month;
	//add for all dates from checkInDate to checkOutDate
	while (startMonthTime <= endMonthTime) {
		//hash date for index
		int index = hash(currentDate);
		//if not null, get occupied dates from day and save it to map
		if (items[index] != NULL) {
			items[index]->getOccupiedDatesFromDay(roomOccupiedDates, currentDate);
		}
		//if occupied, return max - occupied room  no.
		currentDate.tm_mday += 1;
		startMonthTime += 86400;
	}
};

// Group 12
// Chua Dong En, S10202623A
//return map of occupied rooms
map<string, int> RoomScheduleDictionary::getOccupiedRooms(tm checkInDate, tm checkOutDate) {
	//if date is not formatted yet ,format
	if (!(checkInDate.tm_year < 1000)) {
		checkInDate.tm_year -= 1900;
		checkInDate.tm_mon -= 1;
		checkInDate.tm_min = 0;
		checkInDate.tm_sec = 0;
		checkInDate.tm_hour = 0;
	}
	//if date is not formatted yet ,format
	if (!(checkOutDate.tm_year < 1000)) {
		checkOutDate.tm_year -= 1900;
		checkOutDate.tm_mon -= 1;
		checkOutDate.tm_min = 0;
		checkOutDate.tm_sec = 0;
		checkOutDate.tm_hour = 0;
	}
	//convert to unix time
	time_t checkInTime = mktime(&checkInDate);
	time_t checkOutTime = mktime(&checkOutDate);
	//change checkInDate back to original date to be hashed later
	checkInDate.tm_year += 1900;
	checkInDate.tm_mon += 1;
	tm currentDate = checkInDate;
	map<string, int> occupiedRoomsMap;
	//add for all dates from checkInDate to checkOutDate
	while (checkInTime < checkOutTime) {
		//hash date for index
		int index = hash(currentDate);
		//if not null, get occupied rooms and save it to map
		if (items[index] != NULL) {
			items[index]->getOccupiedRooms(occupiedRoomsMap);
		}
		//increment current date and checkInTime to move to next iteration in loop
		currentDate.tm_mday += 1;
		checkInTime += 86400;
	}
	return occupiedRoomsMap;
};