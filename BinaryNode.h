#pragma once
#include "Booking.h"
typedef Booking ItemType;

struct BinaryNode
{
	Booking  item;	// data item
	BinaryNode* left;	// pointer pointing to left subtree
	BinaryNode* right;	// pointer pointing to right subtree
};