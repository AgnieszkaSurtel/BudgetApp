#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <iostream>
#include <vector>
#include <windows.h>

#include "User.h"
<<<<<<< HEAD
#include "UserFile.h"
=======
>>>>>>> feature_Save_to_xml


using namespace std;

class UserManager
{
    int loggedUserId;
    vector <User> users;
<<<<<<< HEAD
    UserFile userFile;

    User enterUserData();

    bool checkIfLoginExist (const string &login);
    void findUserByLogin(const string &login, vector<User>::iterator &itr);
    void findUserById(int id, vector<User>::iterator &itr);

public:

    UserManager(string userFileName) : userFile(userFileName)
    {
        users = userFile.loadUsersFromFile();
        loggedUserId = -1;
    }
    int getLoggedUserId();
    void registerUser();
    bool loginUser();
    void changeUserPassword();
    void logoutUser();
    bool isUserLoggedIn() const
    {
        return loggedUserId != -1;
    }
    int getLoggedUserId() const
    {
        return loggedUserId;
    }
=======

private: // domyslnie wszystko jest prywatne
    User enterUserData();
    int getLoggedUserId();
    bool checkIfLoginExist (const string &login);



public:
    void registerUser();
    void wypiszWszystkichUzytkownikow();
>>>>>>> feature_Save_to_xml

};

#endif
