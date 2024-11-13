#ifndef BOOK_H
#define BOOK_H

#include <string>
using namespace std;

class Book{
    public: 
        string title;
        string author;
        string serialNumber;
        int publicationYear;
        string genre;

        Book(string t, string a, string s, int p, string g)
        :title(t), author(a), serialNumber(s), publicationYear(p), genre(g){}
        
        void displayBookInfo() const;
};

#endif