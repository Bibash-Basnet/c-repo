#include <iostream>
#include <string>
#include <ctime>
#include <fstream>

class Library {
private:
    struct Book {
        int id;
        std::string title;
        std::string author;
        int year;
        bool isBorrowed;
    };

    struct Member {
        std::string id;
        std::string name;
        std::string contact;
    };

    struct Transaction {
        std::string memberID;
        int bookID;
        std::string bookTitle;
        std::string dateBorrowed;
        std::string dateReturned;

        void displayTransaction() const {
            std::cout << "Book ID: " << bookID 
                      << ", Title: " << bookTitle 
                      << ", Date Borrowed: " << dateBorrowed 
                      << ", Date Returned: ";
            
            if (dateReturned.empty()) {
                std::cout << "Not returned yet" << std::endl;
            } else {
                std::cout << dateReturned << std::endl;
            }
        }
    };

    static const int MAX_BOOKS = 100;
    static const int MAX_MEMBERS = 100;
    static const int MAX_TRANSACTIONS = 100;

    Book books[MAX_BOOKS];
    Member members[MAX_MEMBERS];
    Transaction transactions[MAX_TRANSACTIONS];
    int bookCount = 0;
    int memberCount = 0;
    int transactionCount = 0;

    std::string getCurrentDate() const {
        time_t now = time(0);
        tm *ltm = localtime(&now);
        return std::to_string(ltm->tm_mday) + "/" + std::to_string(1 + ltm->tm_mon) + "/" + std::to_string(1900 + ltm->tm_year);
    }

    void saveData() const {
        std::ofstream bookFile("books.txt");
        for (int i = 0; i < bookCount; ++i) {
            bookFile << books[i].id << "|" << books[i].title << "|" 
                     << books[i].author << "|" << books[i].year << "|" 
                     << books[i].isBorrowed << std::endl;
        }
        bookFile.close();

        std::ofstream memberFile("members.txt");
        for (int i = 0; i < memberCount; ++i) {
            memberFile << members[i].id << "|" << members[i].name << "|" 
                       << members[i].contact << std::endl;
        }
        memberFile.close();

        std::ofstream transactionFile("transactions.txt");
        for (int i = 0; i < transactionCount; ++i) {
            transactionFile << transactions[i].memberID << "|" << transactions[i].bookID << "|"
                            << transactions[i].bookTitle << "|" << transactions[i].dateBorrowed << "|"
                            << transactions[i].dateReturned << std::endl;
        }
        transactionFile.close();
    }

    void loadData() {
        std::ifstream bookFile("books.txt");
        if (bookFile) {
            std::string line;
            while (getline(bookFile, line) && bookCount < MAX_BOOKS) {
                Book book;
                size_t pos = 0;
                std::string token;
                
                // Parse bookID
                pos = line.find('|');
                token = line.substr(0, pos);
                book.id = std::stoi(token);
                line.erase(0, pos + 1);
                
                // Parse title
                pos = line.find('|');
                book.title = line.substr(0, pos);
                line.erase(0, pos + 1);
                
                // Parse author
                pos = line.find('|');
                book.author = line.substr(0, pos);
                line.erase(0, pos + 1);
                
                // Parse year
                pos = line.find('|');
                token = line.substr(0, pos);
                book.year = std::stoi(token);
                line.erase(0, pos + 1);
                
                // Parse isBorrowed
                token = line;
                book.isBorrowed = (token == "1");

                books[bookCount++] = book;
            }
            bookFile.close();
        }

        std::ifstream memberFile("members.txt");
        if (memberFile) {
            std::string line;
            while (getline(memberFile, line) && memberCount < MAX_MEMBERS) {
                Member member;
                size_t pos = 0;
                
                // Parse memberID
                pos = line.find('|');
                member.id = line.substr(0, pos);
                line.erase(0, pos + 1);
                
                // Parse name
                pos = line.find('|');
                member.name = line.substr(0, pos);
                line.erase(0, pos + 1);
                
                // Parse contact
                member.contact = line;
                
                members[memberCount++] = member;
            }
            memberFile.close();
        }

        std::ifstream transactionFile("transactions.txt");
        if (transactionFile) {
            std::string line;
            while (getline(transactionFile, line) && transactionCount < MAX_TRANSACTIONS) {
                Transaction transaction;
                size_t pos = 0;
                std::string token;
                
                // Parse memberID
                pos = line.find('|');
                transaction.memberID = line.substr(0, pos);
                line.erase(0, pos + 1);
                
                // Parse bookID
                pos = line.find('|');
                token = line.substr(0, pos);
                transaction.bookID = std::stoi(token);
                line.erase(0, pos + 1);
                
                // Parse bookTitle
                pos = line.find('|');
                transaction.bookTitle = line.substr(0, pos);
                line.erase(0, pos + 1);
                
                // Parse dateBorrowed
                pos = line.find('|');
                transaction.dateBorrowed = line.substr(0, pos);
                line.erase(0, pos + 1);
                
                // Parse dateReturned
                transaction.dateReturned = line;
                
                transactions[transactionCount++] = transaction;
            }
            transactionFile.close();
        }
    }

