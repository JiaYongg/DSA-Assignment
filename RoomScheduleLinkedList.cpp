#include "RoomScheduleLinkedList.h"
// constructor
RoomScheduleLinkedList::RoomScheduleLinkedList() {
	firstNode = NULL;
	size = 0;
};

// destructor
//RoomScheduleLinkedList::~RoomScheduleLinkedList() {};

// add an item to the back of the RoomScheduleLinkedList (append)
bool RoomScheduleLinkedList::add(ItemType item) {
	Node* newNode = new Node;
	newNode->item = item;
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

// add an item at a specified position in the RoomScheduleLinkedList (insert)
bool RoomScheduleLinkedList::add(int index, ItemType item) {
	if (index <= size &&index>=0) {
		Node* newNode = new Node;
		newNode->item = item;
		newNode->next = NULL;


		if (index == 0) {
			newNode->next = firstNode;
			firstNode = newNode;
		}
		else {
			Node* current = firstNode;
			for (int i = 0;i < index - 1;i++) {
				current = current->next;
			}
			newNode->next = current->next;
			current->next = newNode;
		}
		size++;
		return true;
	}
	else {
		return false;
	}
};

// remove an item at a specified position in the RoomScheduleLinkedList
void RoomScheduleLinkedList::remove(int index) {
	if (index <= size && index >= 0) {
		

		if (index == 0) {
			if (size == 1) {
				firstNode = NULL;
			}
			else {
				//Node* temp = firstNode;
				//temp = firstNode;
				firstNode = firstNode->next;
				//delete[] temp;
			}
		}
		else {
			Node* current = firstNode;
			for (int i = 0;i < index - 1;i++) {
				current = current->next;
			}
			//Node* temp = current->next;
			current->next = current->next->next;
			//delete[] temp;
		}
		size--;
	}
};

// get an item at a specified position of the RoomScheduleLinkedList (retrieve)
ItemType RoomScheduleLinkedList::get(int index) {
	if (index <= size && index >= 0) {
		Node* current = firstNode;
		for (int i = 0;i < index ;i++) {
			current = current->next;
		}
		return current->item;
	}
};

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
		std::cout << current->item << endl;
		current = current->next;
	}
};
