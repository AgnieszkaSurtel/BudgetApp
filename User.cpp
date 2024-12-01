#include "User.h"

void User::setId (int newId)
{
    if (newId >= 0)
        id = newId;
}
void User::setFirstName (string newFirstName)
{
    firstName = newFirstName;
}
void User::setLastName (string newLastName)
{
    lastName = newLastName;
}
void User::setLogin(string newLogin)
{
    login = newLogin;
}
void User::setPassword (string newPassword)
{
    password = newPassword;
}

<<<<<<< HEAD
int User::getId() const
{
    return id;
}
string User::getFirstName() const
{
    return firstName;
}
string User::getLastName() const
{
    return lastName;
}
string User::getLogin() const
{
    return login;
}
string User::getPassword() const
=======
int User::getId()
{
    return id;
}
string User::getFirstName()
{
    return firstName;
}
string User::getLastName()
{
    return lastName;
}
string User::getLogin()
{
    return login;
}
string User::getPassword()
>>>>>>> feature_Save_to_xml
{
    return password;
}
