
/* -------------------------------
 Name: Ryniere dos Santos Silva
 Student number: 138888185
 Email: rdos-santos-silva@mysenca.ca
 Section: SBB
 Date: 06/24/2019
 ----------------------------------
 Assignment: 1
 ---------------------------------------------------------------------*/

#ifndef NAMESPACE_DATE_H
#define NAMESPACE_DATE_H

namespace aid {

    #define NO_ERROR   0  // No error - the date is valid
    #define CIN_FAILED 1  // istream failed on information entry
    #define DAY_ERROR  2  // Day value is invalid
    #define MON_ERROR  3  // Month value is invalid
    #define EAR_ERROR 4   // Year value is invalid
    #define PAST_ERROR 5  // Date value is invalid

    const int min_year = 2018;
    const int max_year = 2038;
    const int min_date = 751098;

    class Date {
        private:
        /* data */
        int year;
        int month;
        int day;
        int timestamp;
        int errorState;

        void errCode(int errorCode);
        int Date::mdays(int year, int mon) const;
        void setEmptyState();

        public:
            Date();
            Date(int year, int month, int day);
            ~Date();
    };

} // namespace aid

#endif
