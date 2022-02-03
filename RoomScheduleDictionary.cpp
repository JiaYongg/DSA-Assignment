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
	time_t time = mktime(&key) / 86400;
	if (firstHash == NULL) {
		firstHash = (int) time;
	}
	return time-firstHash;
};

// add a new item with the specified key to the RoomScheduleDictionary
// pre : none
// post: new item is added to the RoomScheduleDictionary
//       size of RoomScheduleDictionary is increased by 1
bool RoomScheduleDictionary::add(KeyType newKey, string guestName, string roomNumber){
	int index = hash(newKey);
	//Node* newNode = new Node;
	//newNode->date= newKey;
	//newNode->guestName = guestName;
	//newNode->next = NULL;
	if (items[index]==NULL) {
		items[index] = new RoomScheduleLinkedList();
		items[index]->add(guestName, roomNumber, newKey);
	}
	else {
		items[index]->add(guestName, roomNumber, newKey);
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
RoomScheduleLinkedList RoomScheduleDictionary::getRoomDateInfo(KeyType key) {
	int index = hash(key);
	return *items[index];
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