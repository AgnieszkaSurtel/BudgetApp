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

public:

     UserManager(string userFileName) : userFile(userFileName) {
        users = userFile.loadUsersFromFile(); // Wczytaj u¿ytkowników z pliku
    }
    void registerUser();
    void wypiszWszystkichUzytkownikow();
};

#endif
