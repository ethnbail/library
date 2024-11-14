#ifndef LIBRARYFUNCTIONS_H
#define LIBRARYFUNCTIONS_H

#include "Book.h"
#include <vector>
#include <string>

using namespace std;

// Updated function signatures to match the new serialNumber type as string
vector<Book> loadAvailableBooks();
void checkoutBook(const string& username, const string& serialNumber);  // Change to string
void returnBook(const string& username);
void displayBooksBySubgenre(const vector<Book>& availableBooks, const string& subgenre, const string& username);

#endif
