#ifndef LIBRARYFUNCTIONS_H
#define LIBRARYFUNCTIONS_H

#include "Book.h"
#include <vector>
#include <string>

using namespace std;

vector<Book> loadAvailableBooks();// load available books from the txt file
void checkoutBook(const string& username, const string& serialNumber); // checkout books by username and serial 
void returnBook(const string& username);// return book by username
void displayBooksBySubgenre(const vector<Book>& availableBooks, const string& subgenre, const string& username);// display books by subgenre

#endif
