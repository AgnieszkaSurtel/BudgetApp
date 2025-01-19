#ifndef BUDGETMAINAPP_H
#define BUDGETMAINAPP_H

#include <string>
#include "UserManager.h"
#include "BudgetManager.h"

using namespace std;

class BudgetMainApp
{
private:
    UserManager userManager;
    BudgetManager *budgetManager;
    const string INCOME_FILE_NAME;
    const string EXPENSE_FILE_NAME;

public:
    BudgetMainApp(const string& userFileName, const string& incomeFileName, const string& expenseFileName);
    ~BudgetMainApp();

    bool isUserLoggedIn() const;
    void registerUser();
    void loginUser();
    void changeUserPassword();
    void logoutUser();
    void addIncome();
    void addExpense();
    void showCurrentMonthBalance();
    void showPreviousMonthBalance();
    void showCustomPeriodBalance ();
};

#endif
