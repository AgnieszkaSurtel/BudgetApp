#include "UserFile.h"

using namespace std;

bool UserFile::addUserToFile(const User& user) {
    CMarkup xml;
    bool fileExists = xml.Load(fileName);

    // Jeœli plik nie istnieje, twórz nowy dokument XML
    if (!fileExists) {
        xml.SetDoc("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n");
        xml.AddElem("Users");
    } else {
        xml.FindElem();
        xml.IntoElem();
    }

    // Dodaj nowego u¿ytkownika do XML
    xml.AddElem("User");
    xml.IntoElem();
    xml.AddElem("UserId", to_string(user.id));
    xml.AddElem("Login", user.login);
    xml.AddElem("Password", user.password);
    xml.AddElem("FirstName", user.firstName);
    xml.AddElem("LastName", user.lastName);
    xml.OutOfElem(); // Wracamy do elementu "Users"

    return xml.Save(fileName); // Zapisz plik
}

vector<User> UserFile::loadUsersFromFile() {
vector<User> users;
    CMarkup xml;
    bool fileExists = xml.Load(fileName);
    if (fileExists) {
        xml.FindElem("Users");
        xml.IntoElem();
        while (xml.FindElem("User")) {
            User user;
            xml.IntoElem();
            user.id = stoi(xml.GetElemContent("UserId"));
            user.login = xml.GetElemContent("Login");
            user.password = xml.GetElemContent("Password");
            user.firstName = xml.GetElemContent("FirstName");
            user.lastName = xml.GetElemContent("LastName");
            users.push_back(user);
            xml.OutOfElem();
        }
    }
    return users;
}

