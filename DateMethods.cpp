#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <regex>
#include <map>

#include "DateMethods.h"

using namespace std;

void DateMethods::calculateCurrentDate(map<string, int>& currentDate)
{
    time_t now = time(0);
    tm *ltm = localtime(&now);

    currentDate["year"] = 1900 + ltm->tm_year;
    currentDate["month"] = 1 + ltm->tm_mon;
    currentDate["day"] = ltm->tm_mday;
}

bool DateMethods::isYearLeap(int year)
{
    return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}

bool DateMethods::validateDate(const string& date)

{
    regex datePattern(R"(^\d{4}-(0[1-9]|1[0-2])-(0[1-9]|[12]\d|3[01])$)");

    if (!regex_match(date, datePattern))
    {
        return false;
    }

    int year = stoi(date.substr(0, 4));
    int month = stoi(date.substr(5, 2));
    int day = stoi(date.substr(8, 2));

    return day <=  DateMethods::getDaysInMonth(year, month);
}
int DateMethods::getDaysInMonth(int year, int month)
{
    switch (month)
    {
    case 2:
        return isYearLeap(year) ? 29 : 28;
    case 4:
    case 6:
    case 9:
    case 11:
        return 30;
    default:
        return 31;
    }
}


int DateMethods::convertStringDateToInt(const string& dateAsString)
{
    return stoi(dateAsString.substr(0, 4) + dateAsString.substr(5, 2) + dateAsString.substr(8, 2));
}

string DateMethods::convertIntDateToStringWithDashes(int date)
{
    stringstream ss;
    ss << setw(4) << setfill('0') << date / 10000 << "-"
       << setw(2) << setfill('0') << (date / 100) % 100 << "-"
       << setw(2) << setfill('0') << date % 100;
    return ss.str();
}


string DateMethods::getCurrentDateAsString()
{
    time_t t = time(nullptr);
    tm* timePtr = localtime(&t);

    ostringstream oss;
    oss << (timePtr->tm_year + 1900) << '-'
        << setw(2) << setfill('0') << (timePtr->tm_mon + 1) << '-'
        << setw(2) << setfill('0') << timePtr->tm_mday;

    return oss.str();
}
int DateMethods::getCurrentMonthFirstDayDate()
{
    map<string, int> currentDate;
    calculateCurrentDate(currentDate);
    return currentDate["year"] * 10000 + currentDate["month"] * 100 + 1;
}

int DateMethods::getCurrentMonthLastDayDate()
{
    map<string, int> currentDate;
    calculateCurrentDate(currentDate);

    int year = currentDate["year"];
    int month = currentDate["month"];


    int lastDay;
    if (month == 2)
    {
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        {
            lastDay = 29;
        }
        else
        {
            lastDay = 28;
        }
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        lastDay = 30;
    }
    else
    {
        lastDay = 31;
    }


    return year * 10000 + month * 100 + lastDay;
}
int DateMethods::getPreviousMonthLastDayDate()
{
    map<string, int> currentDate;
    calculateCurrentDate(currentDate);

    int year = currentDate["year"];
    int month = currentDate["month"];
    if (month == 1)
    {
        year--;
        month = 12;
    }
    else
    {
        month--;
    }

    const int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if (isYearLeap(year) && month == 2)
        return year * 10000 + month * 100 + 29;

    return year * 10000 + month * 100 + daysInMonth[month - 1];
}

int DateMethods::getPreviousMonthFirstDayDate()
{
    map<string, int> currentDate;
    calculateCurrentDate(currentDate);

    int year = currentDate["year"];
    int month = currentDate["month"];
    if (month == 1)
    {
        year--;
        month = 12;
    }
    else
    {
        month--;
    }

    return year * 10000 + month * 100 + 1;
}

