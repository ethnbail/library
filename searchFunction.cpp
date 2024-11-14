#include "searchFunction.h"
#include <iostream>
#include <algorithm>

using namespace std;

// function to get all unique subgenres
vector<string> getSubgenres(const vector<Book>& availableBooks) {
    vector<string> subgenres;

// loops through the list of books
    for (const auto& book : availableBooks) {
        if (find(subgenres.begin(), subgenres.end(), book.subgenre) == subgenres.end()) {
            subgenres.push_back(book.subgenre);
        }
    }

    return subgenres; // returns the list of unique subgenres
}

// function to display the subgenres
void displaySubgenres(const vector<Book>& availableBooks, const vector<string>& subgenres) {
    for (size_t i = 0; i < subgenres.size(); ++i) {// correlates the unique subgenres to a number
        cout << i + 1 << ". " << subgenres[i] << endl;
    }
}
