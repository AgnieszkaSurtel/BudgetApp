#include <iostream>
#include "Markup.h"

#include "UserManager.h"

using namespace std;

int main()
{
    UserManager userManager;
     cout << "REGISTRATION" << endl << endl;
    userManager.registerUser();
    userManager.registerUser();
    userManager.registerUser();
    userManager.wypiszWszystkichUzytkownikow();
    return 0;
}