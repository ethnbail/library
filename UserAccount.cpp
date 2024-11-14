#include "UserAccount.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

void createAccount() {
    string username, password;
    cout << "Enter your desired username: ";
    cin >> username;
    cout << "Enter your desired password: ";
    cin >> password;

    ofstream outFile("users.txt", ios::app);
    outFile << username << "," << password << endl;
    outFile.close();

    cout << "Account created successfully!" << endl;
}

bool signIn(string& username) {
    string enteredUsername, enteredPassword;
    cout << "Enter username: ";
    cin >> enteredUsername;
    cout << "Enter password: ";
    cin >> enteredPassword;

    ifstream inFile("users.txt");
    string line;

    while (getline(inFile, line)) {
        istringstream ss(line);
        string storedUsername, storedPassword;

        getline(ss, storedUsername, ',');
        getline(ss, storedPassword);

        if (storedUsername == enteredUsername && storedPassword == enteredPassword) {
            username = enteredUsername;
            return true;
        }
    }

    return false;
}
