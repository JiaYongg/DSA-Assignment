#pragma once
#include<iostream>
#include <string>
using namespace std;

class Booking
{
public:
	int bookingID;
	tm bookingDate;
	string bookingGuestName;
	string bookingRoomNumber;
	string bookingRoomType;
	string bookingStatus;
	tm checkinDate;
	tm checkOutDate;
	int bookingGuestNumber;
	string bookingSpecialRequest;
	// constructor
	Booking();
};
