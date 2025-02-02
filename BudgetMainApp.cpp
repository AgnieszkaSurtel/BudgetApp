#include <iostream>

#include "Type.h"
#include "BudgetMainApp.h"
#include "BudgetManager.h"


using namespace std;


BudgetMainApp::BudgetMainApp(const string& userFileName, const string& incomeFileName, const string& expenseFileName)
    : userManager(userFileName), budgetManager(nullptr),
      INCOME_FILE_NAME(incomeFileName), EXPENSE_FILE_NAME(expenseFileName) {}

BudgetMainApp::~BudgetMainApp()
{
    delete budgetManager;
}

bool BudgetMainApp::isUserLoggedIn() const
{
    return userManager.isUserLoggedIn();
}

void BudgetMainApp::registerUser()
{
    userManager.registerUser();
}

void BudgetMainApp::loginUser()
{
    if (userManager.loginUser())
    {
        budgetManager = new BudgetManager(INCOME_FILE_NAME, EXPENSE_FILE_NAME, userManager.getLoggedUserId());
    }
}

void BudgetMainApp::changeUserPassword()
{
    userManager.changeUserPassword();
}

void BudgetMainApp::logoutUser()
{
    userManager.logoutUser();
    delete budgetManager;
    budgetManager = nullptr;
}

void BudgetMainApp::addIncome()
{
    if (userManager.isUserLoggedIn() && budgetManager != nullptr)
    {
        budgetManager->addIncome();
    }
    else
    {
        cout << "You must be logged in to add an income!" << endl;
    }
}

void BudgetMainApp::addExpense()
{
    if (userManager.isUserLoggedIn() && budgetManager != nullptr)
    {
        budgetManager->addExpense();
    }
    else
    {
        cout << "You must be logged in to add an expense!" << endl;
    }
}

void BudgetMainApp::showCurrentMonthBalance()
{
    if (userManager.isUserLoggedIn() && budgetManager != nullptr)
    {
        budgetManager->showCurrentMonthBalance();
    }
    else
    {
        cout << "You must be logged in to view your balance!" << endl;
    }
}

void BudgetMainApp::showPreviousMonthBalance()
{
    if (userManager.isUserLoggedIn() && budgetManager != nullptr)
    {
        budgetManager->showPreviousMonthBalance();
    }
    else
    {
        cout << "You must be logged in to view your balance!" << endl;
    }
}

void BudgetMainApp::showCustomPeriodBalance()
{
    if (userManager.isUserLoggedIn() && budgetManager != nullptr)
    {
        budgetManager->showCustomPeriodBalance();
    }
    else
    {
        cout << "You must be logged in to view your balance!" << endl;
    }
}
