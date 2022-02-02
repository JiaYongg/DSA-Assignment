// DSA Assignment.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
//#include "BookingDict.h"
//#include "RoomScheduleDictionary.h"
#include "Room.h"
#include "Booking.h"
#include <string.h>
#include <vector>
#include <chrono>
#include <sstream>

//#include "Dictionary.h"
using namespace std;

void menu();

//Dictionary bookingDictionary;
//RoomDateDictionary dynamicRoomNameDictionary; //(dynamic number of this)
//Delu
//Exec
//Presi
//Rooms roomArray[dynamic]
//
////include string linked list for dates
////linked list (roomType, count)
//
////array size 20 of [roomNumber,string concat dates]
//[roomDateDictionaries] > items
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
    //    Bookings b;
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
        Rooms r;
        r.roomNumber = roomsContent[i][0];
        r.roomTypeName = roomsContent[i][1];
        r.roomTypeCost = stoi(roomsContent[i][2]);


        dynamicRoomNameDictionary.add(r);
        cout << "\n";
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
