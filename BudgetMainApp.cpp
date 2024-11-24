#include "BudgetMainApp.h"
#include "BudgetManager.h"
#include <iostream>

using namespace std;

BudgetMainApp::BudgetMainApp(const string& userFileName, const string& incomeFileName, const string& expenseFileName)
    : userManager(userFileName), budgetManager(nullptr) {}

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
        //budgetManager = new BudgetManager("incomes.xml", "expenses.xml", userManager.getLoggedUserId());
        userManager.getLoggedUserId();
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
    // Dodanie przychodu
}

void BudgetMainApp::addExpense()
{
    // Dodanie wydatku
}

void BudgetMainApp::showCurrentMonthBalance()
{
    // Wyświetlenie bilansu bieżącego miesiąca
}

void BudgetMainApp::showPreviousMonthBalance()
{
    // Wyświetlenie bilansu poprzedniego miesiąca
}

void BudgetMainApp::showCustomPeriodBalance()
{
    // Wyświetlenie bilansu za niestandardowy okres
}
