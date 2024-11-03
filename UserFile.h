#ifndef USERFILE_H
#define USERFILE_H

#include <string>
#include <vector>
#include "User.h"
#include "Markup.h"

using namespace std;

class UserFile {
private:
    string fileName;

public:
    UserFile(const string& userFileName) : fileName(userFileName) {}
    vector<User> loadUsersFromFile();
    bool addUserToFile(const User& user);
};

#endif






/*#ifndef USERFILE_H
#define USERFILE_H

#include <vector>
#include <string>
#include "UserFile.h"

using namespace std;


class UserFile {
private:
  string userFileName;
public:
    // Konstruktor przyjmujący nazwę pliku
    UserFile string (fileName);

    // Metoda do wczytania użytkowników z pliku
    vector<User> loadUsersFromFile();

    // Metoda do dodania nowego użytkownika do pliku
    bool addUserToFile(const User &user);

    // Metoda do zmiany hasła w pliku na podstawie ID użytkownika
    bool changePasswordInFile(int userId, const string &newPassword);
};

#endif
*/
