// Group 12
// Chua Dong En, S10202623A
// Poh Jia Yong, S10202579J

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "BookingDict.h"
//#include "RoomScheduleDictionary.h"
#include "Room.h"
#include "Booking.h"
#include <string.h>
#include <vector>
#include <chrono>


//#include "Dictionary.h"
using namespace std;

void menu();

BookingDict bookingDictionary;
RoomScheduleDictionary dynamicRoomNameDictionary(5,"testRoomType"); //(dynamic number of this)
//Delu
//Exec
//Presi
//Rooms roomArray[dynamic]
//
////include string linked list for dates
////linked list (roomType, count)
//
////array size 20 of [roomNumber,string concat dates]
//[roomDateDictionaries] > items/
//items > [Node, 1, 2, 3, 4]
//Node > take guest , date, store into array
//void printDate(tm Date);
//
////array size 20 of [roomNumber,string concat dates]
//[roomDateDictionaries] > items
//items > [Node, 1, 2, 3, 4]
//Node > take roomNo,date, store into array 
//void printMonth(/*month*/);


int main()
{
    //Date changer
    //When date change, we need to cancel bookings that are overdue checkYstdOverdue()
    
    //File I/O Bookings.csv
    fstream bookingsFile("Bookings.csv", ios::in);
    vector<vector<string>> content;
    vector<string> row;
    string line, word;

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
            bookingDictionary.add(b);
        }
    }


    // File I/O Rooms.csv
    Room* roomArray[20];
    fstream roomsFile("Rooms.csv", ios::in);
    vector<vector<string>> roomsContent;
    vector<string> roomsRow;
    string roomsLine, roomsWord;

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

    for (int i = 1; i < roomsContent.size(); i++)
    {
        // reads row by row in excel
        //room
        //ignore checkout
        //check if overdue, mark as cancel
        //load into main and room hashtable
        Room r;
        r.roomNumber = roomsContent[i][0];
        r.roomTypeName = roomsContent[i][1];
        r.roomTypeCost = stoi(roomsContent[i][2]);
        string roomNo = r.roomNumber.substr(5, 3);
        int index = stoi(roomNo);
        roomArray[index] = &r;
    }



    //Menu
    bool flag = true;
    while (flag)
    {
        menu();
        int option = 0;
        cout << "Pick an option: ";
        cin >> option;

        switch (option)
        {
            case 1: 
            {
                //check in guest function
                tm checkInDate;
                char checkInInput[] = "";
                string guestName, roomType;
               

                cout << "Enter Check In Date: ";
                cin >> checkInInput;
                sscanf_s(checkInInput, "%d/%d/%4d", &checkInDate.tm_mday, &checkInDate.tm_mon, &checkInDate.tm_year);


                cout << "Enter Guest Name: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, guestName);


                cout << "Enter Room Type: ";
                getline(cin, roomType);

                bool checkInStatus = bookingDictionary.checkIn(checkInDate, guestName, roomType);

                if (checkInStatus)
                    cout << "Checked In Sucessfully! \n";
                else
                    cout << guestName + " is already checked in \n";
                break;
            }
                
            case 2:
            {
                // add booking function
                tm bookingDate, checkInDate, checkOutDate;
                char checkInInput[] = "";
                char checkOutInput[] = "";
                string guestName, roomType, status, specialReq;
                int bookingID, numOfGuest;

                // bookingID is +1 of latest record in excel

                // bookingDate is datetime.now of program's current date

                cout << "Enter Guest Name: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, guestName);

                cout << "Enter Room Type: ";
                getline(cin, roomType);

                // status defaults to "Booked" upon completion of booking

                cout << "Enter Check In Date: ";
                cin >> checkInInput;
                sscanf_s(checkInInput, "%d/%d/%4d", &checkInDate.tm_mday, &checkInDate.tm_mon, &checkInDate.tm_year);

                cout << "Enter Check Out Date: ";
                cin >> checkInInput;
                sscanf_s(checkOutInput, "%d/%d/%4d", &checkOutDate.tm_mday, &checkOutDate.tm_mon, &checkOutDate.tm_year);

                cout << "Enter Number of Guest(s): ";
                cin >> numOfGuest;

                string yn;
                cout << "Any Special Request?\n y/n";
                cin >> yn;
                if (yn == "y")
                {
                    cout << "Enter Special Request: ";
                    getline(cin, specialReq);
                }

                //Booking b(bookingID, bookingDate, guestName, roomNum, roomType, status, checkInDate, checkOutDate, numOfGuest, specialReq);

                //bookingDictionary.add(b);

                break;
            }

            case 3:
            {
                // display guest staying in hotel function
                break;
            }

            case 4:
            {
                // display room occupied by month function
                break;
            }

            case 5:
            {
                // delete booking function
                break;
            }

            case 6:
            {
                // search most popular room type function
                break;
            }

            case 7:
            {
                // check in guest without booking function
                break;
            }

            case 8:
            {
                // display bookings given range function
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
    cout << "[6] Search most popular room type\n";
    cout << "[7] Check in Guest without booking\n";
    cout << "[8] Display bookings given range\n";
    cout << "[0] Exit\n";
    cout << "----------------------------------------------\n";
}



//// https://www.cplusplus.com/reference/ctime/tm/ for info about time structure (tm)
//tm result;
//char aString[] = "03/04/2020  06:09:02";
//sscanf_s(aString, "%d/%d/%4d  %d:%d:%d",
//    &result.tm_mday, &result.tm_mon, &result.tm_year, &result.tm_hour, &result.tm_min, &result.tm_sec);
//printf("tm_hour:  %d\n", result.tm_hour);
//printf("tm_min:  %d\n", result.tm_min);
//printf("tm_sec:  %d\n", result.tm_sec);
//printf("tm_mday:  %d\n", result.tm_mday);
//printf("tm_mon:  %d\n", result.tm_mon);
//printf("tm_year:  %d\n", result.tm_year);
//
//result.tm_year -= 1900;
//result.tm_mon -= 1;
//
//time_t time = mktime(&result);
//cout << time << '\n';