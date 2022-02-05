#include  "RoomScheduleLinkedList.h"
#include <iostream>
#include<map>
using namespace std;
// constructor
RoomScheduleLinkedList::RoomScheduleLinkedList() {
	firstNode = NULL;
	roomScheduleLinkedListSize = 0;
};

// destructor
RoomScheduleLinkedList::~RoomScheduleLinkedList() {};

// add an item to the back of the RoomScheduleLinkedList (append)
bool RoomScheduleLinkedList::add(string guestName, string roomNumber, tm date) {
	Node* newNode = new Node;
	newNode->date=date ;
	newNode->guestName = guestName;
	newNode->roomNumber = roomNumber;
	newNode->next = NULL;

	if (roomScheduleLinkedListSize == 0) {
		firstNode = newNode;
	}
	else {
		Node* current = firstNode;
		while (current->next != NULL) {
			current = current->next;
		}
		current->next = newNode;
	}
	roomScheduleLinkedListSize++;
	return true;
};

// remove an item at a specified position in the RoomScheduleLinkedList
void RoomScheduleLinkedList::remove(string guestName, string roomNumber, tm date) {
	Node* current = firstNode;
	while (current != NULL) {
		time_t currentDate = mktime(&current->date);
		time_t compareDate = mktime(&date);
		//cout << date.tm_mday << "\t" << difftime(currentDate, compareDate) << roomScheduleLinkedListSize <<endl;
		if (current->guestName == guestName && current->roomNumber == roomNumber && difftime(currentDate,compareDate)==0) {
			if (roomScheduleLinkedListSize==1) {
				firstNode = NULL;
			}
			else if (roomScheduleLinkedListSize == 2){
				firstNode = current->next;
			}
			else {
				current->next = current->next->next;
			}
			roomScheduleLinkedListSize--;
			//cout << date.tm_mday << "\t" << difftime(currentDate, compareDate) << roomScheduleLinkedListSize<< endl;
			return;
		}
		current = current->next;
	}
	//current = firstNode;
	//while (current != NULL) {
	//	cout << current->guestName << endl;
	//	current = current->next;
	//}
	return;
};

//// get an item at a specified position of the RoomScheduleLinkedList (retrieve)
//string RoomScheduleLinkedList::get(int index) {
//	if (index <= roomScheduleLinkedListSize && index >= 0) {
//		Node* current = firstNode;
//		for (int i = 0;i < index ;i++) {
//			current = current->next;
//		}
//		return current->item;
//	}
//};

// check if the RoomScheduleLinkedList is empty
bool RoomScheduleLinkedList::isEmpty() {
	if (roomScheduleLinkedListSize == 0) {
		return true;
	}
	return false;
};

// check the roomScheduleLinkedListSize of the RoomScheduleLinkedList
int RoomScheduleLinkedList::getLength() {
	return roomScheduleLinkedListSize;
};

// display all the items in the RoomScheduleLinkedList
void RoomScheduleLinkedList::print() {
	Node* current = firstNode;
	while (current != NULL) {
		std::cout << current->roomNumber << endl;
		current = current->next;
	}
};

//print guests which are staying on that date
void RoomScheduleLinkedList::printDateGuests() {
	Node* current = firstNode;
	while (current != NULL) {
		cout << current->guestName << endl;
		current = current->next;
	}
};

//return map with dates that each room is filled
void  RoomScheduleLinkedList::getOccupiedDatesFromDay(map<string, string> &roomOccupiedDates, tm date) {

	Node* current = firstNode;
	while (current != NULL) {
		if (current->roomNumber != " ") {
			if (current->roomNumber != "") {
				string dates = roomOccupiedDates[current->roomNumber];
				if (current->date.tm_mday != 31) {
					dates += std::to_string(current->date.tm_mday % 31) + ", ";
				}
				else {
					dates += std::to_string(31) + ", ";
				}

				roomOccupiedDates[current->roomNumber] = dates;
			}
		}
		current = current->next;
	}
};