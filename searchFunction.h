#ifndef SEARCHFUNCTION_H
#define SEARCHFUNCTION_H

#include <string>
#include <vector>
#include "Book.h"

using namespace std;

vector<string> getSubgenres(const vector<Book>& availableBooks);
void displaySubgenres(const vector<Book>& availableBooks, const vector<string>& subgenres);

#endif
