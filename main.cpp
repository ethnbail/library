#include <iostream>
#include "UserAccount.h"
#include <ctime>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include "libraryFunctions.h"
#include "searchFunction.h"

using namespace std;

int main() {
    int choice;
    string response;
    string username;
    vector<Book> availableBooks = loadAvailableBooks();

    cout << "Welcome to Book Nest Library" << endl;
    cout << "1. Create Account" << endl;
    cout << "2. Sign In" << endl;
    cout << "Choose an option: ";
    cin >> choice;

    if (choice == 1) {
        createAccount();  // Initiates the create account function
    } else if (choice == 2) {
        if (signIn(username)) {
            cout << "Sign-in successful!" << endl;
        } else {
            cout << "Invalid username or password." << endl;
            return 0;
        }
    } else {
        cout << "Invalid option." << endl;
        return 0;
    }
    
    cout << "Would you like to checkout(1) or return(2) a book today? ";
    cin >> response;

    if (response == "1") {
        cout << "Search your book based on title(t) or look at available subgenres(g): ";
        char searchOption;
        cin >> searchOption;

        if (searchOption == 't') {
            // Search for a book by title
            string title;
            cout << "Enter the title of the book: ";
            cin.ignore();
            getline(cin, title);

            // Find the book by title
            auto it = find_if(availableBooks.begin(), availableBooks.end(), [&](const Book& book) {
                return book.title == title;
            });

            if (it != availableBooks.end()) {
                cout << "Book found: " << endl;
                cout << "Title: " << it->title << endl;
                cout << "Author: " << it->author << endl;
                cout << "Serial Number: " << it->serialNumber << endl;

                cout << "Would you like to check out this book? (yes/no): ";
                string confirm;
                cin >> confirm;

                if (confirm == "yes") {
                    // Check out the book and move it to booksCheckedOut.txt
                    checkoutBook(username, std::to_string(it->serialNumber));
                } else {
                    cout << "Checkout canceled." << endl;
                }
            } else {
                cout << "Book not found with the title \"" << title << "\"." << endl;
            }
        } else if (searchOption == 'g') {
            // Search for books by subgenre
            vector<string> subgenres = getSubgenres(availableBooks);
            displaySubgenres(availableBooks, subgenres);
            cout << "Enter the subgenre number you want to browse: ";
            int subgenreChoice;
            cin >> subgenreChoice;

            if (subgenreChoice > 0 && subgenreChoice <= subgenres.size()) {
                string chosenSubgenre = subgenres[subgenreChoice - 1];
                displayBooksBySubgenre(availableBooks, chosenSubgenre, username);
            } else {
                cout << "Invalid subgenre choice." << endl;
            }
        } else {
            cout << "Invalid search option. Please try again." << endl;
        }
    } else if (response == "2") {
        returnBook(username);
    } else {
        cout << "Invalid option. Try again." << endl;
    }

    return 0;
}
