#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

#include "OperationFile.h"
#include "Markup.h"

using namespace std;

OperationFile::OperationFile(const string& fileName) : fileName(fileName) {}

vector<Operation> OperationFile::loadOperationsFromFile(int loggedUserId)
{
    vector<Operation> operations;
    CMarkup xml;

    if (xml.Load(fileName))
    {
        if (xml.FindElem("Root"))
        {
            xml.IntoElem();
            while (xml.FindElem("Operation"))
            {
                xml.IntoElem();
                Operation operation;
                xml.FindElem("Id");
                operation.id = stoi(xml.GetData());
                xml.FindElem("UserId");
                operation.userId = stoi(xml.GetData());
                xml.FindElem("Date");
                operation.date = stoi(xml.GetData());
                xml.FindElem("Item");
                operation.item = xml.GetData();
                xml.FindElem("Amount");
                operation.amount = stod(xml.GetData());
                xml.FindElem("Type");
                operation.type = static_cast<Type>(stoi(xml.GetData()));

                if (operation.userId == loggedUserId)
                {
                    operations.push_back(operation);
                }
                xml.OutOfElem();
            }
        }
    }

    return operations;
}

bool OperationFile::addOperationToFile(const Operation& operation)
{
    CMarkup xml;
    bool fileLoaded = xml.Load(fileName);

    if (!fileLoaded)
    {
        xml.AddElem("Root");
        xml.IntoElem();
    }
    else
    {
        xml.FindElem("Root");
        xml.IntoElem();
    }

    int lastId = 0;

    while (xml.FindElem("Operation"))
    {
        xml.IntoElem();
        if (xml.FindElem("Id"))
        {
            lastId = stoi(xml.GetData());
        }
        xml.OutOfElem();
    }

    int newId = lastId + 1;

    xml.AddElem("Operation");
    xml.IntoElem();
    xml.AddElem("Id", to_string(newId));
    xml.AddElem("UserId", to_string(operation.userId));
    xml.AddElem("Date", to_string(operation.date));
    xml.AddElem("Item", operation.item);
    xml.AddElem("Amount", to_string(operation.amount));
    xml.AddElem("Type", to_string(operation.type));

    xml.OutOfElem();
    xml.OutOfElem();

    return xml.Save(fileName);
}


int OperationFile::getLastOperationIdFromFile() {
    CMarkup xml;
    int lastId = 0;

    if (xml.Load(fileName)) {
        xml.FindElem("Root");
        xml.IntoElem();

        while (xml.FindElem("Operation")) {
            xml.FindChildElem("Id");
            int currentId = stoi(xml.GetChildData());
            lastId = max(lastId, currentId);
        }
    }

    return lastId;
}

int OperationFile::generateNewOperationId() {
    return getLastOperationIdFromFile() + 1;
}
void OperationFile::saveOperationToFile(Operation& newOperation, const string& fileName)
{
    CMarkup xml;
    bool fileExists = xml.Load(fileName);

    if (!fileExists)
    {

        xml.SetDoc("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n");
        xml.AddElem("Root");
    }

    xml.FindElem("Root");
    xml.IntoElem();

    xml.AddElem("Operation");
    xml.IntoElem();
    xml.AddElem("Id", to_string(newOperation.id));
    xml.AddElem("UserId", to_string(newOperation.userId));
    xml.AddElem("Date", to_string(newOperation.date));
    xml.AddElem("Item", newOperation.item);

    stringstream ss;
    ss << fixed << setprecision(2) << newOperation.amount;
    xml.AddElem("Amount", ss.str());
    xml.OutOfElem();

    xml.Save(fileName);
}

