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

using namespace aid;

Date::Date() {
    
    this->errCode = NO_ERROR;
    this->day = 0;
    this->month = 0;
    this->year = 0;
    this->timestamp = 0;
}   

Date::Date(int year, int month, int day) {



}

Date::~Date() {
}


// Private functions

void Date::setEmptyState() {

    this->errCode = NO_ERROR;
    this->day = 0;
    this->month = 0;
    this->year = 0;
    this->timestamp = 0;

}

int Date::mdays(int year, int mon) const {
    int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
    int month = mon >= 1 && mon <= 12 ? mon : 13;
    month--;
    return days[month] + int((month == 1)*((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
}