    bool isMemberExist(const std::string& memberId) const {
        for (int i = 0; i < memberCount; i++) {
            if (members[i].id == memberId) {
                return true;
            }
        }
        return false;
    }

    int findBook(int bookId) const {
        for (int i = 0; i < bookCount; i++) {
            if (books[i].id == bookId) {
                return i;
            }
        }
        return -1; // Book not found
    }

    int findMember(const std::string& memberId) const {
        for (int i = 0; i < memberCount; i++) {
            if (members[i].id == memberId) {
                return i;
            }
        }
        return -1; // Member not found
    }

public:
    void addBook() {
        if (bookCount >= MAX_BOOKS) {
            std::cout << "Cannot add more books. Maximum capacity reached." << std::endl;
            return;
        }

        int id, year;
        std::string title, author;
        std::cout << "Enter Book ID: ";
        std::cin >> id;

        if (findBook(id) != -1) {
            std::cout << "Book ID already exists. Please enter a unique ID." << std::endl;
            return;
        }

        std::cout << "Enter Book Title: ";
        std::cin.ignore();
        std::getline(std::cin, title);
        std::cout << "Enter Author: ";
        std::getline(std::cin, author);
        std::cout << "Enter Publication Year: ";
        std::cin >> year;

        books[bookCount] = {id, title, author, year, false};
        ++bookCount;
        std::cout << "Book added successfully!" << std::endl;
        saveData();
    }

    void addMember() {
        if (memberCount >= MAX_MEMBERS) {
            std::cout << "Cannot add more members. Maximum capacity reached." << std::endl;
            return;
        }

        std::string id, name, contact;
        std::cout << "Enter Member ID: ";
        std::cin >> id;

        if (isMemberExist(id)) {
            std::cout << "Member ID already exists. Please enter a unique ID." << std::endl;
            return;
        }

        std::cout << "Enter Name: ";
        std::cin.ignore();
        std::getline(std::cin, name);
        std::cout << "Enter Contact Information: ";
        std::getline(std::cin, contact);

        members[memberCount] = {id, name, contact};
        ++memberCount;
        std::cout << "Member added successfully!" << std::endl;
        saveData();
    }

