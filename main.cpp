//g++ main.cpp Book.cpp libraryFunctions.cpp UserAccount.cpp -o library.exe
#include <iostream>
#include "UserAccount.h"
#include <ctime>
#include <windows.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "libraryFunctions.h"

using namespace std;

int main() {
    int choice;
    string response;
    string username;

    cout << "Welcome to Book Nest Library" << endl;
    Sleep(2000); // Corrected sleep time (in milliseconds, so 2000 ms = 2 seconds)
    cout << "1. Create Account" << endl;
    cout << "2. Sign In" << endl;
    cout << "Choose an option: ";
    cin >> choice;

    cout << "You chose option " << choice << endl;  // Debug line

    if (choice == 1) {
        createAccount();  // Initiates the create account function
    } else if (choice == 2) {
        if (signIn()) {
            cout << "Sign-in successful!" << endl;
        } else {
            cout << "Invalid username or password." << endl;
            return 0; // Exit if sign-in fails
        }
    } else {
        cout << "Invalid option." << endl;
        return 0; // Exit if an invalid option is chosen
    }
    
    cout << "Did you want to checkout(1) or return(2) a book today? ";
    cin >> response;

    if (response == "1") {
        cout << "Were you looking for a specific book today?" << endl;
      
    } else if (response == "2") {
        cout << "Great! Let's take a look at your account." << endl;
        returnBook(username); // username should be captured during sign-in
    } else {
        cout << "Invalid option. Try again." << endl;
    }

    return 0;
}
