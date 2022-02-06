// BST.cpp - Implementation of Binary Search Tree
#include "BST.h"
#include <time.h>

#define max(x,y) ((x > y)? x : y)

// constructor
BST::BST()
{
	root = NULL;
}

// search for a Booking in the binary search tree
BinaryNode* BST::search(tm date, string guestName, string roomType)
{
	return search(root, date, guestName, roomType);
}

BinaryNode* BST::search(BinaryNode* t, tm date, string guestName, string roomType)
{
	if (t == NULL)	// Booking not found
		return NULL;
	else
	{
		if (!(t->item.checkinDate.tm_year < 1000)) {
			t->item.checkinDate.tm_year -= 1900;
			t->item.checkinDate.tm_mon -= 1;
			t->item.checkinDate.tm_hour = 0;
			t->item.checkinDate.tm_min = 0;
			t->item.checkinDate.tm_sec = 0;
		}
		if (!(date.tm_year < 1000)) {
			date.tm_year -= 1900;
			date.tm_mon -= 1;
			date.tm_hour = 0;
			date.tm_min = 0;
			date.tm_sec = 0;
		}
		time_t checkindate = mktime(&t->item.checkinDate);
		time_t inputdate = mktime(&date);
		double diff = difftime(checkindate, inputdate);
		// use difftime to find the difference between the input date and the current iteration date
		if (diff == 0 && t->item.bookingGuestName == guestName && t->item.bookingRoomType == roomType)// item found
			return t;
		else
			// diff < 0 = unix time difference is negative, therefore search left side of tree
			// else diff >= 0 = search right side of the tree
			if (diff < 0)	// search in left subtree
				return search(t->left, date, guestName, roomType);
			else					// search in right subtree
				return search(t->right, date, guestName, roomType);
	}
}


// insert a Booking object to the binary search tree
void BST::insert(Booking b, map<string, RoomScheduleDictionary>& roomScheduleDictMap)
{
	if (b.bookingStatus != "Checked In") {
		int roomAvail = roomScheduleDictMap[b.bookingRoomType].getAvailableRoomNumber(b.checkinDate,b.checkOutDate);
		//cout << "Booking" << b.bookingGuestName << endl;
		if (roomAvail > 0) {
			insert(root, b);
			roomScheduleDictMap[b.bookingRoomType].add(b.checkinDate, b.checkOutDate, b.bookingGuestName, b.bookingRoomNumber,b.bookingID);
		}
		else {
			cout << "There are no rooms available" << endl;
		}
	}
	else {
		//cout << "Checked in" << b.bookingGuestName << endl;
		insert(root, b);
		roomScheduleDictMap[b.bookingRoomType].add(b.checkinDate, b.checkOutDate, b.bookingGuestName, b.bookingRoomNumber,b.bookingID);
	}
	

}

void BST::insert(BinaryNode* &t, Booking b)
{
	//cout << t <<b.bookingGuestName<< endl;
	if (t == NULL)
	{
		BinaryNode *newNode = new BinaryNode;
		newNode->item = b;
		newNode->left = NULL;
		newNode->right = NULL;
		t = newNode;
	}
	else 
	{
		time_t checkindate = mktime(&t->item.checkinDate);
		time_t inputdate = mktime(&b.checkinDate);
		double diff = difftime(checkindate, inputdate);

		if (diff < 0)
			insert(t->left, b);  // insert in left subtree
		else
			insert(t->right, b); // insert in right subtree	
	}

	t = balance(t);				// balance the tree (AVL Tree function)
}


//// traverse the binary search tree in inorder
void BST::inorder(tm start, tm end)
{
	if (isEmpty())
		cout << "No item found" << endl;
	else
		inorder(root,start, end);
}

void BST::inorder(BinaryNode* t, tm start, tm end)
{
	if (t != NULL)
	{
		time_t start_t = mktime(&start);
		time_t end_t = mktime(&end);

		time_t bstStart_t = mktime(&t->item.checkinDate);
		time_t bstEnd_t = mktime(&t->item.checkOutDate);

		double inputStartAndBstEnd = difftime(start_t, bstEnd_t);

		double inputEndAndBstStart = difftime(end_t, bstStart_t);

		// check if the input range and the booking range overlaps
		// prints out the Booking ID and Guest Name if overlaps(in range)
		if (inputStartAndBstEnd < 0 && inputEndAndBstStart >= 0)
			cout << "Booking ID: " << t->item.bookingID << " "  << t->item.bookingGuestName << endl;
		inorder(t->left,start, end);
		inorder(t->right, start, end);
	}
}

void BST::inorderoverdue(tm current, RoomScheduleDictionary& rsd)
{
	if (isEmpty())
		cout << "No item found" << endl;
	else
		inorderoverdue(root, current, rsd);
}

