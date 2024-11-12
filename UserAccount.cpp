#include <iostream>
#include <fstream>
#include <string>
#include "UserAccount.h"

using namespace std;


void createAccount() {
    string username, password;
    cout << "Enter a username: ";
    cin >> username;
    cout << "Enter a password: ";
    cin >> password;


    ifstream infile("users.txt");// opens the users.txt
    string line;

   
    while (getline(infile, line)) {
        if (line.substr(0, line.find(',')) == username) { // looks if the code has the username trying to be used
            cout << "This username already exists, try again" << endl;
            infile.close(); 
            return;
        }
    }
    infile.close();

    
    ofstream outfile("users.txt", ios::app); 
    outfile << username << "," << password << endl;
    outfile.close(); // adding the new usernameand password to the txt file to save it

    cout << "Account has been created" << endl;
}


bool signIn() {
    string username, password;

    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your password: ";
    cin >> password;

    ifstream infile("users.txt"); 
    string line;

  // finds the username & password that was given
    while (getline(infile, line)) {
        string storedUsername = line.substr(0, line.find(','));
        string storedPassword = line.substr(line.find(',') + 1);

        if (storedUsername == username && storedPassword == password) {

            infile.close();
            return true; 
        }
    }

    infile.close();
    cout << "Invalid username or password" << endl;
    return false; 