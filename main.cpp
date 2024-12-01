#include <iostream>
#include <cstdlib>

#include "BudgetMainApp.h"
#include "Menus.h"

#include "Utils.h"


#include "UserManager.h"

using namespace std;

int main ()
{

    BudgetMainApp budgetMainApp ("users.xml", "incomes.xml", "expenses.xml");

    char choice;

    while(true)
    {
        if(!budgetMainApp.isUserLoggedIn())
        {
            Menus::showTitle("HOME MENU");
            Menus::showHomeMenu();

            choice = Utils::getCharacter();

            switch (choice)
            {
            case '1':
                budgetMainApp.loginUser();
                break;
            case '2':
                budgetMainApp.registerUser();
                break;
            case '9':
                cout <<"See you next time! " << endl;
                system("pause");
                break;
            default:
                cout <<"Character not recognized. Try again: " << endl;
                break;

            }
        }
        else
        {

            Menus::showTitle("MAIN MENU");
            Menus::showMainMenu();

            choice = Utils::getCharacter();

            switch (choice)
            {
            case '1':
                budgetMainApp.addIncome();
                break;
            case '2':
                budgetMainApp.addExpense();
                break;
            case '3':
                budgetMainApp.showCurrentMonthBalance();
                break;
            case '4':
                budgetMainApp.showPreviousMonthBalance();
                break;
            case '5':
                budgetMainApp.showCustomPeriodBalance();
                break;
            case '6':
                budgetMainApp.changeUserPassword();
                break;
            case '8':
                budgetMainApp.logoutUser();
                break;
            default:
                cout << "Character not recognized. Try again: " << endl;
                break;
            }

        }
    }

    UserManager userManager;
     cout << "REGISTRATION" << endl << endl;
    userManager.registerUser();

  
    return 0;
>
}
