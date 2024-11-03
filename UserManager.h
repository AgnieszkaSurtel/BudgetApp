#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <iostream>
#include <vector>
#include <windows.h>

#include "User.h"


using namespace std;

class UserManager
{
    int loggedUserId;
    vector <User> users;

private: // domyslnie wszystko jest prywatne
    User enterUserData();
    int getLoggedUserId();
    bool checkIfLoginExist (const string &login);



public:
    void registerUser();
    void wypiszWszystkichUzytkownikow();

};

#endif
