#include "RoomScheduleDictionary.h"
#include <string>
// constructor
RoomScheduleDictionary::RoomScheduleDictionary(int maxRoom, string roomType) {
	MaxRoom = maxRoom;
	roomTypeName = roomType;
	for (int i = 0; i < MAX_SIZE;i++)
	{
		items[i] = NULL;
	}
};

RoomScheduleDictionary::RoomScheduleDictionary() {
	for (int i = 0; i < MAX_SIZE; i++)
	{
		items[i] = NULL;
	}
};

// destructor is to remove dynamic memory
// static memory is destroyed when program ends. But not dynamic memory
// auto called by program, programmer does not call this destructor
RoomScheduleDictionary::~RoomScheduleDictionary(){
	//for (int i = 0; i < MAX_SIZE; i++)
	//{
	//	if (items[i] != NULL)
	//	{
	//		Node* temp = items[i];
	//		while (temp != NULL)
	//		{
	//			items[i] = temp->next;
	//			temp->next = NULL;
	//			delete temp;
	//			temp = items[i];
	//		}
	//	}
	//}
};

int RoomScheduleDictionary::hash(KeyType key){
	key.tm_year -= 1900;
	key.tm_mon -= 1;
	key.tm_min = 0;
	key.tm_sec = 0;
	key.tm_hour = 0;
	time_t time = mktime(&key) / 86400;
	if (firstHashRoom == NULL) {
		firstHashRoom = (int) time;
	}
	return time-firstHashRoom;
};



// add a new item with the specified key to the RoomScheduleDictionary
// pre : none
// post: new item is added to the RoomScheduleDictionary
	// add entry for every date from checkin to checkout exclusive, check if null, add info to list
bool RoomScheduleDictionary::add(tm checkInDate, tm checkOutDate, string guestName, string roomNumber){
	//change to time_t for comparsion and looping
	checkInDate.tm_year -= 1900;
	checkInDate.tm_mon -= 1;
	checkInDate.tm_min = 0;
	checkInDate.tm_sec = 0;
	checkInDate.tm_hour = 0;
	checkOutDate.tm_year -= 1900;
	checkOutDate.tm_mon -= 1;
	checkOutDate.tm_min = 0;
	checkOutDate.tm_sec = 0;
	checkOutDate.tm_hour = 0;
	time_t checkInTime = mktime(&checkInDate);
	time_t checkOutTime = mktime(&checkOutDate);
	//change checkInDate back to original date to be hashed later
	checkInDate.tm_year += 1900;
	checkInDate.tm_mon += 1;
	tm currentDate = checkInDate;
	//add for all dates from checkInDate to checkOutDate
	while (checkInTime < checkOutTime) {
		int index = hash(currentDate);
		if (items[index] == NULL) {
			items[index] = new RoomScheduleLinkedList();
			items[index]->add(guestName, roomNumber, currentDate);
		}
		else {
			items[index]->add(guestName, roomNumber, currentDate);
		}
		currentDate.tm_mday += 1;
		checkInTime += 86400;
	}
	return true;
};

// remove an item with the specified key in the RoomScheduleDictionary
// pre : key must exist in the RoomScheduleDictionary
// post: item is removed from the RoomScheduleDictionary
//       size of RoomScheduleDictionary is decreased by 1
void RoomScheduleDictionary::remove(KeyType newKey, string guestName, string roomNumber){
	int index = hash(newKey);
	//Node* newNode = new Node;
	//newNode->date = newKey;
	//newNode->guestName = guestName;
	//newNode->next = NULL;
	if (items[index] == NULL) {
		return;
	}
	else {
		items[index]->remove(guestName, roomNumber, newKey);
	}
	return;
};

// get an item with the specified key in the RoomScheduleDictionary (retrieve)
// pre : key must exist in the RoomScheduleDictionary
// post: none
// return the item with the specified key from the RoomScheduleDictionary
//
//hash, check if null, get MaxValue - list.size
int RoomScheduleDictionary::getAvailableRoomNumber(KeyType key) {
	int index = hash(key);
	return MaxRoom - items[index]->getLength();
};

//hash, get list of stayees and the room they are in
//RoomScheduleLinkedList RoomScheduleDictionary::getRoomDateInfo(KeyType key) {
//	int index = hash(key);
//	return *items[index];
//};

//print guests which are staying on that date
void RoomScheduleDictionary::printDateGuests(tm key) {
	int index = hash(key);
	if (items[index] != NULL) {
		items[index]->printDateGuests();
	}
};
// get an item with the specified key in the RoomScheduleDictionary (retrieve)
// pre : key must exist in the RoomScheduleDictionary
// post: none
// return the item with the specified key from the RoomScheduleDictionary
//string RoomScheduleDictionary::get(KeyType key){
//	int index = hash(key);
//	if (items[index] != NULL) {
//		Node* currentNode = items[index];
//		if (currentNode->key == key) {
//			return currentNode->item;
//		}
//		while (currentNode->next != NULL)
//		{
//			currentNode = currentNode->next;
//			if (currentNode->key == key) {
//				return currentNode->item;
//			}
//		}
//	}
//};

// check if the RoomScheduleDictionary is empty
// pre : none
// post: none
// return true if the RoomScheduleDictionary is empty{}; otherwise returns false
//bool RoomScheduleDictionary::isEmpty(){
//	return size == 0;
//};

// check the size of the RoomScheduleDictionary
// pre : none
// post: none
// return the number of items in the RoomScheduleDictionary
//int RoomScheduleDictionary::getLength(){
//	return size;
//};

//------------------- Other useful functions -----------------

// display the items in the RoomScheduleDictionary
//void RoomScheduleDictionary::print(){
//	string s;
//	for (int i = 0;i < MAX_SIZE;i++) {
//		if (items[i] != NULL) {
//			Node* currentNode = items[i];
//			s += currentNode->key + ":" + currentNode->item + ",";
//			while (currentNode->next != NULL) {
//				currentNode = currentNode->next;
//				s += currentNode->key + ":" + currentNode->item + ",";
//			}
//		}
//	}
//	std::cout << s<<endl;
//};