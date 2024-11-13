#include "searchFunction.h"
#include <iostream>
#include <algorithm>

using namespace std;

vector<string> getSubgenres(const vector<Book>& availableBooks) {
    vector<string> subgenres;

    for (const auto& book : availableBooks) {
        if (find(subgenres.begin(), subgenres.end(), book.subgenre) == subgenres.end()) {
            subgenres.push_back(book.subgenre);
        }
    }

    return subgenres;
}

void displaySubgenres(const vector<Book>& availableBooks, const vector<string>& subgenres) {
    for (size_t i = 0; i < subgenres.size(); ++i) {
        cout << i + 1 << ". " << subgenres[i] << endl;
    }
}
