#include "RoomScheduleLinkedList.h"
// constructor
RoomScheduleLinkedList::RoomScheduleLinkedList() {
	firstNode = NULL;
	size = 0;
};

// destructor
//RoomScheduleLinkedList::~RoomScheduleLinkedList() {};

// add an item to the back of the RoomScheduleLinkedList (append)
bool RoomScheduleLinkedList::add(string guestName, string roomNumber, tm date) {
	Node* newNode = new Node;
	newNode->date=date ;
	newNode->guestName = guestName;
	newNode->next = NULL;

	if (size == 0) {
		firstNode = newNode;
	}
	else {
		Node* current = firstNode;
		while (current->next != NULL) {
			current = current->next;
		}
		current->next = newNode;
	}
	size++;
	return true;
};

// remove an item at a specified position in the RoomScheduleLinkedList
void RoomScheduleLinkedList::remove(string guestName, string roomNumber, tm date) {
	Node* current = firstNode;
	while (current != NULL) {
		if (current->guestName == guestName && current->roomNumber == roomNumber && current->date == date) {
			if (size==1) {
				current = NULL;
			}
			else if (size == 2){
				current = current->next;
			}
			else {
				current->next = current->next->next;
			}
			size--;
			return;
		}
		current = current->next;
	}
	return;
};

//// get an item at a specified position of the RoomScheduleLinkedList (retrieve)
//string RoomScheduleLinkedList::get(int index) {
//	if (index <= size && index >= 0) {
//		Node* current = firstNode;
//		for (int i = 0;i < index ;i++) {
//			current = current->next;
//		}
//		return current->item;
//	}
//};

// check if the RoomScheduleLinkedList is empty
bool RoomScheduleLinkedList::isEmpty() {
	if (size == 0) {
		return true;
	}
	return false;
};

// check the size of the RoomScheduleLinkedList
int RoomScheduleLinkedList::getLength() {
	return size;
};

// display all the items in the RoomScheduleLinkedList
void RoomScheduleLinkedList::print() {
	Node* current = firstNode;
	while (current != NULL) {
		std::cout << current->roomNumber << endl;
		current = current->next;
	}
};
