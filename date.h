#ifndef __DATE_H
#define __DATE_H

#include <string>
#include <iostream>
#include <iomanip>

class Date {

    public:
        Date(int month, int day, int year, int hour, int minute, std::string AmPm);
        int month() const;
        int day() const;
        int year() const;
        int hour() const;
        int minute() const;
        std::string AmPm();
        friend std::ostream& operator<<(std::ostream& ost, const Date& date);
        bool operator<(Date& rhs);

    private:
        int _month;
        int _day;
        int _year;
        int _hour;
        int _minute;
        std::string _AmPm;

};


#endif