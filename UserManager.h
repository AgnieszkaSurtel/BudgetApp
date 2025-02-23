#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <iostream>
#include <vector>

#include "User.h"
#include "UserFile.h"

using namespace std;

class UserManager
{
    int loggedUserId;
    vector <User> users;
    UserFile userFile;

    User enterUserData();

    bool checkIfLoginExist (const string &login);

public:

    UserManager(string userFileName) : userFile(userFileName)
    {
        loggedUserId = -1;
        users = userFile.loadUsersFromFile();

    }
    void registerUser();
    int getLoggedUserId() const;
    bool loginUser();
    void changeUserPassword();
    void logoutUser();
    bool isUserLoggedIn() const;
};

#endif
