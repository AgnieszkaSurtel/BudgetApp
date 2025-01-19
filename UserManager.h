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

    void findUserByLogin(const string &login, vector<User>::iterator &itr);
    void findUserById(int id, vector<User>::iterator &itr);
    bool checkIfLoginExist (const string &login);

public:

    UserManager(string userFileName) : userFile(userFileName)
    {
        users = userFile.loadUsersFromFile();
        loggedUserId = -1;
    }
    int getLoggedUserId() const;
    void registerUser();
    bool loginUser();
    void changeUserPassword();
    void logoutUser();
    bool isUserLoggedIn() const;


};

#endif
