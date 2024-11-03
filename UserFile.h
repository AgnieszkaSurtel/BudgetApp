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


