#include "libraryFunctions.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// Constructor for the Book struct
Book::Book(string t, string a, string s, int p, string g)
    : title(t), author(a), serialNumber(s), publicationYear(p), genre(g) {}

// Default constructor for the Book struct
Book::Book() = default;

// Function to load available books from "booksavailable.txt"
vector<Book> loadAvailableBooks() {
    ifstream file("booksavailable.txt");
    vector<Book> books;
    string line;

    while (getline(file, line)) {
        istringstream iss(line);
        string title, author, serialNumber, genre;
        int publicationYear;

        getline(iss, title, ',');
        getline(iss, author, ',');
        getline(iss, serialNumber, ',');
        iss >> publicationYear;
        iss.ignore(); // Ignore comma
        getline(iss, genre, ',');

        books.emplace_back(title, author, serialNumber, publicationYear, genre);
    }
    file.close();
    return books;
}

// Function to checkout a book
void checkoutBook(const string& username, const string& serialNumber) {
    vector<Book> books = loadAvailableBooks();
    Book selectedBook;
    bool found = false;

    for (const Book& book : books) {
        if (book.serialNumber == serialNumber) {
            selectedBook = book;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Book not found." << endl;
        return;
    }

    fstream file("users.txt", ios::in | ios::out);
    string line, content;
    bool userFound = false;

    while (getline(file, line)) {
        if (line.find(username) != string::npos) {
            userFound = true;
            content += line + "," + selectedBook.title + "," + selectedBook.serialNumber + "\n";
        } else {
            content += line + "\n";
        }
    }
    file.close();

    if (userFound) {
        ofstream outFile("users.txt", ios::trunc);
        outFile << content;
        outFile.close();
        cout << "Book checked out successfully." << endl;
    } else {
        cout << "User not found." << endl;
    }
}

// Function to return a book
void returnBook(const string& username) {
    ifstream file("users.txt");
    string line, content;
    bool userFound = false;

    cout << "Books checked out by " << username << ":\n";

    // Locate the user in the file and display their checked-out books
    while (getline(file, line)) {
        if (line.find(username) != string::npos) {
            userFound = true;
            istringstream iss(line);
            string segment;
            vector<string> segments;
            while (getline(iss, segment, ',')) {
                s egments.push_back(segment);
            }

            // Display checked-out books
            for (size_t i = 2; i < segments.size(); i += 2) {
                cout << "Title: " << segments[i] << ", Serial Number: " << segments[i + 1] << endl;
            }
            break;
        }
    }
    file.close();

    if (!userFound) {
        cout << "User not found." << endl;
        return;
    }

    cout << "Enter the serial number of the book to return: ";
    string serialNumber;
    cin >> serialNumber;

    // Reopen the file to process the return
    ifstream fileIn("users.txt");
    while (getline(fileIn, line)) {
        if (line.find(username) != string::npos) {
            istringstream iss(line);
            string segment;
            vector<string> segments;
            while (getline(iss, segment, ',')) {
                segments.push_back(segment);
            }

            // Rewrite user's data, excluding the returned book
            content += segments[0] + "," + segments[1];
            for (size_t i = 2; i < segments.size(); i += 2) {
                if (segments[i + 1] != serialNumber) {
                    content += "," + segments[i] + "," + segments[i + 1];
                }
            }
            content += "\n";
        } else {
            content += line + "\n";
        }
    }
    fileIn.close();

    // Update the file with the modified content
    ofstream outFile("users.txt", ios::trunc);
    outFile << content;
    outFile.close();
    cout << "Book returned successfully." << endl;
}
