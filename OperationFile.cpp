#include "OperationFile.h"

using namespace std;

OperationFile::OperationFile(const string& fileName) : fileName(fileName) {}

vector<Operation> OperationFile::loadOperationsFromFile(int loggedUserId)
{
    vector<Operation> operations;
    CMarkup xml;

    if (!xml.Load(fileName))
        return operations;

    xml.FindElem("Operations");
    xml.IntoElem();

    while (xml.FindElem("Operation"))
    {
        Operation operation;
        xml.IntoElem();

        if (xml.FindElem("UserId") && stoi(xml.GetData()) == loggedUserId)
        {
            if (xml.FindElem("Id")) operation.id = stoi(xml.GetData());
            if (xml.FindElem("Date")) operation.date = stoi(xml.GetData());
            if (xml.FindElem("Item")) operation.item = xml.GetData();
            if (xml.FindElem("Amount")) operation.amount = stod(xml.GetData());
            operations.push_back(operation);
        }
        xml.OutOfElem();
    }

    return operations;
}

bool OperationFile::addOperationToFile(const Operation& operation)
{
    CMarkup xml;
    if (!xml.Load(fileName))
    {
        xml.AddElem("Operations");
    }

    xml.FindElem();
    xml.IntoElem();
    xml.AddElem("Operation");
    xml.IntoElem();
    xml.AddElem("Id", operation.id);
    xml.AddElem("UserId", operation.userId);
    xml.AddElem("Date", operation.date);
    xml.AddElem("Item", operation.item);
    xml.AddElem("Amount", operation.amount);
    xml.OutOfElem();

    return xml.Save(fileName);
}
