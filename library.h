#include "./classing.cpp"
#include <iostream>
#include <string>
#include <ctime>
#include <fstream>

using namespace std;

const int MAX_BOOKS = 3000;
const int MAX_MEMBERS = 1000;
const int MAX_TRANSACTIONS = 1000;

class Library {

private:
    Book books[MAX_BOOKS];
    Member members[MAX_MEMBERS];
    Transaction transactions[MAX_TRANSACTIONS];
    int bookCount;
    int memberCount;
    int transactionCount;

    string getCurrentDate() {
        time_t now = time(0);
        tm *ltm = localtime(&now);
        return to_string(ltm->tm_mday) + "/" + to_string(1 + ltm->tm_mon) + "/" + to_string(1900 + ltm->tm_year);
    }

    void saveData() {
        ofstream bookFile("books.txt");
        for (int i = 0; i < bookCount; ++i) {
            bookFile << books[i].bookID << "|" << books[i].title << "|"
                     << books[i].author << "|" << books[i].year << "|"
                     << books[i].isBorrowed << endl;
        }
        bookFile.close();

        ofstream memberFile("members.txt");
        for (int i = 0; i < memberCount; ++i) {
            memberFile << members[i].memberID << "|" << members[i].name << "|"
                       << members[i].contact << endl;
        }
        memberFile.close();

        ofstream transactionFile("transactions.txt");
        for (int i = 0; i < transactionCount; ++i) {
            transactionFile << transactions[i].memberID << "|" << transactions[i].bookID << "|"
                            << transactions[i].bookTitle << "|" << transactions[i].dateBorrowed << "|"
                            << transactions[i].dateReturned << endl;
        }
        transactionFile.close();
    }

    void loadData() {
        ifstream bookFile("books.txt");
        if (bookFile) {
            string line;
            while (getline(bookFile, line) && bookCount < MAX_BOOKS) {
                Book book;
                size_t pos = 0;
                string token;

                pos = line.find('|');
                token = line.substr(0, pos);
                book.bookID = stoi(token);
                line.erase(0, pos + 1);

                pos = line.find('|');
                book.title = line.substr(0, pos);
                line.erase(0, pos + 1);

                pos = line.find('|');
                book.author = line.substr(0, pos);
                line.erase(0, pos + 1);

                pos = line.find('|');
                token = line.substr(0, pos);
                book.year = stoi(token);
                line.erase(0, pos + 1);

                token = line;
                book.isBorrowed = (token == "1");

                books[bookCount++] = book;
            }
            bookFile.close();
        }

        ifstream memberFile("members.txt");
        if (memberFile) {
            string line;
            while (getline(memberFile, line) && memberCount < MAX_MEMBERS) {
                Member member;
                size_t pos = 0;

                pos = line.find('|');
                member.memberID = line.substr(0, pos);
                line.erase(0, pos + 1);

                pos = line.find('|');
                member.name = line.substr(0, pos);
                line.erase(0, pos + 1);

                member.contact = line;

                members[memberCount++] = member;
            }
            memberFile.close();
        }

        ifstream transactionFile("transactions.txt");
        if (transactionFile) {
            string line;
            while (getline(transactionFile, line) && transactionCount < MAX_TRANSACTIONS) {
                Transaction transaction;
                size_t pos = 0;
                string token;

                pos = line.find('|');
                transaction.memberID = line.substr(0, pos);
                line.erase(0, pos + 1);

                pos = line.find('|');
                token = line.substr(0, pos);
                transaction.bookID = stoi(token);
                line.erase(0, pos + 1);

                pos = line.find('|');
                transaction.bookTitle = line.substr(0, pos);
                line.erase(0, pos + 1);

                pos = line.find('|');
                transaction.dateBorrowed = line.substr(0, pos);
                line.erase(0, pos + 1);

                transaction.dateReturned = line;

                transactions[transactionCount++] = transaction;
            }
            transactionFile.close();
        }
    }

    bool isBookIDUnique(int bookId) {
        for (int i = 0; i < bookCount; i++) {
            if (books[i].bookID == bookId) {
                return false;
            }
        }
        return true;
    }

    bool isMemberIDUnique(const string &memberId) {
        for (int i = 0; i < memberCount; i++) {
            if (members[i].memberID == memberId) {
                return false;
            }
        }
        return true;
    }

    bool checkMemberExistence(const string &memberId) {
        for (int i = 0; i < memberCount; i++) {
            if (members[i].memberID == memberId) {
                return true;
            }
        }
        return false;
    }

    int findBook(int bookId) {
        for (int i = 0; i < bookCount; i++) {
            if (books[i].bookID == bookId) {
                return i;
            }
        }
        return -1;
    }

