#pragma once

#ifndef OPERATION_H
#define OPERATION_H

#include <string>
#include "Type.h"

using namespace std;

struct Operation
{
    int id;
    int userId;
    int date;
    string item;
    double amount;

     Type type;

    Operation(int id = 0, int userId = 0, int date = 0, const string& item = "", double amount = 0.0)
        : id(id), userId(userId), date(date), item(item), amount(amount) {}
};

#endif