void BST::inorderoverdue(BinaryNode* t, tm current, RoomScheduleDictionary& rsd)
{
	if (t != NULL)
	{
		if (t->item.bookingStatus == "Booking")
		{
			time_t checkInDate = mktime(&t->item.checkinDate);
			time_t inputCheckInDate = mktime(&current);
			double diff = difftime(checkInDate, inputCheckInDate);
			if (diff < 0)
			{
				// Set status to "Overdue"
				t->item.bookingStatus == "Overdue";
				// Remove booking from roomschedule
				rsd.remove(t->item.checkinDate, t->item.checkOutDate, t->item.bookingGuestName, t->item.bookingRoomNumber);
				// free up the room
			}
		}

		inorderoverdue(t->left, current, rsd);
		inorderoverdue(t->right, current, rsd);
	}
}

void BST::inorderpopular(map<string, int> &roomTypeMap)
{
	if (isEmpty())
		cout << "No item found" << endl;
	else
		inorderpopular(root, roomTypeMap);
}

void BST::inorderpopular(BinaryNode* t, map<string, int> &roomTypeMap)
{
	if (t != NULL)
	{

		roomTypeMap[t->item.bookingRoomType] += 1;

		inorderpopular(t->left, roomTypeMap);
		inorderpopular(t->right, roomTypeMap);
	}
}

// check if the binary search tree is empty
bool BST::isEmpty()
{
	return (root == NULL);
}

// delete a Booking from the binary search tree
void BST::remove(tm date, string guestName, string roomType)
{
	remove(root, date, guestName, roomType);
	balanceTree(root);			// AVL Tree function
}

void BST::remove(BinaryNode* &t, tm date, string guestName, string roomType)
{
	if (t != NULL)
	{
		time_t checkindate = mktime(&t->item.checkinDate);
		time_t inputdate = mktime(&date);
		double diff = difftime(checkindate, inputdate);
		if (diff < 0)			// search in left subtree
			remove(t->left, date, guestName, roomType);
		else if (diff > 0)	// search in right subtree
			remove(t->right, date, guestName, roomType);
		else						// diff == 0 (found) - base case
		{
			if (t->left == NULL && t->right == NULL) // case 1 : node has 0 child
			{
				BinaryNode* temp = t;	// to be deleted
				t = NULL;
				delete temp;			// delete the node
			}
			else if (t->left == NULL)	// case 2 : node has 1 child
			{
				BinaryNode* temp = t;	// node to be deleted

				if (t == root)			// current node is root
					root = t->right;
				else
					t = t->right;

				delete temp;			// delete the node
			}
			else if (t->right == NULL)	// case 2 : node has 1 child
			{
				BinaryNode* temp = t;	// node to be deleted

				if (t == root)			// current node is root
					root = t->left;
				else
					t = t->left;

				delete temp;			// delete the node
			}
			else // case 3 : node has 2 children
			{
				BinaryNode* successor = t->left;
				while (successor->right != NULL)	// search for right most node in left sub-tree
					successor = successor->right;

				ItemType item = successor->item;	
				remove(t->left, item.checkinDate, item.bookingGuestName, item.bookingRoomType);  // delete the successor (either case 1 or case 2)
				t->item = item;					// replace the node�s Booking with that of the successor
			}
		}
	}
}

// change status from "Booked" to "Checked In" in tree and validates if the status is already "Checked In"
// check if room is available, assign room to the guest who just checked in if room available
// else not available, check in fails
bool BST::checkIn(tm date, string guestName, string roomType, map<string, RoomScheduleDictionary>& roomScheduleDictMap, Room roomArray[20])
{
	BinaryNode* b = search(date, guestName, roomType);
	if (b == NULL) {
		return false;
	}
	if (b->item.bookingStatus == "Checked In") {
		return false;
	}
	else
	{
		b->item.bookingStatus = "Checked In";
		// need to assign room to the guest who just checked in also need to check if the room is avail.
	    map<string,int> occupiedRooms = roomScheduleDictMap[b->item.bookingRoomType].getAvailrooms(b->item.checkinDate, b->item.checkOutDate);
		if (occupiedRooms.size() != 0) {
			for (int i = 0; i < 20; i++) {
				for (const auto& p : occupiedRooms)
				{
					if (roomArray[i].roomTypeName == b->item.bookingRoomType) {
						if (roomArray[i].roomNumber != p.first) {
							b->item.bookingRoomNumber = roomArray[i].roomNumber;
						}
					}
				}
			}
		}
		else {
			for (int i = 0; i < 20; i++) {
				if (roomArray[i].roomTypeName == b->item.bookingRoomType) {
						b->item.bookingRoomNumber = roomArray[i].roomNumber;
				}
			}
		}
		
		cout << "Checked in to: "<<b->item.bookingRoomNumber<<endl;
		return true;
	}
	return true;
}

void BST::printPopular(map<string, int> &roomTypeMap)
{
	inorderpopular(roomTypeMap);
}

void BST::printRange(tm start, tm end)
{
	inorder(start, end);
}

void BST::checkOverDue(tm current, RoomScheduleDictionary &rsd)
{
	inorderoverdue(current, rsd);
}