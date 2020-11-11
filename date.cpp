#include "date.h"

Date::Date(int month, int day, int year, int hour, int minute, std::string AmPm) 
    : _month{month} , _day{day} , _year{year}, _hour{hour}, _minute{minute}, _AmPm{AmPm} { }

int Date::month() const {
    return _month;
}

int Date::day() const {
    return _day;
}

int Date::year() const {
    return _year;
}

int Date::hour() const {
    return _hour;
}

int Date::minute() const {
    return _minute;
}

std::string Date::AmPm() {
    return _AmPm;
}

std::ostream& operator<<(std::ostream& ost, const Date& date) {
    std::string output = std::to_string(date._month) + '/' + std::to_string(date._day) + '/' + std::to_string(date._year);
    ost << std::setw(10) << output;
    ost << std::setw(2) << std::right << date._hour << ":" << std::setfill('0') << std::setw(2) << std::right << date._minute << " " << date._AmPm << std::setw(5) << std::setfill(' ');
    return ost;
}

bool Date::operator<(Date& rhs) {
    if(this->year() < rhs.year()) {
        return true;
    }
    else if(this->year() > rhs.year()) {
        return false;
    }
    else if (this->month() < rhs.month()) {
        return true;
    }
    else if (this->month() > rhs.month()) {
        return false;
    }
    else if(this->day() < rhs.day()) {
        return true;
    }
    else if((this->AmPm() == "AM" || this->AmPm() == "Am" || this->AmPm() == "aM" || this->AmPm() == "am") && (rhs._AmPm == "PM" || rhs._AmPm == "Pm" || rhs._AmPm == "pM" || rhs._AmPm == "pm")){
        return true;
    }
    else if((this->AmPm() == "PM" || this->AmPm() == "Pm" || this->AmPm() == "pM" || this->AmPm() == "pm") && (rhs._AmPm == "AM" || rhs._AmPm == "Am" || rhs._AmPm == "aM" || rhs._AmPm == "am")) {
        return false;
    }
    else if(this->day() == rhs.day() && this->hour() == 12) {
        return true;
    }
    else if(this->day() > rhs.day()) {
        return false;
    }
    else if(this->day() > rhs.day() && this->hour() < rhs.hour()) {
        return true;
    }
    else if(this->day() > rhs.day() && this->minute() < rhs.minute()) {
        return true;
    }
    else {
        return false;
    }
}