#ifndef USERFILE_H
#define USERFILE_H

#include <vector>
#include <string>
#include "UserFile.h" // zak³adam, ¿e masz plik nag³ówkowy z deklaracj¹ struktury User

class UserFile {
private:
    std::string userFileName;  // Nazwa pliku z u¿ytkownikami

public:
    // Konstruktor przyjmuj¹cy nazwê pliku
    UserFile(std::string fileName);

    // Metoda do wczytania u¿ytkowników z pliku
    std::vector<User> loadUsersFromFile();

    // Metoda do dodania nowego u¿ytkownika do pliku
    bool addUserToFile(const User &user);

    // Metoda do zmiany has³a w pliku na podstawie ID u¿ytkownika
    bool changePasswordInFile(int userId, const std::string &newPassword);
};

#endif
