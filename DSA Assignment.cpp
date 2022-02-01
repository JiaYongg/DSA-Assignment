// DSA Assignment.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include "Dictionary.h"
#include "RoomDateDictionary.h"
#include "Rooms.h"

//#include "Dictionary.h"
using namespace std;

void menu();

Dictionary bookingDictionary;
RoomDateDictionary dynamicRoomNameDictionary; (dynamic number of this)
Delu
Exec
Presi
Rooms roomArray[dynamic]

//include string linked list for dates
//linked list (roomType, count)

//array size 20 of [roomNumber,string concat dates]
[roomDateDictionaries] > items
items > [Node, 1, 2, 3, 4]
Node > take guest , date, store into array
void printDate(tm Date);

//array size 20 of [roomNumber,string concat dates]
[roomDateDictionaries] > items
items > [Node, 1, 2, 3, 4]
Node > take roomNo,date, store into array 
void printMonth(/*month*/);


int main()
{
    //Date changer
    //When date change, we need to cancel bookings that are overdue checkYstdOverdue()
    
    //File I/O
    ifstream myFile;
    myFile.open("Bookings.csv");
    string str;
    getline(myFile, str);
    while (myFile.good())
    {
        string line;
        getline(myFile, line, ',');
        cout << line << endl; // reads row by row in excel
        //room
        //ignore checkout
        //check if overdue, mark as cancel
        //load into main and room hashtable
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
