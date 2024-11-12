#include "Book.h"
#include <iostream>

using namespace std;

void Book displayBookInfo() const{
    cout << "Title: " << title << endl;
    cout << "Author: " << author << endl;
    cout << "Serial Number: " << serialNumber << endl;
    cout << "Publication Year: " << publicationYear << endl;
    cout << "Genre: " << genre << endl;
}