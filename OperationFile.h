#ifndef OPERATIONFILE_H
#define OPERATIONFILE_H

#include "Operation.h"
#include "Markup.h"
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class OperationFile
{
private:
    string fileName;

public:
    OperationFile(const string& fileName);

    vector<Operation> loadOperationsFromFile(int loggedUserId);
    bool addOperationToFile(const Operation& operation);
    int getLastOperationIdFromFile();
    int getLastOperationId();
    int generateNewOperationId();
    void saveOperationToFile(Operation& newOperation, const string& fileName);

};

#endif
