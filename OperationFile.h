#ifndef OPERATIONFILE_H
#define OPERATIONFILE_H

#include "Operation.h"
#include "Markup.h"
#include <vector>
#include <string>

using namespace std;

class OperationFile
{
private:
    string fileName;

public:
    OperationFile(const string& fileName);

    vector<Operation> loadOperationsFromFile(int loggedUserId);
    bool addOperationToFile(const Operation& operation);
};

#endif
