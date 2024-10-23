#include <iostream>
#include <vector>

#include "User.h"

using namespace std;

class UserManager
{
    int loggedUserId;
    vector <User> users;

public:
    void registerUser();

};
