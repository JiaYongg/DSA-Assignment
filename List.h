// List.h - - Specification of List ADT

#include<string>
#include<iostream>
using namespace std;

typedef string ItemType;

class List
{
private:
	struct Node
	{
		ItemType guestName;	// data item
		ItemType roomNumber;
		tm date;
		Node* next;	// pointer pointing to next item
	};

	Node* firstNode;	// point to the first item
	int  size;			// number of items in the list

public:



	// constructor
	List();

	// add a new item to the back of the list (append)
	// pre : size < MAX_SIZE
	// post: new item is added to the back of the list
	//       size of list is increased by 1
	bool add(ItemType guestName, ItemType roomType, tm date);

	// remove an item at a specified position in the list
	// pre : 1 <= index <= size
	// post: item is removed the specified position in the list
	//       items after the position are shifted forward by 1 position
	//       size of list is decreased by 1
	void remove(ItemType guestName, ItemType roomType, tm date);

	// get an item at a specified position of the list (retrieve)
	// pre : 1 <= index <= size
	// post: none
	// return the item in the specified index of the list
	ItemType get(int index);

	// check if the list is empty
	// pre : none
	// post: none
	// return true if the list is empty; otherwise returns false
	bool isEmpty();

	// check the size of the list
	// pre : none
	// post: none
	// return the number of items in the list
	int getLength();

	//------------------- Other useful functions -----------------

	// display the items in the list
	void print();

	// void replace(int index, ItemType item);
	// int search(ItemType item);
};