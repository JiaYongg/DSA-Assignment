// RoomScheduleLinkedList.h - - Specification of RoomScheduleLinkedList ADT

#include<string>
#include<iostream>
using namespace std;

typedef string ItemType;

class RoomScheduleLinkedList
{
private:
	struct Node
	{
		ItemType guestName;	// data item
		ItemType roomNumber;
		tm date;
	};
		Node* next;	// pointer pointing to next item

	Node* firstNode;	// point to the first item
	int  size;			// number of items in the RoomScheduleLinkedList

public:



	// constructor
	RoomScheduleLinkedList();

	// add a new item to the back of the RoomScheduleLinkedList (append)
	// pre : size < MAX_SIZE
	// post: new item is added to the back of the RoomScheduleLinkedList
	//       size of RoomScheduleLinkedList is increased by 1
	bool add(ItemType guestName, ItemType roomType, tm date);

	// remove an item at a specified position in the RoomScheduleLinkedList
	// pre : 1 <= index <= size
	// post: item is removed the specified position in the RoomScheduleLinkedList
	//       items after the position are shifted forward by 1 position
	//       size of RoomScheduleLinkedList is decreased by 1
	void remove(ItemType guestName, ItemType roomType, tm date);

	// get an item at a specified position of the RoomScheduleLinkedList (retrieve)
	// pre : 1 <= index <= size
	// post: none
	// return the item in the specified index of the RoomScheduleLinkedList
	ItemType get(int index);

	// check if the RoomScheduleLinkedList is empty
	// pre : none
	// post: none
	// return true if the RoomScheduleLinkedList is empty; otherwise returns false
	bool isEmpty();

	// check the size of the RoomScheduleLinkedList
	// pre : none
	// post: none
	// return the number of items in the RoomScheduleLinkedList
	int getLength();

	//------------------- Other useful functions -----------------

	// display the items in the RoomScheduleLinkedList
	void print();

	// void replace(int index, ItemType item);
	// int search(ItemType item);
};
