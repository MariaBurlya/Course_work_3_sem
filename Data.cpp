#include "Date.h"
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
    int totalDays = 0;
    
    // Дни за полные годы
    for (int i = 0; i < year; i++) {
        totalDays += isLeapYear(i) ? 366 : 365;
    }
    
    // Дни за полные месяцы текущего года
    for (int i = 1; i < month; i++) {
        totalDays += daysInMonth(i, year);
    }
    
    // Дни текущего месяца
    totalDays += day - 1;
    
    return totalDays;
}

void Date::fromDays(int days) {
    if (days < 0) {
        // Обработка отрицательных дней (даты до 01.01.0000)
        days = 0;
    }
    
    // Находим год
    year = 0;
    while (true) {
        int daysInThisYear = isLeapYear(year) ? 366 : 365;
        if (days < daysInThisYear) {
            break;
        }
        days -= daysInThisYear;
        year++;
    }
    
    // Находим месяц
    month = 1;
    while (true) {
        int daysInThisMonth = daysInMonth(month, year);
        if (days < daysInThisMonth) {
            break;
        }
        days -= daysInThisMonth;
        month++;
    }
    
    // Находим день
    day = days + 1; // +1 потому что дни начинаются с 1
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

bool Date::operator>(const Date& other) const {
    return toDays() > other.toDays();
}

bool Date::operator==(const Date& other) const {
    return toDays() == other.toDays();
}

bool Date::operator!=(const Date& other) const {
    return toDays() != other.toDays();
}

bool Date::operator<=(const Date& other) const {
    return toDays() <= other.toDays();
}

bool Date::operator>=(const Date& other) const {
    return toDays() >= other.toDays();
}

int Date::operator-(const Date& other) const {
    return toDays() - other.toDays();
}

// Новые операторы для задания
Date& Date::operator=(const Date& other) {
    if (this != &other) {
        day = other.day;
        month = other.month;
        year = other.year;
    }
    return *this;
}

// Оператор [] для доступа к компонентам даты
int Date::operator[](int index) const {
    switch(index) {
        case 0: return day;
        case 1: return month;
        case 2: return year;
        default: throw out_of_range("Индекс должен быть 0, 1 или 2");
    }
}

// Оператор преобразования в int (количество дней с 01.01.0000)
Date::operator int() const {
    return toDays();
}

// Оператор преобразования в string
Date::operator string() const {
    return toString();
}

// Операторы ввода/вывода (добавьте их в Date.h)
ostream& operator<<(ostream& os, const Date& date) {
    os << date.toString();
    return os;
}

istream& operator>>(istream& is, Date& date) {
    int d, m, y;
    char dot1, dot2;
    
    if (is >> d >> dot1 >> m >> dot2 >> y) {
        if (dot1 == '.' && dot2 == '.') {
            try {
                date = Date(d, m, y);
            } catch (const exception& e) {
                is.setstate(ios::failbit);
            }
        } else {
            is.setstate(ios::failbit);
        }
    }
    return is;
}
