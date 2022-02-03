// DSA Assignment.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

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
    //fstream bookingsFile("Bookings.csv", ios::in);
    //vector<vector<string>> content;
    //vector<string> row;
    //string line, word;

    //if (bookingsFile.is_open())
    //{
    //    while (getline(bookingsFile, line))
    //    {
    //        row.clear();

    //        stringstream str(line);

    //        while (getline(str, word, ','))
    //            row.push_back(word);
    //        content.push_back(row);
    //    }
    //}

    //for (int i = 1; i < content.size(); i++)
    //{
    //    Booking b;
    //    tm date;
    //    b.bookingID = stoi(content[i][0]); // stoi converts string to int
    //    sscanf_s(content[i][1].c_str(), "%d/%d/%4d  %d:%d:%d", &date.tm_mday, &date.tm_mon, &date.tm_year, &date.tm_hour, &date.tm_min, &date.tm_sec);
    //    b.bookingDate = date;
    //    b.bookingGuestName = content[i][2];
    //    b.bookingRoomNumber = content[i][3];
    //    b.bookingRoomType = content[i][4];
    //    b.bookingStatus = content[i][5];
    //    sscanf_s(content[i][6].c_str(), "%d/%d/%4d  %d:%d:%d", &date.tm_mday, &date.tm_mon, &date.tm_year, &date.tm_hour, &date.tm_min, &date.tm_sec);
    //    b.checkinDate = date;
    //    sscanf_s(content[i][7].c_str(), "%d/%d/%4d  %d:%d:%d", &date.tm_mday, &date.tm_mon, &date.tm_year, &date.tm_hour, &date.tm_min, &date.tm_sec);
    //    b.checkOutDate = date;
    //    b.bookingGuestNumber = stoi(content[i][8]);
    //    b.bookingSpecialRequest = content[i][9];

    //    // list.add(b)
    //    bookingDictionary.add(b);
    //    cout << "\n";
    //}

    // File I/O Rooms.csv
    Room* roomArray[20];
    fstream roomsFile("Rooms.csv", ios::in);
    vector<vector<string>> roomsContent;
    vector<string> roomsRow;
    string line, word;

    if (roomsFile.is_open())
    {
        while (getline(roomsFile, line))
        {
            roomsRow.clear();

            stringstream str(line);

            while (getline(str, word, ','))
                roomsRow.push_back(word);
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
        //dynamicRoomNameDictionary.add(r);
        cout << r.roomNumber << "\n";
    }



    //Menu
    int option;
    menu();
    cin >> option;
    //if (option == 1)
    //    //check in guest function
    //else if (option == 2)
    //    // add booking function
    //else if (option == 3)
    //    // display guest staying in hotel function
    //else if (option == 4)
    //    // display room occupied by month function
    //else if (option == 5)
    //    // delete booking function
    //else if (option == 6)
    //    // search most popular room type function
    //else if (option == 7)
    //    // check in guest without booking function
    //else if (option == 8)
    //    // display bookings given range function
    //else if (option == 0)
    //    return 0;
}

void menu() 
{
    cout << endl;
    // Basic Features
    cout << "Data Structure and Algorithm Assignment \n";
    cout << "--------------------------------\n";
    cout << "1. Check in Guest       \n";
    cout << "2. Add Booking          \n";
    cout << "3. Display Guest staying in Hotel \n";
    cout << "4. Display rooms occupied - by month \n";
    // Additional Features
    cout << "5. Delete Booking       \n";
    cout << "6. Search most popular room type \n";
    cout << "7. Check in Guest without booking  \n";
    cout << "8. Display bookings given range \n";
    cout << "0 Exit                             \n";
    cout << "--------------------------------\n";
    cout << "Enter option : ";
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