#include "UserAccount.h"
#include <iostream>
#include <fstream>

void creatAccount(){
    string username, password;

    cout << "Enter a username";
        cin >> username;
    cout << "Enter a password";
        cin >> password;

        ifstream infile("user.txt");
        string line;
    while (getline(infile, line)){
        if (line.substr(0, line.find(,))== username){
            cout << "This username already exists, try again" << endl;
            infile.close();
            return;
        }
    }
    infile.close();

    
}