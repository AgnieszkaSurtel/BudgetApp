#include <iostream>


#include "UserManager.h"

using namespace std;

int main()
{
    UserManager userManager;
     cout << "REGISTRATION" << endl << endl;
    userManager.registerUser();

    userManager.wypiszWszystkichUzytkownikow();
    return 0;
}
