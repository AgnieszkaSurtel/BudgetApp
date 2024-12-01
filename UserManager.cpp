#include <algorithm>
#include <cstdlib>

#include "UserManager.h"
#include "UserFile.h"
#include "BudgetManager.h"

void UserManager::registerUser()
{
    User user =  enterUserData();
    users.push_back(user);

    userFile.addUserToFile(user);
    cout << endl << "Account created successfully" << endl << endl;
    system("pause");
    system ("cls");
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

/*{
    return loggedUserId;
}
*/
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
