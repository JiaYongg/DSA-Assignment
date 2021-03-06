// Group 12
// Chua Dong En, S10202623A
// Poh Jia Yong, S10202579J
#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <ostream>
#include "BookingDict.h"
#include "Room.h"
#include "Booking.h"
#include <map>
#include <string.h>
#include <vector>
#include <chrono>


//#include "Dictionary.h"
using namespace std;

void addToCsv(Booking b);
void menu();

int main()
{

    //Contains all rooms (index = room no. -101)
    Room roomArray[20];
    //Contains all room types and count of how many rooms they have, used to dynamically generate RoomScheduleDictionaries
    map<string, int> roomTypeMap;
    //Contains all RoomScheduleDictionaries 
    map<string, RoomScheduleDictionary> roomScheduleMap;
    // File I/O Rooms.csv
    fstream roomsFile("Rooms.csv", ios::in);
    vector<vector<string>> roomsContent;
    vector<string> roomsRow;
    string roomsLine, roomsWord;

    //Read rooms file into lines
    if (roomsFile.is_open())
    {
        while (getline(roomsFile, roomsLine))
        {
            roomsRow.clear();

            stringstream str(roomsLine);

            while (getline(str, roomsWord, ','))
                roomsRow.push_back(roomsWord);
            roomsContent.push_back(roomsRow);
        }
    }

    //Loop through lines of rooms and store them into roomArray and roomTypeMap
    for (int i = 1; i < roomsContent.size(); i++)
    {
        Room r;
        r.roomNumber = roomsContent[i][0];
        r.roomTypeName = roomsContent[i][1];
        r.roomTypeCost = stoi(roomsContent[i][2]);
        string roomNo = r.roomNumber.substr(5, 3);
        int index = stoi(roomNo)-101;
        roomArray[index] = r;
        roomTypeMap[r.roomTypeName] += 1;
    }

    //Loop through roomTypeMap and dynamically create RoomScheduleDictionaries in roomScheduleMap
    for (const auto& p : roomTypeMap)
    {
        RoomScheduleDictionary dynamicRoomTypeDictionary(p.second, p.first);
        roomScheduleMap[p.first] = dynamicRoomTypeDictionary;
    }
    
    BookingDict bookingDictionary;
    //File I/O Bookings.csv
    fstream bookingsFile("Bookings.csv", ios::in);
    vector<vector<string>> content;
    vector<string> row;
    string line, word;

    //Read bookings file into lines
    if (bookingsFile.is_open())
    {
        while (getline(bookingsFile, line))
        {
            row.clear();

            stringstream str(line);

            while (getline(str, word, ','))
                row.push_back(word);
            content.push_back(row);
        }
    }
    //bookID to be used as the last entry for excel for add
    int bookID = 0;
    //Loop through lines of bookings and store them into bookDictionary if the booking status is anything but "Checked Out"
    for (int i = 1; i < content.size(); i++)
    {
        Booking b;
        tm date;
        b.bookingID = stoi(content[i][0]); // stoi converts string to int
        sscanf_s(content[i][1].c_str(), "%d/%d/%4d  %d:%d:%d", &date.tm_mday, &date.tm_mon, &date.tm_year, &date.tm_hour, &date.tm_min, &date.tm_sec);
        b.bookingDate = date;
        b.bookingGuestName = content[i][2];
        b.bookingRoomNumber = content[i][3];
        b.bookingRoomType = content[i][4];
        b.bookingStatus = content[i][5];
        sscanf_s(content[i][6].c_str(), "%d/%d/%4d  %d:%d:%d", &date.tm_mday, &date.tm_mon, &date.tm_year, &date.tm_hour, &date.tm_min, &date.tm_sec);
        b.checkinDate = date;
        sscanf_s(content[i][7].c_str(), "%d/%d/%4d  %d:%d:%d", &date.tm_mday, &date.tm_mon, &date.tm_year, &date.tm_hour, &date.tm_min, &date.tm_sec);
        b.checkOutDate = date;
        b.bookingGuestNumber = stoi(content[i][8]);

        if (content[i].size() == 10)
        {
            b.bookingSpecialRequest = content[i][9];
        }
        if (b.bookingStatus != "Checked Out") {
            bookingDictionary.add(b,roomScheduleMap);
        }
        bookID = b.bookingID; // sets bookID to the last booking ID in excel
    }
   
    // Current date of program is 1st April 2021
    char currentDate[] = "01/04/2021 00:00:00";
    tm currentDatetm;
    sscanf_s(currentDate, "%d/%d/%4d  %d:%d:%d", &currentDatetm.tm_mday, &currentDatetm.tm_mon, &currentDatetm.tm_year, 
        &currentDatetm.tm_hour, &currentDatetm.tm_min, &currentDatetm.tm_sec);

    //Menu
    bool flag = true;
    while (flag)
    {
        cout << "--------------------------------------------" << endl;
        cout << "Current date (dd/mm/yyyy/) is : " << currentDatetm.tm_mday << "/" << currentDatetm.tm_mon << "/" << currentDatetm.tm_year << endl;
        menu();
        int option = 0;
        cout << "Pick an option: ";
        cin >> option;

        switch (option)
        {
            // Basic Features
            case 1: 
            {
                // Group 12
                // Poh Jia Yong, S10202579J
                //Check in guest function
                tm checkInDate;
                char checkInInput[] = "";
                string guestName, roomType;
               
                cout << "----------------Check In Guest-------------------\n";
                cout << "Enter Guest Name: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, guestName);


                cout << "Enter Room Type: ";
                getline(cin, roomType);

                cout << "Enter Check In Date (dd/mm/yyyy/): ";
                cin >> checkInInput;
                sscanf_s(checkInInput, "%d/%d/%4d", &checkInDate.tm_mday, &checkInDate.tm_mon, &checkInDate.tm_year);
                checkInDate.tm_min = 0;
                checkInDate.tm_sec = 0;
                checkInDate.tm_hour = 0;

                bool checkInStatus = bookingDictionary.checkIn(checkInDate, guestName, roomType, roomScheduleMap,roomArray);

                if (checkInStatus)
                    cout << "Checked In Sucessfully! \n";
                else
                    cout << guestName + " is already checked in \n";
                break;
            }
                
            case 2:
            {
                // Group 12
                // Poh Jia Yong, S10202579J
                // Add booking function
                tm bookingDate, checkInDate, checkOutDate;
                char checkInInput[] = "";
                char checkOutInput[] = "";
                string guestName, roomType, status, specialReq;
                int numOfGuest;

                // bookID is +1 of latest record in excel
                bookID += 1;

                // bookingDate is datetime.now of program's current date
                bookingDate = currentDatetm;

                cout << "----------------Add Booking-------------------\n";
                cout << "Enter Guest Name: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, guestName);

                cout << "Enter Room Type: ";
                getline(cin, roomType);

                // status defaults to "Booked" upon completion of booking
                status = "Booked";

                cout << "Enter Check In Date (dd/mm/yyyy/): ";
                cin >> checkInInput;
                sscanf_s(checkInInput, "%d/%d/%4d", &checkInDate.tm_mday, &checkInDate.tm_mon, &checkInDate.tm_year);
                checkInDate.tm_min = 0;
                checkInDate.tm_sec = 0;
                checkInDate.tm_hour = 0;

                cout << "Enter Check Out Date (dd/mm/yyyy/): ";
                cin >> checkOutInput;
                sscanf_s(checkOutInput, "%d/%d/%4d", &checkOutDate.tm_mday, &checkOutDate.tm_mon, &checkOutDate.tm_year);
                checkOutDate.tm_min = 0;
                checkOutDate.tm_sec = 0;
                checkOutDate.tm_hour = 0;

                cout << "Enter Number of Guest(s): ";
                cin >> numOfGuest;

                string yn;
                cout << "Any Special Request? (y/n): ";
                cin >> yn;

                if (yn != "y")
                {
                    specialReq = "";
                }
                else
                {
                    cout << "Enter Special Request: ";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    getline(cin, specialReq);
                }

                Booking b(bookID, bookingDate, guestName, "", roomType, status, checkInDate, checkOutDate, numOfGuest, specialReq);

                bool added = bookingDictionary.add(b,roomScheduleMap);

                if (added)
                    cout << "Booking successfully added with the Booking ID of " + to_string(bookID) + "\n";

                // Write to excel once done
                addToCsv(b);
                break;
            }

            case 3:
            {

                // Group 12
                // Chua Dong En, S10202623A
                // Display guest staying in hotel function
                tm selectedDate;
                char selectedDateInput[] = "";
                cout << "----------------Display Guest staying in Hotel-------------------\n";
                cout << "Enter Date (dd/mm/yyyy/): ";
                cin >> selectedDateInput;
                selectedDate.tm_min = 0;
                selectedDate.tm_sec = 0;
                selectedDate.tm_hour = 0;
                sscanf_s(selectedDateInput, "%d/%d/%4d", &selectedDate.tm_mday, &selectedDate.tm_mon, &selectedDate.tm_year);
                //Loop through each roomScheduleDict in roomScheduleMap using roomTypeMap
                for (const auto& p : roomTypeMap)
                {
                    roomScheduleMap[p.first].printDateGuests(selectedDate);
                }
                cout << endl;
                break;
            }

            case 4:
            {
                // Group 12
                // Chua Dong En, S10202623A
                //NOTE! For booked bookings, room has not been occupied yet therefore it is not shown
                // Display room occupied by month function
                tm selectedDate;
                char selectedDateInput[] = "";
                cout << "----------------Display Room Occupied by Month-------------------\n";
                cout << "Enter Date (mm/yyyy): ";
                cin >> selectedDateInput;
                selectedDate.tm_min = 0;
                selectedDate.tm_sec = 0;
                selectedDate.tm_hour = 0;
                sscanf_s(selectedDateInput, "%d/%4d", &selectedDate.tm_mon, &selectedDate.tm_year);
                map<string, string> roomOccupiedDates;
                for (int i = 0; i < 20; i++) {
                    string roomNumber = roomArray[i].roomNumber;
                    roomOccupiedDates[roomNumber] = "";
                }
                for (const auto& p : roomTypeMap)
                {
                    roomScheduleMap[p.first].getOccupiedDatesFromMonth(roomOccupiedDates, selectedDate);
                }
                for (const auto& p :roomOccupiedDates)
                {
                    cout<< p.first << ":"<<'\t' << p.second.substr(0,p.second.size()-2) << std::endl;
                    //cout<< p.first << ":"<<'\t' << p.second << std::endl;
                }
                cout << endl;
                break;
            }
            // Additional Features
            case 5:
            {
                // Group 12
                // Poh Jia Yong, S10202579J
                // Delete booking function
                tm checkInDate;
                char checkInInput[] = "";
                string guestName, roomType;

                cout << "----------------Delete Booking-------------------\n";
                cout << "Enter Guest Name: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, guestName);

                cout << "Enter Room Type: ";
                getline(cin, roomType);

                cout << "Enter Check In Date (dd/mm/yyyy/): ";
                cin >> checkInInput;
                sscanf_s(checkInInput, "%d/%d/%4d", &checkInDate.tm_mday, &checkInDate.tm_mon, &checkInDate.tm_year);
                checkInDate.tm_min = 0;
                checkInDate.tm_sec = 0;
                checkInDate.tm_hour = 0;

                bookingDictionary.remove(checkInDate, guestName, roomType, roomScheduleMap);

                break;
            }

            case 6:
            {

                // Group 12
                // Chua Dong En, S10202623A
                // Search for most popular room type function
                map<string, int> popularRoomTypeMap;
                for (const auto& p : roomTypeMap)
                {
                    popularRoomTypeMap[p.first] = 0;
                }
                bookingDictionary.printPopular(popularRoomTypeMap);
                for (const auto& p : popularRoomTypeMap)
                {
                    cout <<p.first<<"  \t" << popularRoomTypeMap[p.first] << endl;
                }

                break;
            }

            case 7:
            {
                // Group 12
                // Poh Jia Yong, S10202579J
                // Check in guest without booking function
                tm bookingDate, checkInDate, checkOutDate;
                char checkInInput[] = "";
                char checkOutInput[] = "";
                string guestName, roomType, status, specialReq;
                int numOfGuest;

                // bookID is +1 of latest record in excel
                bookID += 1;

                // bookingDate is datetime.now of program's current date
                bookingDate = currentDatetm;

                cout << "----------------Check In Guest without booking-------------------\n";
                cout << "Enter Guest Name: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, guestName);

                cout << "Enter Room Type: ";
                getline(cin, roomType);

                // status defaults to "Booked" upon completion of booking
                status = "Booked";

                cout << "Enter Check In Date (dd/mm/yyyy/): ";
                cin >> checkInInput;
                sscanf_s(checkInInput, "%d/%d/%4d", &checkInDate.tm_mday, &checkInDate.tm_mon, &checkInDate.tm_year);
                checkInDate.tm_min = 0;
                checkInDate.tm_sec = 0;
                checkInDate.tm_hour = 0;

                cout << "Enter Check Out Date (dd/mm/yyyy/): ";
                cin >> checkOutInput;
                sscanf_s(checkOutInput, "%d/%d/%4d", &checkOutDate.tm_mday, &checkOutDate.tm_mon, &checkOutDate.tm_year);
                checkOutDate.tm_min = 0;
                checkOutDate.tm_sec = 0;
                checkOutDate.tm_hour = 0;

                cout << "Enter Number of Guest(s): ";
                cin >> numOfGuest;

                string yn;
                cout << "Any Special Request? (y/n): ";
                cin >> yn;

                if (yn != "y")
                {
                    specialReq = "";
                }
                else
                {
                    cout << "Enter Special Request: ";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    getline(cin, specialReq);
                }

                Booking b(bookID, bookingDate, guestName, "", roomType, status, checkInDate, checkOutDate, numOfGuest, specialReq);

                // write to excel once done
                
                bookingDictionary.add(b,roomScheduleMap);
                bookingDictionary.checkIn(b.checkinDate, b.bookingGuestName, b.bookingRoomType,roomScheduleMap,roomArray);

                Booking newBooking = bookingDictionary.get(b.checkinDate, b.bookingGuestName, b.bookingRoomType);
                addToCsv(newBooking);

                break;
            }

            case 8:
            {
                // Group 12
                // Poh Jia Yong, S10202579J
                // Display bookings given range function
                tm startDate, endDate;
                char startInput[] = "";
                char endInput[] = "";

                cout << "----------------Display bookings given range-------------------\n";
                cout << "Enter Start Date (dd/mm/yyyy/): ";
                cin >> startInput;
                startDate.tm_min = 0;
                startDate.tm_sec = 0;
                startDate.tm_hour = 0;
                sscanf_s(startInput, "%d/%d/%4d", &startDate.tm_mday, &startDate.tm_mon, &startDate.tm_year);

                cout << "Enter End Date (dd/mm/yyyy/): ";
                cin >> endInput;
                endDate.tm_min = 0;
                endDate.tm_sec = 0;
                endDate.tm_hour = 0;
                sscanf_s(endInput, "%d/%d/%4d", &endDate.tm_mday, &endDate.tm_mon, &endDate.tm_year);

                bookingDictionary.printRange(startDate, endDate);
                break;
            }
            // Extra Features
            case 9:
            {
                // Group 12
                // Poh Jia Yong, S10202579J
                // Get Guest Booking function
                tm checkInDate;
                char checkInInput[] = "";
                string guestName, roomType;
                cout << "----------------Get Guest-------------------\n";
                cout << "Enter Guest Name: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, guestName);

                cout << "Enter Room Type: ";
                getline(cin, roomType);

                cout << "Enter Check In Date (dd/mm/yyyy/): ";
                cin >> checkInInput;
                sscanf_s(checkInInput, "%d/%d/%4d", &checkInDate.tm_mday, &checkInDate.tm_mon, &checkInDate.tm_year);

                Booking b = bookingDictionary.get(checkInDate, guestName, roomType);

                if (b.bookingGuestName != "Not Found")
                    cout << "\nBooking ID: " << b.bookingID << "\nGuest name : " << b.bookingGuestName <<  "\nBooking Status: " << b.bookingStatus << endl;
                else
                    cout << "\nBooking not found" << endl;
                break;
            }
            case 10: 
            {
                // Group 12
                // Chua Dong En, S10202623A
                // Poh Jia Yong, S10202579J
                // Change Current Date
                // Check if overdue, mark as cancel
                // Date changer
                // When date change, we need to cancel bookings that are overdue checkYstdOverdue()
                char currentInput[] = "";
                tm currentDate;
                cout << "----------------Change Current Date-------------------\n";
                cout << "Enter Date (dd/mm/yyyy/) to change to: ";
                cin >> currentInput;
                currentDate.tm_min = 0;
                currentDate.tm_sec = 0;
                currentDate.tm_hour = 0;
                sscanf_s(currentInput, "%d/%d/%4d", &currentDate.tm_mday, &currentDate.tm_mon, &currentDate.tm_year);
                currentDatetm = currentDate;
                bookingDictionary.checkOverdue(currentDatetm, roomScheduleMap);
                break;
            }
            case 0:
            {
                flag = false;
                cout << "Good bye";
                break;
            }
        }
    }
}

