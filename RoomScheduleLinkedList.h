// Group 12
// Chua Dong En, S10202623A
// Poh Jia Yong, S10202579J
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

	// constructor
	RoomScheduleLinkedList();

	// destructor
	~RoomScheduleLinkedList();

	// add an item to the back of the RoomScheduleLinkedList (append)
	bool add(string guestName, string roomNumber, tm date,int bid);

	// remove an item at a specified position in the RoomScheduleLinkedList
	void remove(string guestName, string roomNumber, tm date);

	// check if the RoomScheduleLinkedList is empty
	bool isEmpty();

	// check the roomScheduleLinkedListSize of the RoomScheduleLinkedList
	int getLength();

	// display all the items in the RoomScheduleLinkedList
	void print();

	//print guests which are staying on that date
	void printDateGuests();

	//fill map with dates that each room is occupied
	void getOccupiedDatesFromDay(map<string, string>& roomOccupiedDates, tm date);

	//fill map with occupied room numbers (no date needed)
	void getOccupiedRooms(map<string, int> &occupiedRoomsMap);

	//fill map with bookingIDs of occupied rooms
	void getBookedRooms(map<int, int>& occupiedRoomsMap);

};
