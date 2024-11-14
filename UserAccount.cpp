#include "UserAccount.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// function to create a new user
void createAccount() {
    string username, password;
    cout << "Enter your desired username: ";
    cin >> username;
    cout << "Enter your desired password: ";
    cin >> password;
// open the users.txt in append mode to right at the bottom of the file
    ofstream outFile("users.txt", ios::app);
    outFile << username << "," << password << endl; // write the new username and password
    outFile.close();

    cout << "Account created successfully!" << endl;
}

// function to sign in to existing user
bool signIn(string& username) {
    string enteredUsername, enteredPassword;
    cout << "Enter username: ";
    cin >> enteredUsername;
    cout << "Enter password: ";
    cin >> enteredPassword;

    ifstream inFile("users.txt");
    string line;

// goes through each line in the file
    while (getline(inFile, line)) {
        istringstream ss(line);
        string storedUsername, storedPassword;

        getline(ss, storedUsername, ',');
        getline(ss, storedPassword);
        
// if a username and password match with what was entered it will sign in
        if (storedUsername == enteredUsername && storedPassword == enteredPassword) {
            username = enteredUsername;
            return true;
        }
    }

    return false;
}
