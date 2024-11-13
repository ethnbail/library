#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

struct Book {
    string title;
    string author;
    string serialNumber;
    string date;
    string genre;
};

struct User {
    string username;
    string password;
    vector<Book> checkedOutBooks;
};

// Function to load available books from "booksavailable.txt"
vector<Book> loadAvailableBooks() {
    ifstream file("booksavailable.txt");
    vector<Book> books;
    string line;
    
    while (getline(file, line)) {
        istringstream iss(line);
        Book book;
        getline(iss, book.title, ',');
        getline(iss, book.author, ',');
        getline(iss, book.serialNumber, ',');
        getline(iss, book.date, ',');
        getline(iss, book.genre, ',');
        books.push_back(book);
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

    while (getline(file, line)) {
        if (line.find(username) != string::npos) {
            userFound = true;
            istringstream iss(line);
            string segment;
            vector<string> segments;
            while (getline(iss, segment, ',')) {
                segments.push_back(segment);
            }

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

    ifstream fileIn("users.txt");
    while (getline(fileIn, line)) {
        if (line.find(username) != string::npos) {
            istringstream iss(line);
            string segment;
            vector<string> segments;
            while (getline(iss, segment, ',')) {
                segments.push_back(segment);
            }

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

    ofstream outFile("users.txt", ios::trunc);
    outFile << content;
    outFile.close();
    cout << "Book returned successfully." << endl;
}