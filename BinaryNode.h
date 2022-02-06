// Group 12
// Chua Dong En, S10202623A
// Poh Jia Yong, S10202579J
#pragma once
#include "Booking.h"
typedef Booking ItemType;

struct BinaryNode
{
	Booking  item;	// data item
	BinaryNode* left;	// pointer pointing to left subtree
	BinaryNode* right;	// pointer pointing to right subtree
};