void menu() 
{
    cout << "----------------Main Menu-------------------\n";
    // Basic Features
    cout << "[1] Check in Guest\n";
    cout << "[2] Add Booking\n";
    cout << "[3] Display Guest staying in Hotel\n";
    cout << "[4] Display rooms occupied - by month\n";
    // Additional Features
    cout << "[5] Delete Booking\n";
    cout << "[6] Search most popular room type (From running dataset)\n";
    cout << "[7] Check in Guest without booking\n";
    cout << "[8] Display Bookings given range\n";
    // Extra Features
    cout << "[9] Get Guest Booking\n";
    cout << "[10] Change Current Date\n";
    cout << "[0] Exit\n";
    cout << "----------------------------------------------\n";
}

void addToCsv(Booking b)
{
    // Group 12
        // Poh Jia Yong, S10202579J
    fstream fout;

    fout.open("Bookings.csv", ios::app);
    ostringstream oss;
    b.bookingDate.tm_year -= 1900;
    b.bookingDate.tm_mon -= 1;
    oss << put_time(&b.bookingDate, "%d-%m-%Y %H-%M-%S");
    string bookdate = oss.str();

    oss.str("");
    oss.clear();
    b.checkinDate.tm_year -= 1900;
    b.checkinDate.tm_mon -= 1;
    oss << put_time(&b.checkinDate, "%d-%m-%Y");
    string checkin = oss.str();

    oss.str("");
    oss.clear();
    b.checkOutDate.tm_year -= 1900;
    b.checkOutDate.tm_mon -= 1;
    oss << put_time(&b.checkOutDate, "%d-%m-%Y");
    string checkout = oss.str();
    string csvBookObj;

    csvBookObj = "\n" + to_string(b.bookingID) + "," + bookdate + "," + b.bookingGuestName + "," + b.bookingRoomNumber + ","
        + b.bookingRoomType + "," + b.bookingStatus + "," + checkin + "," + checkout + "," + to_string(b.bookingGuestNumber)
        + "," + b.bookingSpecialRequest;

    fout << csvBookObj;
}