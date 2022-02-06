// Group 12
// Chua Dong En, S10202623A
#include<string>
#include<iostream>
#include<map>
using namespace std;

class RoomScheduleLinkedList
{
private:
	struct Node
	{
		string guestName;	// data item
		string roomNumber;
		int bookingID;
		tm date;
		Node* next;	// pointer pointing to next item
	};


	Node* firstNode;	// point to the first item
	int  roomScheduleLinkedListSize;			// number of items in the RoomScheduleLinkedList

public:

	// Group 12
	// Chua Dong En, S10202623A
	// constructor
	RoomScheduleLinkedList();

	// Group 12
	// Chua Dong En, S10202623A
	// destructor
	~RoomScheduleLinkedList();

	// Group 12
	// Chua Dong En, S10202623A
	// add an item to the back of the RoomScheduleLinkedList (append)
	bool add(string guestName, string roomNumber, tm date,int bid);

	// Group 12
	// Chua Dong En, S10202623A
	// remove an item at a specified position in the RoomScheduleLinkedList
	void remove(string guestName, string roomNumber, tm date);

	// Group 12
	// Chua Dong En, S10202623A
	// check if the RoomScheduleLinkedList is empty
	bool isEmpty();

	// Group 12
	// Chua Dong En, S10202623A
	// check the roomScheduleLinkedListSize of the RoomScheduleLinkedList
	int getLength();

	// Group 12
	// Chua Dong En, S10202623A
	// display all the items in the RoomScheduleLinkedList
	void print();

	// Group 12
	// Chua Dong En, S10202623A
	//print guests which are staying on that date
	void printDateGuests();

	// Group 12
	// Chua Dong En, S10202623A
	//fill map with dates that each room is occupied
	void getOccupiedDatesFromDay(map<string, string>& roomOccupiedDates, tm date);

	// Group 12
	// Chua Dong En, S10202623A
	//fill map with occupied room numbers (no date needed)
	void getOccupiedRooms(map<string, int> &occupiedRoomsMap);

	// Group 12
	// Chua Dong En, S10202623A
	//fill map with bookingIDs of occupied rooms
	void getBookedRooms(map<int, int>& occupiedRoomsMap);

};
