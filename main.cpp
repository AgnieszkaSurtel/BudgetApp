#include <iostream>

#include "UserManager.h"

using namespace std;

int main()
{
    UserManager userManager("users.xml");

    cout << "=== REJESTRACJA ===" << endl;

    //userManager.registerUser();

    cout << "=== LOGOWANIE ===" << endl;
    if (userManager.loginUser())
    {
        cout << "Logowanie zakonczone sukcesem!" << endl;

        char choice;
        cout << "Czy chcesz zmienic haslo? (t/n): ";
        cin >> choice;

        if (choice == 't' || choice == 'T')
        {
            userManager.changeUserPassword();
        }
        else
        {
            cout << "Nie zmieniono has³a." << endl;
        }
    }
    else
    {
        cout << "Logowanie nie powiod³o siê. Sprawdz login i haslo." << endl;
    }


    return 0;

//    userManager.wypiszWszystkichUzytkownikow();
    return 0;
}