    void borrowBook() {
        std::string memberId;
        int bookId;
        std::cout << "Enter Member ID: ";
        std::cin >> memberId;

        if (!isMemberExist(memberId)) {
            std::cout << "No member with this ID: " << memberId << std::endl;
            return;
        }

        std::cout << "Enter Book ID to borrow: ";
        std::cin >> bookId;

        int bookIndex = findBook(bookId);
        if (bookIndex == -1) {
            std::cout << "Book not found." << std::endl;
            return;
        }

        if (books[bookIndex].isBorrowed) {
            std::cout << "Book is already borrowed." << std::endl;
            return;
        }

        books[bookIndex].isBorrowed = true;
        transactions[transactionCount++] = {memberId, bookId, books[bookIndex].title, getCurrentDate(), ""};
        
        std::cout << "Book '" << books[bookIndex].title << "' borrowed successfully!" << std::endl;
        std::cout << "Book ID: " << bookId << ", Member ID: " << memberId << ", Date Borrowed: " << getCurrentDate() << std::endl; // Debug statement
        
        saveData();
    }

    void returnBook() {
        std::string memberId;
        int bookId;
        std::cout << "Enter Member ID: ";
        std::cin >> memberId;

        if (!isMemberExist(memberId)) {
            std::cout << "No member with this ID: " << memberId << std::endl;
            return;
        }

        std::cout << "Enter Book ID to return: ";
        std::cin >> bookId;

        int bookIndex = findBook(bookId);
        if (bookIndex == -1) {
            std::cout << "Book not found." << std::endl;
            return;
        }

        if (!books[bookIndex].isBorrowed) {
            std::cout << "Book was not borrowed." << std::endl;
            return;
        }

        bool transactionFound = false;

        // Find the latest transaction where this book was borrowed by the member
        for (int i = transactionCount - 1; i >= 0; --i) {
            if (transactions[i].memberID == memberId && transactions[i].bookID == bookId) {
                if (transactions[i].dateReturned.empty()) {
                    transactions[i].dateReturned = getCurrentDate();
                    books[bookIndex].isBorrowed = false;
                    transactionFound = true;
                    std::cout << "Book '" << books[bookIndex].title << "' returned successfully on " << transactions[i].dateReturned << "!" << std::endl;
                } else {
                    std::cout << "Book was already returned on " << transactions[i].dateReturned << "." << std::endl;
                }
                break; // We found the matching transaction, no need to continue searching
            }
        }

        if (!transactionFound) {
            std::cout << "No borrowing record found for this book and member combination." << std::endl;
        }

        std::cout << "Book ID: " << bookId << ", Member ID: " << memberId << ", Date Returned: " << getCurrentDate() << std::endl; // Debug statement
        
        saveData();
    }

    void viewBorrowingHistory() const {
        std::string memberId;
        std::cout << "Enter Member ID to view borrowing history: ";
        std::cin >> memberId;

        if (!isMemberExist(memberId)) {
            std::cout << "No member with this ID: " << memberId << std::endl;
            return;
        }

        // Check if there is any borrowing history for the member
        bool hasHistory = false;
        std::cout << "Borrowing History for member ID: " << memberId << std::endl;
        for (int i = 0; i < transactionCount; i++) {
            if (transactions[i].memberID == memberId) {
                transactions[i].displayTransaction();
                hasHistory = true;
            }
        }

        if (!hasHistory) {
            std::cout << "No borrowing history found for member ID: " << memberId << std::endl;
        }
    }

    void menu() {
        loadData();
        int choice;
        do {
            std::cout << "\nLibrary Management System\n";
            std::cout << "1. Add Book\n";
            std::cout << "2. Add Member\n";
            std::cout << "3. Borrow Book\n";
            std::cout << "4. Return Book\n";
            std::cout << "5. View Borrowing History\n";
            std::cout << "6. Exit\n";
            std::cout << "Enter your choice: ";
            std::cin >> choice;

            switch (choice) {
                case 1: addBook(); break;
                case 2: addMember(); break;
                case 3: borrowBook(); break;
                case 4: returnBook(); break;
                case 5: viewBorrowingHistory(); break;
                case 6: std::cout << "Exiting...\n"; break;
                default: std::cout << "Invalid choice. Please try again." << std::endl;
            }
        } while (choice != 6);
    }
};

int main() {
    Library lib;
    lib.menu();
    return 0;
}
