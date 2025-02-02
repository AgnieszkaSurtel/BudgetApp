#ifndef BUDGETMANAGER_H
#define BUDGETMANAGER_H

#include "OperationFile.h"
#include "DateMethods.h"
#include "Markup.h"
#include <vector>
#include <optional>

using namespace std;

class BudgetManager
{
private:
    const int LOGGED_USER_ID;
    int lastUserId;
    OperationFile incomeFile;
    OperationFile expenseFile;
    vector<Operation> incomes;
    vector<Operation> expenses;

    Operation addOperationDetails(Type type);
    void sortOperationsByDate(vector<Operation>& operations);
    double calculateBalance(int startDate, int endDate, const Type& type);


public:
    BudgetManager(const string& incomeFileName, const string& expenseFileName, int loggedUserId);

    int lastUsedId;
    int lastUsedIncomeExpenseId;

    int loadLastUsedId(const string& fileName);
    void addTransaction(Type type);
    string getTransactionDate();
    string getTransactionDescription();
    double getTransactionAmount();
    string formatAmount(double amount);
    int getLastOperationId(CMarkup& xml);

    void saveOperationToFile(Operation& newOperation, const string& fileName);
    void saveLastUsedId(int lastId);
    void addIncome();
    void addExpense();
    void showOperations(const vector<Operation>& operations, int startDate, int endDate);
    void showCurrentMonthBalance();
    void showPreviousMonthBalance();
    void showCustomPeriodBalance();

};
#endif
