#ifndef USER_H
#define USER_H

#include <iostream>

using namespace std;

struct User
{
    int id;
    string firstName, lastName, login, password;

public:
    //settery

    void setId (int newId);
    void setFirstName(string newFirstName);
    void setLastName (string newLastName);
    void setLogin(string newLogin);
    void setPassword (string newPassword);

    //gettery

    int getId() const;
    string getFirstName() const;
    string getLastName() const;
    string getLogin() const;
    string getPassword() const;
};

#endif
