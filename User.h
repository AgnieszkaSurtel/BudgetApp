#ifndef USER_H
#define USER_H

#include <iostream>

using namespace std;

struct User
{
    int id;
    string firstName, lastName, login, password;

public:
<<<<<<< HEAD
=======
    //settery
>>>>>>> feature_Save_to_xml

    void setId (int newId);
    void setFirstName(string newFirstName);
    void setLastName (string newLastName);
    void setLogin(string newLogin);
    void setPassword (string newPassword);

<<<<<<< HEAD
    int getId() const;
    string getFirstName() const;
    string getLastName() const;
    string getLogin() const;
    string getPassword() const;
=======
    //gettery

    int getId();
    string getFirstName();
    string getLastName();
    string getLogin();
    string getPassword();
>>>>>>> feature_Save_to_xml
};

#endif