    int findMember(string memberId) {
        for (int i = 0; i < memberCount; i++) {
            if (members[i].memberID == memberId) {
                return i;
            }
        }
        return -1;
    }

public:
    Library() : bookCount(0), memberCount(0), transactionCount(0) {
        loadData();
    }

    void addBook() {
        if (bookCount >= MAX_BOOKS) {
            cout << "Cannot add more books. Maximum capacity reached." << endl;
            return;
        }

        int id, year;
        string title, author;
        cout << "Enter Book ID: ";
        cin >> id;

        if (!isBookIDUnique(id)) {
            cout << "Book ID already exists. Please enter a unique ID." << endl;
            return;
        }

        cout << "Enter Book Title: ";
        cin.ignore();
        getline(cin, title);
        cout << "Enter Author: ";
        getline(cin, author);
        cout << "Enter Publication Year: ";
        cin >> year;

       books[bookCount].bookID = id;
       books[bookCount].title = title;
       books[bookCount].author = author;
       books[bookCount].year = year;               
       books[bookCount].isBorrowed = false;        
       bookCount++;                                
        cout << "Book added successfully!" << endl;
        saveData();
    }

    void addMember() {
        if (memberCount >= MAX_MEMBERS) {
            cout << "Cannot add more members. Maximum capacity reached." << endl;
            return;
        }

        string id, name, contact;
        cout << "Enter Member ID: ";
        cin >> id;

        if (!isMemberIDUnique(id)) {
            cout << "Member ID already exists. Please enter a unique ID." << endl;
            return;
        }

        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Contact Information: ";
        getline(cin, contact);

       members[memberCount].memberID = id;
       members[memberCount].name = name;
       members[memberCount].contact = contact;
       memberCount++;                              

        cout << "Member added successfully!" << endl;
        saveData();
    }

    void borrowBook() {
        string memberId;
        int bookId;
        cout << "Enter Member ID: ";
        cin >> memberId;

        if (!checkMemberExistence(memberId)) {
            cout << "Member not found. Please register the member first." << endl;
            return;
        }

        cout << "Enter Book ID to borrow: ";
        cin >> bookId;

        int bookIndex = findBook(bookId);
        if (bookIndex == -1) {
            cout << "Book not found." << endl;
            return;
        }

        if (books[bookIndex].isBorrowed) {
            cout << "Book is already borrowed." << endl;
            return;
        }


                books[bookIndex].isBorrowed = true;
        string dateBorrowed = getCurrentDate();

       transactions[transactionCount].memberID = memberId;
       transactions[transactionCount].bookID = bookId;
       transactions[transactionCount].bookTitle = books[bookIndex].title;
       transactions[transactionCount].dateBorrowed = dateBorrowed;
       transactions[transactionCount].dateReturned = "";
       transactionCount++;                                                

        cout << "Book borrowed successfully!" << endl;
        saveData();
    }

    void returnBook() {
        string memberId;
        int bookId;
        cout << "Enter Member ID: ";
        cin >> memberId;

        cout << "Enter Book ID to return: ";
        cin >> bookId;

        int bookIndex = findBook(bookId);
        if (bookIndex == -1) {
            cout << "Book not found." << endl;
            return;
        }

        if (!books[bookIndex].isBorrowed) {
            cout << "This book was not borrowed." << endl;
            return;
        }

        for (int i = 0; i < transactionCount; i++) {
            if (transactions[i].bookID == bookId && transactions[i].memberID == memberId && transactions[i].dateReturned.empty()) {
                books[bookIndex].isBorrowed = false;
                transactions[i].dateReturned = getCurrentDate();
                cout << "Book returned successfully!" << endl;
                saveData();
                return;
            }
        }

        cout << "No record found for this borrowing transaction." << endl;
    }

    void viewBorrowingHistory() {
        string memberId;
        cout << "Enter Member ID to view borrowing history: ";
        cin >> memberId;

        if (!checkMemberExistence(memberId)) {
            cout << "Member not found." << endl;
            return;
        }

        cout << "Borrowing History for Member ID: " << memberId << endl;
        for (int i = 0; i < transactionCount; i++) {
            if (transactions[i].memberID == memberId) {
                transactions[i].displayTransaction();
            }
        }
    }

    void viewAllBooks() {
        cout << "Book List:" << endl;
        for (int i = 0; i < bookCount; i++) {
            cout << "ID: " << books[i].bookID
                 << ", Title: " << books[i].title
                 << ", Author: " << books[i].author
                 << ", Year: " << books[i].year
                 << ", Borrowed: " << (books[i].isBorrowed ? "Yes" : "No") << endl;
        }
    }

    void viewAllMembers() {
        cout << "Member List:" << endl;
        for (int i = 0; i < memberCount; i++) {
            cout << "ID: " << members[i].memberID
                 << ", Name: " << members[i].name
                 << ", Contact: " << members[i].contact << endl;
        }
    }
};
