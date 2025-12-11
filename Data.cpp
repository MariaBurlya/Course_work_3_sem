#include "Data.h"
#include <ctime>
#include <sstream>
#include <iomanip>
#include <stdexcept>

using namespace std;

bool Date::isLeapYear(int y) const {
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

int Date::daysInMonth(int m, int y) const {
    switch(m) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return 31;
        case 4: case 6: case 9: case 11:
            return 30;
        case 2:
            return isLeapYear(y) ? 29 : 28;
        default:
            return 0;
    }
}

bool Date::isValidDate(int d, int m, int y) const {
    if (y < 0 || y > 9999) return false;
    if (m < 1 || m > 12) return false;
    if (d < 1 || d > daysInMonth(m, y)) return false;
    return true;
}

int Date::toDays() const {
    int y = year;
    int m = month;
    int d = day;
    
    int totalDays = y * 365 + y / 4 - y / 100 + y / 400;
    
    for (int i = 1; i < m; i++) {
        totalDays += daysInMonth(i, y);
    }
    
    totalDays += d - 1;
    return totalDays;
}

void Date::fromDays(int days) {
    year = 0;
    
    while (days >= (isLeapYear(year) ? 366 : 365)) {
        days -= isLeapYear(year) ? 366 : 365;
        year++;
    }
    
    month = 1;
    while (days >= daysInMonth(month, year)) {
        days -= daysInMonth(month, year);
        month++;
    }
    
    day = days + 1;
}

Date::Date() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    year = 1900 + ltm->tm_year;
    month = 1 + ltm->tm_mon;
    day = ltm->tm_mday;
}

Date::Date(int d, int m, int y) : day(d), month(m), year(y) {
    if (!isValidDate(d, m, y)) {
        throw invalid_argument("Некорректная дата!");
    }
}

bool Date::isValid() const {
    return isValidDate(day, month, year);
}

string Date::toString() const {
    ostringstream oss;
    oss << setw(2) << setfill('0') << day << "."
        << setw(2) << setfill('0') << month << "."
        << setw(4) << setfill('0') << year;
    return oss.str();
}

Date Date::today() {
    return Date();
}

bool Date::checkLeapYear(int y) {
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

Date Date::operator+(int days) const {
    Date result = *this;
    result.fromDays(result.toDays() + days);
    return result;
}

Date Date::operator-(int days) const {
    Date result = *this;
    result.fromDays(result.toDays() - days);
    return result;
}

Date& Date::operator+=(int days) {
    fromDays(toDays() + days);
    return *this;
}

Date& Date::operator-=(int days) {
    fromDays(toDays() - days);
    return *this;
}

Date& Date::operator++() {
    *this += 1;
    return *this;
}

Date Date::operator++(int) {
    Date temp = *this;
    *this += 1;
    return temp;
}

Date& Date::operator--() {
    *this -= 1;
    return *this;
}

Date Date::operator--(int) {
    Date temp = *this;
    *this -= 1;
    return temp;
}

bool Date::operator<(const Date& other) const {
    return toDays() < other.toDays();
}

bool Date::operator==(const Date& other) const {
    return toDays() == other.toDays();
}

int Date::operator-(const Date& other) const {
    return toDays() - other.toDays();
}
