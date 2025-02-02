#include <iostream>
#include <vector>
#include <string>
#include <sstream>

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





