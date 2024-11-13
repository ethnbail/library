#ifndef LIBRARYFUNCTIONS_H
#define LIBRARYFUNCTIONS_H

#include "Book.h"
#include <vector>
#include <string>

using namespace std;

vector<Book> loadAvailableBooks();
void checkoutBook(const string& username, int serialNumber);
void returnBook(const string& username);
void displayBooksBySubgenre(const vector<Book>& availableBooks, const string& subgenre, const string& username);

#endif
