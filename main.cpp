#include "./library.h" 

int main() {
    Library library;
    int choice;

    do {
        cout << "\n-------------------------------------\n";
        cout << "|      Library Management System    |\n";
        cout << "|-----------------------------------|\n";
        cout << "| Option |       Description        |\n";
        cout << "|--------|--------------------------|\n";
        cout << "|   1    | Add Book                 |\n";
        cout << "|   2    | Add Member               |\n";
        cout << "|   3    | Borrow Book              |\n";
        cout << "|   4    | Return Book              |\n";
        cout << "|   5    | View Borrowing History   |\n";
        cout << "|   6    | View All Books           |\n";
        cout << "|   7    | View All Members         |\n";
        cout << "|   0    | Exit                     |\n";
        cout << "|________|__________________________|\n";
        cout << "Enter your choice: ";
        cin >> choice;


        switch (choice) {
            case 1:
                library.addBook();
                break;
            case 2:
                library.addMember();
                break;
            case 3:
                library.borrowBook();
                break;
            case 4:
                library.returnBook();
                break;
            case 5:
                library.viewBorrowingHistory();
                break;
            case 6:
                library.viewAllBooks();
                break;
            case 7:
                library.viewAllMembers();
                break;
            case 0:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);

    return 0;
}
