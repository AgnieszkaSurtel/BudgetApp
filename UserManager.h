#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <iostream>
#include <vector>
#include <windows.h>

#include "User.h"
#include "UserFile.h"


using namespace std;

class UserManager
{
    int loggedUserId;
    vector <User> users;
    UserFile userFile;

    User enterUserData();
    int getLoggedUserId();
    bool checkIfLoginExist (const string &login);
    void findUserByLogin(const string &login, vector<User>::iterator &itr);
    void findUserById(int id, vector<User>::iterator &itr);

public:

     UserManager(string userFileName) : userFile(userFileName) {
        users = userFile.loadUsersFromFile(); // Wczytaj u¿ytkowników z pliku
        loggedUserId = -1;
    }
    void registerUser();
    bool loginUser();
    void changeUserPassword();
    void logoutUser();
    bool isUserLoggedIn() const { return loggedUserId != -1; }
    int getLoggedUserId() const { return loggedUserId; }

};

#endif
