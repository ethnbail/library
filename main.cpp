//g++ main.cpp UserAccount.cpp -o library.exe

#include <iostream>
#include "UserAccount.h"
#include <ctime>
#include <windows.h>

using namespace std;

int main() {
    int choice;
    string response;

    cout << "Welcome to Book Nest Library" << endl;
    Sleep(3000); // Corrected sleep time (in milliseconds, so 3000 ms = 3 seconds)
    cout << "1. Create Account" << endl;
    cout << "2. Sign In" << endl;
    cout << "Choose an option: " << endl;

    cin >> choice;

    cout << "You chose option " << choice << endl;  // Debug line

    if (choice == 1) {
        createAccount();  //initiates the create account function
    } else if (choice == 2) {
        if (signIn()) {
            cout << "Sign-in successful!" << endl;
        } else {
            cout << "Invalid username or password." << endl;
        }
    } else {
        cout << "Invalid option." << endl;
    }
    
    cout << "Did you want to checkout(1) or return(2) a book today?"<< endl;
    cin << response;
       if (response == 1) {
       cout <<"Were you looking for a specific book today?" << endl;
    } else if (reponse == 2) {
        if (signIn()) {
            cout << "Sign-in successful!" << endl;
        } else {
            cout << "Invalid username or password." << endl;
        }
    } else {
        cout << "Invalid option." << endl;
    }
    
    return 0;
}
