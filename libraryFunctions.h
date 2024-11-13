#ifndef LIBRARYFUNCTIONS_H
#define LIBRARYFUNCTIONS_H

#include <string>
#include <vector>

using namespace std;

// Declaration of the Book struct
struct Book {
    string title;
    string author;
    string serialNumber;
    int publicationYear;
    string genre;

    // Constructor for initializing Book objects
    Book(string t, string a, string s, int p, string g);
    Book(); // Default constructor
};

// Declaration of the User struct (if needed in multiple files)
struct User {
    string username;
    string password;
    vector<Book> checkedOutBooks;
};

// Function declarations
vector<Book> loadAvailableBooks();
void checkoutBook(const string& username, const string& serialNumber);
void returnBook(const string& username);

#endif // LIBRARYFUNCTIONS_H
