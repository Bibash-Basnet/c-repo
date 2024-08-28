#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include <fstream>

using namespace std;

class Book {
public:
    int bookID;
    string title;
    string author;
    int year;
    bool isBorrowed;

    Book() : bookID(0), title(""), author(""), year(0), isBorrowed(false) {}
};

class Member {
public:
    string memberID;
    string name;
    string contact;

    Member() : memberID(""), name(""), contact("") {}
};

class Transaction {
public:
    string memberID;
    int bookID;
    string bookTitle;
    string dateBorrowed;
    string dateReturned;

    Transaction() : memberID(""), bookID(0), bookTitle(""), dateBorrowed(""), dateReturned("") {}

    void displayTransaction() const {
        cout << "Book ID: " << bookID
             << ", Title: " << bookTitle
             << ", Date Borrowed: " << dateBorrowed
             << ", Date Returned: ";

        if (dateReturned.empty()) {
            cout << "Not returned yet" << endl;
        } else {
            cout << dateReturned << endl;
        }
    }
};
