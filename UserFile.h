#ifndef USERFILE_H
#define USERFILE_H

#include <vector>
#include <string>
#include "UserFile.h" // zak�adam, �e masz plik nag��wkowy z deklaracj� struktury User

class UserFile {
private:
    std::string userFileName;  // Nazwa pliku z u�ytkownikami

public:
    // Konstruktor przyjmuj�cy nazw� pliku
    UserFile(std::string fileName);

    // Metoda do wczytania u�ytkownik�w z pliku
    std::vector<User> loadUsersFromFile();

    // Metoda do dodania nowego u�ytkownika do pliku
    bool addUserToFile(const User &user);

    // Metoda do zmiany has�a w pliku na podstawie ID u�ytkownika
    bool changePasswordInFile(int userId, const std::string &newPassword);
};

#endif
