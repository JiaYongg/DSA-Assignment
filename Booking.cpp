// Group 12
// Chua Dong En, S10202623A
// Poh Jia Yong, S10202579J
#include "Booking.h"
#include <string>

Booking::Booking() {};

Booking::Booking(int bookID, tm bookDate, string bookGuestName, string bookRoomNum, string bookRoomType, string bookStatus,
	tm bookCheckInDate, tm bookCheckOutDate, int bookGuestNumber, string bookSpecialReq)
{
	bookingID = bookID;
	bookingDate = bookDate;
	bookingGuestName = bookGuestName;
	bookingRoomNumber = bookRoomNum;
	bookingRoomType = bookRoomType;
	bookingStatus = bookStatus;
	checkinDate = bookCheckInDate;
	checkOutDate = bookCheckOutDate;
	bookingGuestNumber = bookGuestNumber;
	bookingSpecialRequest = bookSpecialReq;
}