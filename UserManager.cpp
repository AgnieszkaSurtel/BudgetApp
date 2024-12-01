<<<<<<< HEAD
#include <algorithm>
#include <cstdlib>

#include "UserManager.h"
#include "UserFile.h"
#include "BudgetManager.h"
=======
#include "UserManager.h"
>>>>>>> feature_Save_to_xml

void UserManager::registerUser()
{
    User user =  enterUserData();
    users.push_back(user);

<<<<<<< HEAD
    userFile.addUserToFile(user);
    cout << endl << "Account created successfully" << endl << endl;
    system("pause");
    system ("cls");
=======
    cout << endl << "Account created successfully" << endl << endl;
    system("pause");
>>>>>>> feature_Save_to_xml
}

User UserManager::enterUserData()
{
    User user;
    user.setId(getLoggedUserId());
    string firstName, lastName, login, password;

    cout << "Please enter your first name: ";
    cin >> firstName;
    user.setFirstName(firstName);

    cout << "Please enter your last name: ";
    cin >> lastName;
    user.setLastName(lastName);

    do
    {
        cout << "Please enter your login: ";
        cin >> login;
        user.setLogin(login);
    }
    while (checkIfLoginExist(user.getLogin()) == true);
    cout << "Please enter your password: ";
    cin >> password;
    user.setPassword(password);

    return user;
}

int UserManager::getLoggedUserId()
{
    if (users.empty() ==true)
        return 1;
    else return users.back().getId() + 1;
}

<<<<<<< HEAD
/*{
    return loggedUserId;
}
*/
=======
>>>>>>> feature_Save_to_xml
bool UserManager::checkIfLoginExist (const string &login)
{
    for (int i = 0; i < users.size(); i++)
    {
        if (users[i].getLogin() == login)
        {
            cout << endl << "A user with this login exist " << endl;
            return true;
        }

    }
    return false;
}

<<<<<<< HEAD
bool UserManager::loginUser()
{
    string login, password;
    cout << "Enter your login: ";
    cin >> login;
    cout << "Enter your password: ";
    cin >> password;

    for (auto itr = users.begin(); itr != users.end(); ++itr)
    {
        if (itr->getLogin() == login && itr->getPassword() == password)
        {
            loggedUserId = itr->getId();
            cout << "Login successful! Welcome, " << itr->getFirstName() << "!" << endl;
            system ("pause");
            system ("cls");
            return true;

        }
    }
    cout << "Invalid login or password." << endl;
    system ("pause");
    system ("cls");
    return false;
}

void UserManager::changeUserPassword()
{
    string newPassword;
    cout << "Enter new password: ";
    cin >> newPassword;

    if (userFile.changePasswordInFile(loggedUserId, newPassword))
    {
        users = userFile.loadUsersFromFile();
        cout << "Password has been successfully changed." << endl;
    }
    else
    {
        cout << " User not found. Password change failed." << endl;
    }
}

void UserManager::logoutUser()
{
    loggedUserId = -1;
    cout << "Logged out successfully." << endl;
}
=======
void UserManager::wypiszWszystkichUzytkownikow()
{
        for (int i = 0; i < users.size(); i++)
    {
        cout << "ID: " << users[i].getId() << endl;
        cout << "First Name: " << users[i].getFirstName() << endl;
        cout << "Last Name: " << users[i].getLastName() << endl;
        cout << "Login " << users[i].getLogin() << endl;
        cout << "Password: " << users[i].getPassword() << endl;

    }
}
>>>>>>> feature_Save_to_xml
