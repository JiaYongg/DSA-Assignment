// Group 12
// Chua Dong En, S10202623A
#include  "RoomScheduleLinkedList.h"
#include <iostream>
#include<map>
using namespace std;

// Group 12
// Chua Dong En, S10202623A
// constructor
RoomScheduleLinkedList::RoomScheduleLinkedList() {
	firstNode = NULL;
	roomScheduleLinkedListSize = 0;
};

// Group 12
// Chua Dong En, S10202623A
// destructor
RoomScheduleLinkedList::~RoomScheduleLinkedList() {
	Node* current = firstNode;
	Node* next;
	while (current != NULL) {
		next = current->next;
		delete current;
		current = next;
	}
};

// Group 12
// Chua Dong En, S10202623A
// add an item to the back of the RoomScheduleLinkedList (append)
bool RoomScheduleLinkedList::add(string guestName, string roomNumber, tm date,int bid) {
	//initialize new node
	Node* newNode = new Node;
	newNode->date=date ;
	newNode->guestName = guestName;
	newNode->roomNumber = roomNumber;
	newNode->bookingID = bid;
	newNode->next = NULL;

	//if size 0, change firstNode
	if (roomScheduleLinkedListSize == 0) {
		firstNode = newNode;
	}
	//if size >0, add to last node
	else {
		Node* current = firstNode;
		while (current->next != NULL) {
			current = current->next;
		}
		current->next = newNode;
	}
	//increment size
	roomScheduleLinkedListSize++;
	//no data validation hahahaha
	return true;
};

// Group 12
// Chua Dong En, S10202623A
// remove an item at a specified position in the RoomScheduleLinkedList
void RoomScheduleLinkedList::remove(string guestName, string roomNumber, tm date) {
	Node* current = firstNode;
	//if date is not formatted yet ,format
	if (!(date.tm_year < 1000)) {
		date.tm_year -= 1900;
		date.tm_mon -= 1;
		date.tm_min = 0;
		date.tm_sec = 0;
		date.tm_hour = 0;
	}
	//traverse through and remove
	while (current != NULL) {
		//unix time for time comparison
		time_t currentDate = mktime(&current->date);
		time_t compareDate = mktime(&date);
		//check if same, if same remove
		if (current->guestName == guestName && current->roomNumber == roomNumber && difftime(currentDate,compareDate)==0) {
			if (roomScheduleLinkedListSize==1) {
				firstNode = NULL;
			}
			else if (roomScheduleLinkedListSize == 2){
				firstNode = current->next;
			}
			else {
				Node* temp = firstNode;
				while (temp->next->bookingID!=current->bookingID) {
					temp = temp->next;
				}
				temp->next = current->next;
				//removes current from Linked list
			}
			//decrement size
			roomScheduleLinkedListSize--;
			return;
		}
		//traverse
		current = current->next;
	}
	return;
};

// Group 12
// Chua Dong En, S10202623A
// check if the RoomScheduleLinkedList is empty
bool RoomScheduleLinkedList::isEmpty() {
	if (roomScheduleLinkedListSize == 0) {
		return true;
	}
	return false;
};

// Group 12
// Chua Dong En, S10202623A
// check the roomScheduleLinkedListSize of the RoomScheduleLinkedList
int RoomScheduleLinkedList::getLength() {
	return roomScheduleLinkedListSize;
};

// Group 12
// Chua Dong En, S10202623A
// display all the items in the RoomScheduleLinkedList
void RoomScheduleLinkedList::print() {
	Node* current = firstNode;
	while (current != NULL) {
		std::cout << "Occupied by: "<<current->guestName <<" "<< current->roomNumber << endl;
		current = current->next;
	}
};

// Group 12
// Chua Dong En, S10202623A
//print guests which are staying on that date
void RoomScheduleLinkedList::printDateGuests() {
	Node* current = firstNode;
	while (current != NULL) {
		cout << current->guestName << endl;
		current = current->next;
	}
};

// Group 12
// Chua Dong En, S10202623A
//fill map with dates that each room is occupied
void  RoomScheduleLinkedList::getOccupiedDatesFromDay(map<string, string> &roomOccupiedDates, tm date) {

	Node* current = firstNode;
	//traverse
	while (current != NULL) {
		//validation
		if (current->roomNumber != " ") {
			if (current->roomNumber != "") {
				//get existing dates for room no. in map, concat new date
				string dates = roomOccupiedDates[current->roomNumber];
				if (current->date.tm_mday != 31) {
					dates += std::to_string(current->date.tm_mday % 31) + ", ";
				}
				else {
					dates += std::to_string(31) + ", ";
				}
				//set value to map value
				roomOccupiedDates[current->roomNumber] = dates;
			}
		}
		//traversal
		current = current->next;
	}
};

// Group 12
// Chua Dong En, S10202623A
//fill map with occupied room numbers (no date needed)
void RoomScheduleLinkedList::getOccupiedRooms(map<string, int> &occupiedRoomsMap) {
	Node* current = firstNode;
	while (current != NULL) {
		if (current->roomNumber != " ") {
			if (current->roomNumber != "") {
				occupiedRoomsMap[current->roomNumber] = 1;
			}
		}
		current = current->next;
	}
};

// Group 12
// Chua Dong En, S10202623A
//fill map with bookingIDs of occupied rooms
void RoomScheduleLinkedList::getBookedRooms(map<int, int>& occupiedRoomsMap) {
	Node* current = firstNode;
	while (current != NULL) {
		occupiedRoomsMap[current->bookingID] = 1;
		current = current->next;
	}
};