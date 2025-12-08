#include "Data.h"
#include <ctime>
#include <sstream>
#include <iomanip>
#include <cmath>

using namespace std;

// ==================== СТАТИЧЕСКИЕ МЕТОДЫ ====================

// Статический метод проверки високосного года
bool Date::isLeapYear(int y) {
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

// Статический метод для получения текущей даты
Date Date::today() {
    time_t now = time(nullptr);
    tm* localTime = localtime(&now);
    return Date(localTime->tm_mday, localTime->tm_mon + 1, localTime->tm_year + 1900);
}

// ==================== ВСПОМОГАТЕЛЬНЫЕ ПРИВАТНЫЕ МЕТОДЫ ====================

// Внутренний метод проверки високосного года
bool Date::checkLeapYear(int y) const {
    return isLeapYear(y);  // Используем статический метод
}

// Количество дней в месяце
int Date::daysInMonth(int m, int y) const {
    static const int days[] = {31, 28, 31, 30, 31, 30, 
                               31, 31, 30, 31, 30, 31};
    if (m == 2 && isLeapYear(y)) {
        return 29;
    }
    if (m < 1 || m > 12) return 0;
    return days[m - 1];
}

// Преобразование даты в количество дней от 01.01.0001
int Date::toDays() const {
    int d = day;
    int m = month;
    int y = year;
    
    // Алгоритм преобразования даты в дни
    m = (m + 9) % 12;
    y = y - m / 10;
    int daysFromYear = 365 * y + y / 4 - y / 100 + y / 400;
    int daysFromMonth = (m * 306 + 5) / 10;
    
    return daysFromYear + daysFromMonth + d - 1;
}

// Преобразование количества дней в дату
void Date::fromDays(int days) {
    // Алгоритм преобразования дней в дату
    int g = days + 365;
    int y = (10000 * g + 14780) / 3652425;
    int ddd = g - (365 * y + y / 4 - y / 100 + y / 400);
    
    if (ddd < 0) {
        y--;
        ddd = g - (365 * y + y / 4 - y / 100 + y / 400);
    }
    
    int mi = (100 * ddd + 52) / 3060;
    int mm = (mi + 2) % 12 + 1;
    y = y + (mi + 2) / 12;
    int dd = ddd - (mi * 306 + 5) / 10 + 1;
    
    day = dd;
    month = mm;
    year = y;
}

// Приведение даты к корректному виду
void Date::normalize() {
    if (!isValid()) {
        int days = this->toDays();
        this->fromDays(days);
    }
}

// ==================== КОНСТРУКТОРЫ И ДЕСТРУКТОР ====================

// Конструктор по умолчанию
Date::Date() : day(1), month(1), year(2000) {}

// Конструктор с параметрами
Date::Date(int d, int m, int y) : day(d), month(m), year(y) {
    if (!isValid()) {
        throw invalid_argument("Некорректная дата!");
    }
}

// Конструктор копирования
Date::Date(const Date& other) : day(other.day), month(other.month), year(other.year) {}

// ==================== ГЕТТЕРЫ И СЕТТЕРЫ ====================

// Геттеры
int Date::getDay() const { return day; }
int Date::getMonth() const { return month; }
int Date::getYear() const { return year; }

// Сеттеры
void Date::setDay(int d) {
    int oldDay = day;
    day = d;
    if (!isValid()) {
        day = oldDay;
        throw invalid_argument("Некорректный день!");
    }
}

void Date::setMonth(int m) {
    int oldMonth = month;
    month = m;
    if (!isValid()) {
        month = oldMonth;
        throw invalid_argument("Некорректный месяц!");
    }
}

void Date::setYear(int y) {
    int oldYear = year;
    year = y;
    if (!isValid()) {
        year = oldYear;
        throw invalid_argument("Некорректный год!");
    }
}

// ==================== ОСНОВНЫЕ МЕТОДЫ ====================

// Проверка корректности даты
bool Date::isValid() const {
    if (year < 1) return false;
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > daysInMonth(month, year)) return false;
    return true;
}

// Вывод даты на экран
void Date::print() const {
    cout << setw(2) << setfill('0') << day << "."
         << setw(2) << setfill('0') << month << "."
         << setw(4) << year;
}

// ==================== ПЕРЕГРУЖЕННЫЕ ОПЕРАТОРЫ ====================

// 1. Оператор присваивания
Date& Date::operator=(const Date& other) {
    if (this != &other) {
        day = other.day;
        month = other.month;
        year = other.year;
    }
    return *this;
}

// 2. Бинарные арифметические операторы

// Дата + число
Date Date::operator+(int days) const {
    Date result(*this);
    result += days;
    return result;
}

// Дата - число
Date Date::operator-(int days) const {
    return *this + (-days);
}

// Дружественная функция: число + Дата
Date operator+(int days, const Date& date) {
    return date + days;
}

// 3. Арифметика с накоплением
Date& Date::operator+=(int days) {
    int currentDays = this->toDays();
    currentDays += days;
    this->fromDays(currentDays);
    return *this;
}

Date& Date::operator-=(int days) {
    return *this += (-days);
}

// 4. Унарные операторы

// Префиксный ++
Date& Date::operator++() {
    *this += 1;
    return *this;
}

// Постфиксный ++
Date Date::operator++(int) {
    Date temp(*this);
    ++(*this);
    return temp;
}

// Префиксный --
Date& Date::operator--() {
    *this -= 1;
    return *this;
}

// Постфиксный --
Date Date::operator--(int) {
    Date temp(*this);
    --(*this);
    return temp;
}

// 5. Логические операторы

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

bool Date::operator==(const Date& other) const {
    return day == other.day && month == other.month && year == other.year;
}

bool Date::operator!=(const Date& other) const {
    return !(*this == other);
}

// 6. Оператор взятия элемента []
int Date::operator[](int index) const {
    switch (index) {
        case 0: return day;
        case 1: return month;
        case 2: return year;
        default: throw out_of_range("Индекс должен быть 0, 1 или 2");
    }
}

// 7. Операторы преобразования типа

// Преобразование в int (количество дней от 01.01.0001)
Date::operator int() const {
    return this->toDays();
}

// Преобразование в string
Date::operator std::string() const {
    stringstream ss;
    ss << setw(2) << setfill('0') << day << "."
       << setw(2) << setfill('0') << month << "."
       << setw(4) << year;
    return ss.str();
}

// ==================== ДОПОЛНИТЕЛЬНЫЕ МЕТОДЫ ====================

// Разница в днях между двумя датами
int Date::daysBetween(const Date& other) const {
    return abs(this->toDays() - other.toDays());
}
