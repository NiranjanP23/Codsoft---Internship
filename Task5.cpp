#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <sstream>
#include <unordered_map>

using namespace std;

struct Book {
    string title;
    string author;
    string ISBN;
    bool isAvailable = true;
};

struct Borrower {
    string name;
    string borrowerID;
};

struct Transaction {
    string ISBN;
    string borrowerID;
    time_t checkoutDate;
    time_t returnDate;
    bool isReturned = false;
};

const int FINE_PER_DAY = 10;  


vector<Book> books;
vector<Borrower> borrowers;
vector<Transaction> transactions;


string timeToString(time_t time) {
    char buffer[80];
    struct tm* timeInfo;
    timeInfo = localtime(&time);
    strftime(buffer, 80, "%d-%m-%Y", timeInfo);
    return string(buffer);
}


void addBook(const Book& book) {
    books.push_back(book);
    cout << "Book added successfully!" << endl;
}


void searchBook(const string& searchTerm) {
    bool found = false;
    for (const auto& book : books) {
        if (book.title.find(searchTerm) != string::npos || 
            book.author.find(searchTerm) != string::npos || 
            book.ISBN.find(searchTerm) != string::npos) {
            cout << "Found: " << book.title << " by " << book.author 
                 << " (ISBN: " << book.ISBN << ") - " 
                 << (book.isAvailable ? "Available" : "Checked out") << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "No books found with the search term: " << searchTerm << endl;
    }
}

/
void checkoutBook(const string& ISBN, const string& borrowerID) {
    bool found = false;
    for (auto& book : books) {
        if (book.ISBN == ISBN && book.isAvailable) {
            book.isAvailable = false;
            found = true;
            Transaction transaction = { ISBN, borrowerID, time(0), 0, false };
            transactions.push_back(transaction);
            cout << "Book checked out successfully." << endl;
            break;
        }
    }
    if (!found) {
        cout << "Book not available for checkout." << endl;
    }
}


void returnBook(const string& ISBN, const string& borrowerID) {
    bool found = false;
    for (auto& book : books) {
        if (book.ISBN == ISBN && !book.isAvailable) {
            book.isAvailable = true;
            found = true;
            cout << "Book returned successfully." << endl;

            
            for (auto& transaction : transactions) {
                if (transaction.ISBN == ISBN && transaction.borrowerID == borrowerID && !transaction.isReturned) {
                    transaction.isReturned = true;
                    transaction.returnDate = time(0);
                    break;
                }
            }
            break;
        }
    }
    if (!found) {
        cout << "Book return failed. Check if the ISBN and borrower ID are correct." << endl;
    }
}


void calculateFine(const string& borrowerID) {
    time_t currentTime = time(0);
    bool found = false;

    for (const auto& transaction : transactions) {
        if (transaction.borrowerID == borrowerID && !transaction.isReturned) {  
            double daysDiff = difftime(currentTime, transaction.checkoutDate) / (60 * 60 * 24);
            if (daysDiff > 14) {  
                int fine = static_cast<int>((daysDiff - 14) * FINE_PER_DAY);
                cout << "Overdue book (ISBN: " << transaction.ISBN << ") | Fine: $" << fine << endl;
                found = true;
            }
        }
    }

    if (!found) {
        cout << "No overdue books found for borrower ID: " << borrowerID << endl;
    }
}


void displayMenu() {
    cout << "Library Management System" << endl;
    cout << "1. Add Book" << endl;
    cout << "2. Search Book" << endl;
    cout << "3. Checkout Book" << endl;
    cout << "4. Return Book" << endl;
    cout << "5. Calculate Fine" << endl;
    cout << "6. Exit" << endl;
}

int main() {
    int choice;
    string title, author, ISBN, borrowerID;

    while (true) {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter book title: ";
                cin.ignore();
                getline(cin, title);
                cout << "Enter book author: ";
                getline(cin, author);
                cout << "Enter book ISBN: ";
                getline(cin, ISBN);
                addBook({title, author, ISBN, true});
                break;

            case 2:
                cout << "Enter title, author, or ISBN to search: ";
                cin.ignore();
                getline(cin, ISBN);
                searchBook(ISBN);
                break;

            case 3:
                cout << "Enter book ISBN: ";
                cin.ignore();
                getline(cin, ISBN);
                cout << "Enter borrower ID: ";
                getline(cin, borrowerID);
                checkoutBook(ISBN, borrowerID);
                break;

            case 4:
                cout << "Enter book ISBN: ";
                cin.ignore();
                getline(cin, ISBN);
                cout << "Enter borrower ID: ";
                getline(cin, borrowerID);
                returnBook(ISBN, borrowerID);
                break;

            case 5:
                cout << "Enter borrower ID: ";
                cin.ignore();
                getline(cin, borrowerID);
                calculateFine(borrowerID);
                break;

            case 6:
                cout << "Exiting the program." << endl;
                return 0;

            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }
}
