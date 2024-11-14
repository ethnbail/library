#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <vector>

using namespace std;

class Book {
public:
// member variables
    string title;
    string author;
    string serialNumber;
    int publicationYear;
    string genre;
    string subgenre;

// construcr with parameters to initals a book object
    Book(string t, string a, string s, int p, string g, string subg)
        : title(t), author(a), serialNumber(s), publicationYear(p), genre(g), subgenre(subg) {}

    // Default constructor for creating an empty book
    Book() : title(""), author(""), serialNumber(""), publicationYear(0), genre(""), subgenre("") {}
};

#endif
