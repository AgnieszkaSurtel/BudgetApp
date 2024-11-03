#include "UserFile.h"
#include "User.h"
#include "Markup.h"
#include <iostream>

using namespace std;

// Dodawanie użytkownika do pliku XML
bool UserFile::addUserToFile(const User& user)
{
    CMarkup xml;

    // Wczytaj plik XML, jeśli istnieje
    bool fileExists = xml.Load("users.xml");

    // Jeśli plik nie istnieje, utwórz nowy dokument XML
    if (!fileExists)
    {
        xml.SetDoc("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n");
        xml.AddElem("Users");
    }

    // Przejdź do głównego elementu "Users"
    xml.FindElem("Users");
    xml.IntoElem();

    // Dodaj nowy element "User" z danymi użytkownika
    xml.AddElem("User");
    xml.IntoElem();
    xml.AddElem("UserId", to_string(user.getId()));
    xml.AddElem("Login", user.getLogin());
    xml.AddElem("Password", user.getPassword());
    xml.OutOfElem(); // Powrót do elementu "Users"

    // Zapisz zmiany do pliku XML
    xml.Save("users.xml");
    return true;
}

// Wczytywanie użytkowników z pliku XML
vector<User> UserFile::loadUsersFromFile()
{
    vector<User> users;
    CMarkup xml;

    // Wczytaj plik XML
    if (!xml.Load("users.xml")) {
        cout << "Nie znaleziono pliku users.xml. Brak uzytkowników do załadowania." << endl;
        return users; // Zwraca pusty wektor, jeśli plik nie istnieje
    }

    // Przejdź do głównego elementu "Users"
    xml.FindElem("Users");
    xml.IntoElem();

    // Wczytaj każdy element "User" z danymi użytkowników
    while (xml.FindElem("User")) {
        User user;
        xml.IntoElem();

        // Pobierz dane użytkownika
        if (xml.FindElem("UserId")) {
            user.setId(stoi(xml.GetData()));
        }
        if (xml.FindElem("Login")) {
            user.setLogin(xml.GetData());
        }
        if (xml.FindElem("Password")) {
            user.setPassword(xml.GetData());
        }

        xml.OutOfElem(); // Powrót do listy "User"
        users.push_back(user); // Dodaj użytkownika do wektora
    }

    return users;
}
