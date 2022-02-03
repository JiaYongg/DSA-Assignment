#pragma once
#include "BookingDict.h"
typedef Booking ItemType;

struct BinaryNode
{
	Booking  item;	// data item
	BinaryNode* left;	// pointer pointing to left subtree
	BinaryNode* right;	// pointer pointing to right subtree
};