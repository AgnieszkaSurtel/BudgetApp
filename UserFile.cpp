#include "UserFile.h"
#include "User.h"
#include "Markup.h"


using namespace std;

bool UserFile::addUserToFile(const User& user)
{
    CMarkup xml;
    bool fileExists = xml.Load("users.xml");

    if (!fileExists)
    {
        xml.SetDoc("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n");
        xml.AddElem("Users");
    }

    xml.FindElem("Users");
    xml.IntoElem();

    int lastUserId = 0;
    while (xml.FindElem("User"))
    {
        xml.IntoElem();
        if (xml.FindElem("UserId"))
        {
            int userId = stoi(xml.GetData());
            if (userId > lastUserId)
            {
                lastUserId = userId;
            }
        }
        xml.OutOfElem();
    }


    int newUserId = lastUserId + 1;

    xml.AddElem("User");
    xml.IntoElem();
    xml.AddElem("UserId", to_string(newUserId));
    xml.AddElem("Login", user.getLogin());
    xml.AddElem("Password", user.getPassword());
    xml.AddElem("FirstName", user.getFirstName());
    xml.AddElem("LastName", user.getLastName());
    xml.OutOfElem();

    if (!xml.Save("users.xml")) {
        cout << "Failed to save users.xml!" << endl;
        return false;
    }
    return true;
}

vector<User> UserFile::loadUsersFromFile()
{
    vector<User> users;
    CMarkup xml;

    if (!xml.Load("users.xml"))
    {
        return users;
    }

    xml.FindElem("Users");
    xml.IntoElem();

    while (xml.FindElem("User"))
    {
        User user;
        xml.IntoElem();

        if (xml.FindElem("UserId"))
        {
            user.setId(stoi(xml.GetData()));
        }
        if (xml.FindElem("Login"))
        {
            user.setLogin(xml.GetData());
        }
        if (xml.FindElem("Password"))
        {
            user.setPassword(xml.GetData());
        }
        if (xml.FindElem("FirstName"))
        {
            user.setFirstName(xml.GetData());
        }
         if (xml.FindElem("LastName"))
        {
            user.setLastName(xml.GetData());
        }
        xml.OutOfElem();
        users.push_back(user);
    }

    return users;
}

bool UserFile::changePasswordInFile(int id, const string &newPassword)
{
    CMarkup xml;
    string fileName = "users.xml";
    bool fileExists = xml.Load(fileName);

    if (!fileExists)
    {
        cout << "File not found " << fileName << ". Password change failed." << endl;
        return false;
    }

    xml.FindElem("Users");
    xml.IntoElem();

    bool userFound = false;

    while (xml.FindElem("User"))
    {
        xml.IntoElem();
        int userId = -1;

        if (xml.FindElem("UserId"))
        {
            userId = stoi(xml.GetData());
        }

        if (userId == id)
        {
            userFound = true;
            if (xml.FindElem("Password"))
            {
                xml.SetData(newPassword);
            }
            xml.OutOfElem();
            break;
        }

         xml.OutOfElem();
    }

    if (!xml.Save(fileName)) {
        cout << "Failed to save " << fileName << " after password change." << endl;
        return false;
    }

    return userFound;
}


