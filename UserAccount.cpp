#include <iostream>
#include <fstream>
#include <string>
#include "UserAccount.h"

using namespace std;

// Function to create a new account
void createAccount() {
    string username, password;

    cout << "Enter a username: ";
    cin >> username;
    cout << "Enter a password: ";
    cin >> password;

    // Open the file to check if the username already exists
    ifstream infile("users.txt"); // Corrected file name to "users.txt"
    string line;

    // Check if the username already exists
    while (getline(infile, line)) {
        if (line.substr(0, line.find(',')) == username) {
            cout << "This username already exists, try again" << endl;
            infile.close();
            return;
        }
    }
    infile.close();

    // If the username doesn't exist, append the new account to the file
    ofstream outfile("users.txt", ios::app); // Corrected syntax for file output
    outfile << username << "," << password << endl;
    outfile.close();

    cout << "Account has been created" << endl;
}

// Function to sign in to an existing account
bool signIn() {
    string username, password;

    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your password: ";
    cin >> password;

    ifstream infile("users.txt"); // Corrected file name to "users.txt"
    string line;

    // Read the file and check for matching username and password
    while (getline(infile, line)) {
        string storedUsername = line.substr(0, line.find(','));
        string storedPassword = line.substr(line.find(',') + 1);

        if (storedUsername == username && storedPassword == password) {

            infile.close();
            return true; // Return true if the sign-in is successful
        }
    }

    infile.close();
    cout << "Invalid username or password" << endl;
    return false; // Return false if sign-in fails
}
