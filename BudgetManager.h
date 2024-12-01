#ifndef BUDGETMANAGER_H
#define BUDGETMANAGER_H

#include <string>
#include <vector>

using namespace std;

class BudgetManager
{
private:
    int loggedUserId;
    string incomeFileName;
    string expenseFileName;


public:
    BudgetManager();
    BudgetManager(const string& incomeFileName, const string& expenseFileName, int userId);
    void addIncome();
    void addExpense();
    void showCurrentMonthBalance();
    void showPreviousMonthBalance();
    void showCustomPeriodBalance();
};

#endif

