#ifndef DATEMETHODS_H
#define DATEMETHODS_H

#include <string>
#include <map>

#include <ctime>
#include <iomanip>
#include <sstream>

using namespace std;

class DateMethods
{
public:

    static void calculateCurrentDate(map<string, int>& currentDate);
    static bool isYearLeap(int year);
    static bool validateDate(const string& dateAsString);
    static int convertStringDateToInt(const string& date);
    static string convertIntDateToStringWithDashes(int date);
    static string getCurrentDateAsString();
    static int getDaysInMonth(int year, int month);

    static int getCurrentMonthFirstDayDate();
    static int getCurrentMonthLastDayDate();
    static int getPreviousMonthLastDayDate();
    static int getPreviousMonthFirstDayDate();

};


#endif
