// реализация методов, определение функций и глобальных переменных

#include "data.h"
#include <ctime>
#include <sstream>
#include <iomanip>

using namespace std;


bool Date::isLeapYear(int y) const {
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

int Date::daysInMonth(int m, int y) const {
    static const int days[] = {31, 28, 31, 30, 31, 30, 
                               31, 31, 30, 31, 30, 31};
    if (m == 2 && isLeapYear(y)) {
        return 29;
    }
    if (m < 1 || m > 12) {
        return 0;
    }
    return days[m - 1];
}

void Date::validate() const {
    if (year < 1) {
        throw out_of_range("Год должен быть положительным числом");
    }
    if (month < 1 || month > 12) {
        throw out_of_range("Месяц должен быть от 1 до 12");
    }
    if (day < 1 || day > daysInMonth(month, year)) {
        throw out_of_range("Некорректный день для данного месяца и года");
    }
}

void Date::normalize() {
    // Приводим дату к корректному виду
    while (month > 12) {
        month -= 12;
        year++;
    }
    while (month < 1) {
        month += 12;
        year--;
    }
    
    while (day > daysInMonth(month, year)) {
        day -= daysInMonth(month, year);
        month++;
        if (month > 12) {
            month = 1;
            year++;
        }
    }
    
    while (day < 1) {
        month--;
        if (month < 1) {
            month = 12;
            year--;
        }
        day += daysInMonth(month, year);
    }
    
    if (year < 1) {
        year = 1;
    }
}

int Date::toDays() const {
    // Преобразование даты в количество дней с 01.01.0001
    int total = 0;
    
    // Дни за полные годы
    for (int y = 1; y < year; y++) {
        total += isLeapYear(y) ? 366 : 365;
    }
    
    // Дни за полные месяцы текущего года
    for (int m = 1; m < month; m++) {
        total += daysInMonth(m, year);
    }
    
    // Дни текущего месяца
    total += day;
    
    return total;
}

Date Date::fromDays(int days) {
    if (days < 1) days = 1;
    
    Date result(1, 1, 1);
    result.day = days;
    result.normalize();
    return result;
}

// ----- Конструкторы и деструктор -----

Date::Date() : day(1), month(1), year(2000) {
    // Конструктор по умолчанию устанавливает 01.01.2000
}

Date::Date(int d, int m, int y) : day(d), month(m), year(y) {
    validate();
}

Date::Date(const Date& other) : day(other.day), month(other.month), year(other.year) {
    // Конструктор копирования
}

Date::~Date() {
    // Деструктор - ничего особенного не делаем
    // Но он должен быть согласно требованиям
}

// ----- Методы вывода -----

void Date::print() const {
    cout << setfill('0') << setw(2) << day << "."
         << setw(2) << month << "." << setw(4) << year;
}

string Date::toString() const {
    stringstream ss;
    ss << setfill('0') << setw(2) << day << "."
       << setw(2) << month << "." << setw(4) << year;
    return ss.str();
}

// ----- Оператор присваивания -----

Date& Date::operator=(const Date& other) {
    if (this != &other) {
        day = other.day;
        month = other.month;
        year = other.year;
    }
    return *this;
}

// ----- Бинарные арифметические операторы -----

Date Date::operator+(int days) const {
    Date result = *this;
    result.day += days;
    result.normalize();
    return result;
}

Date Date::operator-(int days) const {
    return *this + (-days);
}

Date operator+(int days, const Date& date) {
    return date + days;  // используем уже реализованный оператор
}

// ----- Арифметика с накоплением -----

Date& Date::operator+=(int days) {
    day += days;
    normalize();
    return *this;
}

Date& Date::operator-=(int days) {
    return *this += (-days);
}

// ----- Унарные операторы -----

Date& Date::operator++() {
    *this += 1;
    return *this;
}

Date Date::operator++(int) {
    Date temp = *this;
    ++(*this);
    return temp;
}

Date& Date::operator--() {
    *this -= 1;
    return *this;
}

Date Date::operator--(int) {
    Date temp = *this;
    --(*this);
    return temp;
}

// ----- Логические операторы -----

bool Date::operator==(const Date& other) const {
    return day == other.day && month == other.month && year == other.year;
}

bool Date::operator!=(const Date& other) const {
    return !(*this == other);
}

bool Date::operator<(const Date& other) const {
    if (year != other.year) return year < other.year;
    if (month != other.month) return month < other.month;
    return day < other.day;
}

bool Date::operator>(const Date& other) const {
    return other < *this;
}

bool Date::operator<=(const Date& other) const {
    return !(*this > other);
}

bool Date::operator>=(const Date& other) const {
    return !(*this < other);
}

// ----- Операторы взятия элемента -----

int& Date::operator[](int index) {
    switch(index) {
        case 0: return day;
        case 1: return month;
        case 2: return year;
        default: throw out_of_range("Индекс должен быть 0, 1 или 2 (день, месяц, год)");
    }
}

const int& Date::operator[](int index) const {
    switch(index) {
        case 0: return day;
        case 1: return month;
        case 2: return year;
        default: throw out_of_range("Индекс должен быть 0, 1 или 2 (день, месяц, год)");
    }
}

// ----- Операторы преобразования типа -----

Date::operator string() const {
    return toString();
}

Date::operator int() const {
    // Количество дней с 01.01.1970 (Unix epoch)
    Date epoch(1, 1, 1970);
    return this->toDays() - epoch.toDays();
}

// ----- Дополнительные методы -----

int Date::daysBetween(const Date& other) const {
    return abs(this->toDays() - other.toDays());
}

int Date::dayOfWeek() const {
    // Алгоритм Зеллера для расчета дня недели
    int d = day;
    int m = month;
    int y = year;
    
    if (m < 3) {
        m += 12;
        y--;
    }
    
    int k = y % 100;
    int j = y / 100;
    
    int h = (d + 13*(m+1)/5 + k + k/4 + j/4 + 5*j) % 7;
    
    // 0=суббота, 1=воскресенье, 2=понедельник...
    return (h + 5) % 7;  // чтобы 0=воскресенье
}

// ----- Статические методы -----

Date Date::today() {
    time_t now = time(nullptr);
    tm* local = localtime(&now);
    return Date(local->tm_mday, local->tm_mon + 1, local->tm_year + 1900);
}

bool Date::isValidDate(int d, int m, int y) {
    try {
        Date temp(d, m, y);
        return true;
    } catch (const exception&) {
        return false;
    }
}
