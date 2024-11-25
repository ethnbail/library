#include <limits>
#include "libraryFunctions.h"
#include "MergeSort.h"
#include "searchFunction.h"
#include "UserAccount.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// function to load list of available books
vector<Book> loadAvailableBooks() {
    ifstream file("booksavailable.txt");
    vector<Book> books; // vector to store books
    string line;

// loops through each line 
    while (getline(file, line)) {
        istringstream iss(line);
        string title, author, serialNumber, genre, subgenre;
        int publicationYear;

// reads each component of the book
        getline(iss, title, ',');
        getline(iss, author, ',');
        getline(iss, serialNumber, ',');  // Read serial number as string
        iss >> publicationYear;
        iss.ignore(); // Ignore the comma after the year
        getline(iss, genre, ',');
        getline(iss, subgenre);

        books.emplace_back(title, author, serialNumber, publicationYear, genre, subgenre);  // Pass serialNumber as string
    }
    file.close();// close after reading
    return books;
}

// function to handle checking out a book
void checkoutBook(const string& username, const string& serialNumber) {
    vector<Book> books = loadAvailableBooks();
    Book selectedBook;
    bool found = false;

    // Find and remove the book from available books
    for (auto it = books.begin(); it != books.end(); ++it) {
        if (it->serialNumber == serialNumber) {  // Compare serial numbers as string
            selectedBook = *it;
            books.erase(it);
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Book not found in available books." << endl;
        return;
    }

    // Update booksAvailable.txt
    ofstream availableOut("booksavailable.txt", ios::trunc);
    if (!availableOut) {
        cout << "Error opening booksavailable.txt for writing." << endl;
        return;
    }

    for (const auto& book : books) {
        availableOut << book.title << "," << book.author << "," << book.serialNumber
                     << "," << book.publicationYear << "," << book.genre << "," << book.subgenre << endl;
    }
    availableOut.close();

    // Add book to booksCheckedOut.txt
    ofstream checkedOutOut("booksCheckedOut.txt", ios::app);
    if (!checkedOutOut) {
        //error handling
        cout << "Error opening booksCheckedOut.txt for appending." << endl;
        return;
    }

    cout << "Writing to file: " << username << "," << selectedBook.title << "," << selectedBook.serialNumber << endl;

    checkedOutOut << username << "," << selectedBook.title << "," << selectedBook.serialNumber << endl;
    checkedOutOut.close();

    cout << "Book checked out successfully." << endl;
}

void returnBook(const string& username) {
    ifstream file("users.txt");
    ofstream availableBooksOut("booksavailable.txt", ios::app);  // Open this in append mode
    string line;

    bool userFound = false;
    vector<Book> checkedOutBooks;

// goes through the user file to find the username
    while (getline(file, line)) {
        if (line.find(username) != string::npos) {
            userFound = true;
            istringstream iss(line);
            string segment;
            vector<string> segments;
            while (getline(iss, segment, ',')) {
                segments.push_back(segment); // splits user data with commas
            }

            // Extract the checked-out books
            for (size_t i = 2; i < segments.size(); i += 2) {
                Book book;
                book.title = segments[i];
                book.serialNumber = segments[i + 1];  // Treat ISBN as string
                checkedOutBooks.push_back(book);
            }
            break;
        }
    }
    file.close();

    if (!userFound) {
        cout << "User not found." << endl;
        return;
    }

// display the books currently checked out by user
    cout << "Books checked out by " << username << ":" << endl;
    for (size_t i = 0; i < checkedOutBooks.size(); ++i) {
        cout << i + 1 << ". \"" << checkedOutBooks[i].title << "\" - Serial Number: " << checkedOutBooks[i].serialNumber << endl;
    }

    cout << "Enter the number of the book to return: ";
    int choice;
    cin >> choice;

    if (choice > 0 && choice <= checkedOutBooks.size()) {
        Book bookToReturn = checkedOutBooks[choice - 1];

        // Find the corresponding book in the available books list and write all details back
        vector<Book> availableBooks = loadAvailableBooks();  // Load books from available list
        ofstream availableBooksOut("booksavailable.txt", ios::trunc);  // Write to the available books file
        
        for (const Book& book : availableBooks) {
            if (book.serialNumber == bookToReturn.serialNumber) {
                availableBooksOut << "\"" << book.title << "\","
                                  << "\"" << book.author << "\","
                                  << book.serialNumber << ","
                                  << book.publicationYear << ","
                                  << "\"" << book.genre << "\","
                                  << "\"" << book.subgenre << "\"\n";  // Write details to file
                cout << "Book returned successfully." << endl;
            }
            else {
                availableBooksOut << "\"" << book.title << "\","
                                  << "\"" << book.author << "\","
                                  << book.serialNumber << ","
                                  << book.publicationYear << ","
                                  << "\"" << book.genre << "\","
                                  << "\"" << book.subgenre << "\"\n";
            }
        }
    } else {
        cout << "Invalid selection." << endl;
    }

    availableBooksOut.close();
}

void displayBooksBySubgenre(const vector<Book>& availableBooks, const string& subgenre, const string& username) {
    vector<Book> booksInSubgenre;

    // Filter books by subgenre
    for (const Book& book : availableBooks) {
        if (book.subgenre == subgenre) {
            booksInSubgenre.push_back(book);
        }
    }

    // Display available books
    if (booksInSubgenre.empty()) {
        cout << "No books found in this subgenre." << endl;
    } else {
mergeSort(booksInSubgenre, 0, booksInSubgenre.size() - 1);

        cout << "Books available in " << subgenre << ":" << endl;
        for (size_t i = 0; i < booksInSubgenre.size(); ++i) {
            cout << i + 1 << ". " << booksInSubgenre[i].title << " by " << booksInSubgenre[i].author << endl;
        }

        // Ask user to select a book
        cout << "Enter the number of the book you want to checkout: ";
        int bookChoice;
        cin >> bookChoice;

        // Handle invalid input
        if (cin.fail()) {
            cin.clear(); // Clear input buffer to restore cin to a usable state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore bad input
            cout << "Invalid input. Please enter a valid number." << endl;
            return;
        }

        // Check for valid book selection
        if (bookChoice > 0 && bookChoice <= booksInSubgenre.size()) {
            checkoutBook(username, booksInSubgenre[bookChoice - 1].serialNumber);  // Use serialNumber from the selected book
        } else {
            cout << "Invalid choice. Please select a number between 1 and " << booksInSubgenre.size() << "." << endl;
        }
    }
}
