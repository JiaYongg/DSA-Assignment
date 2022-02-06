// Group 12
// Poh Jia Yong, S10202579J
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
	Booking(int bookID, tm bookDate, string bookGuestName, string bookRoomNum, string bookRoomType, string bookStatus,
	tm bookCheckInDate, tm bookCheckOutDate, int bookGuestNumber, string bookSpecialReq);
};
