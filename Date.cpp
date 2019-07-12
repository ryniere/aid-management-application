/* -------------------------------
 Name: Ryniere dos Santos Silva
 Student number: 138888185
 Email: rdos-santos-silva@mysenca.ca
 Section: SBB
 Date: 06/24/2019
 ----------------------------------
 Assignment: 1
 ---------------------------------------------------------------------*/

#include "Date.h"
#include <iomanip>

using namespace aid;
using namespace std;

Date::Date()
{
    this->setEmptyState();
}

Date::Date(int year, int month, int day)
{
    this->setDate(year, month, day);
}

Date::~Date()
{
}

// Public functions

int Date::errCode() const
{
    return this->errorState;
}

bool Date::bad() const
{
    return this->errorState != NO_ERROR;
}

std::istream &Date::read(std::istream &istr)
{
    if (istr.fail())
    {
        this->errCode(CIN_FAILED);
        this->setEmptyState();
    }
    else
    {
        string dateString;

        istr >> dateString;

        if (!parseDate(dateString, "/"))
        {

            if (!parseDate(dateString, "-"))
            {
                this->errCode(CIN_FAILED);
                this->setEmptyState();
            }   
        }
    }

    return istr;
}

std::ostream &Date::write(std::ostream &ostr) const
{
    ostr << setw(4) << setfill('0') << this->year << "/" << setw(2) << setfill('0') << this->month << "/" << setw(2) << setfill('0') << this->day;

    return ostr;
}

// Overloaded operators

bool Date::operator==(const Date &rhs) const
{
    return this->timestamp == rhs.timestamp;
}

bool Date::operator!=(const Date &rhs) const
{
    return this->timestamp != rhs.timestamp;
}

bool Date::operator<(const Date &rhs) const
{
    return this->timestamp < rhs.timestamp;
}

bool Date::operator>(const Date &rhs) const
{
    return this->timestamp > rhs.timestamp;
}

bool Date::operator<=(const Date &rhs) const
{
    return this->timestamp <= rhs.timestamp;
}

bool Date::operator>=(const Date &rhs) const
{
    return this->timestamp >= rhs.timestamp;
}

// Private functions

void Date::setEmptyState()
{
    this->day = 0;
    this->month = 0;
    this->year = 0;
    this->timestamp = 0;
}

void Date::errCode(int errorCode)
{
    this->errorState = errorCode;
}

int Date::mdays(int year, int mon) const
{
    int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1};
    int month = mon >= 1 && mon <= 12 ? mon : 13;
    month--;
    return days[month] + int((month == 1) * ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
}

void Date::setDate(int year, int month, int day) {

     if (year < min_year || year > max_year)
    {
        this->errCode(YEAR_ERROR);
        this->setEmptyState();
    }
    else if (month < 1 || month > 12)
    {
        this->errCode(MON_ERROR);
        this->setEmptyState();
    }
    else if (day > this->mdays(year, month))
    {
        this->errCode(DAY_ERROR);
        this->setEmptyState();
    }
    else
    {
        this->timestamp = year * 372 + month * 31 + day;
        if (this->timestamp >= min_date)
        {
            this->errCode(NO_ERROR);
            this->year = year;
            this->month = month;
            this->day = day;
        }
        else
        {
            this->errCode(PAST_ERROR);
            this->setEmptyState();
        }
    }
}

bool Date::parseDate(string dateString, string delimiter)
{
    bool isValid = false;
    vector<string> v1 = split(dateString, delimiter);

    if (v1.size() == 3)
    {
        try
        {
            int year = stoi(v1.at(0));
            int month = stoi(v1.at(1));
            int day = stoi(v1.at(2));

            this->setDate(year, month, day);

            isValid = true;
        }
        catch (const std::exception &e)
        {
        }
    }

    return isValid;
}

// Helper Functions

std::ostream &operator<<(std::ostream &output, const Date &date)
{
    date.write(output);
    return output;
}

std::istream &operator>>(std::istream &input, Date &date)
{
    date.read(input);
    return input;
}

std::vector<string> split(string value, string delimiter)
{
    vector<string> v;
    size_t pos = 0;
    while ((pos = value.find(delimiter)) != string::npos)
    {
        v.push_back(value.substr(0, pos));
        value.erase(0, pos + delimiter.length());
    }
    v.push_back(value);

    return v;
}

