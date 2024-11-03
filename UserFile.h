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
    // Konstruktor przyjmuj�cy nazw� pliku
    UserFile string (fileName);

    // Metoda do wczytania u�ytkownik�w z pliku
    vector<User> loadUsersFromFile();

    // Metoda do dodania nowego u�ytkownika do pliku
    bool addUserToFile(const User &user);

    // Metoda do zmiany has�a w pliku na podstawie ID u�ytkownika
    bool changePasswordInFile(int userId, const string &newPassword);
};

#endif
*/
