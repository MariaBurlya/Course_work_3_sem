#include "Data.h"
#include <ctime>
#include <sstream>
#include <iomanip>

using namespace std;

// ==================== ПРИВАТНЫЕ МЕТОДЫ ====================

// Проверка високосного года
bool Date::isLeapYear(int y) const {
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

// Количество дней в месяце
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

// Проверка корректности даты
bool Date::isValidDate(int d, int m, int y) const {
    if (y < 0 || y > 9999) return false;
    if (m < 1 || m > 12) return false;
    if (d < 1 || d > daysInMonth(m, y)) return false;
    return true;
}

// Нормализация даты (исправление некорректных значений)
void Date::normalize() {
    // Если год отрицательный - делаем положительным
    if (year < 0) year = -year;
    
    // Корректировка месяцев > 12
    while (month > 12) {
        month -= 12;
        year++;
    }
    while (month < 1) {
        month += 12;
        year--;
    }
    
    // Корректировка дней
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
}

// Конвертация в дни от 01.01.0000
int Date::toDays() const {
    int y = year;
    int m = month;
    int d = day;
    
    // Учитываем годы
    int totalDays = y * 365 + y / 4 - y / 100 + y / 400;
    
    // Добавляем дни за месяцы текущего года
    for (int i = 1; i < m; i++) {
        totalDays += daysInMonth(i, y);
    }
    
    // Добавляем дни
    totalDays += d - 1;  // -1 потому что 01.01 считается как 0 дней
    
    return totalDays;
}

// Конвертация из дней в дату
void Date::fromDays(int days) {
    // Начальная дата: 1 января 0 года
    year = 0;
    
    // Определяем год
    while (days >= (isLeapYear(year) ? 366 : 365)) {
        days -= isLeapYear(year) ? 366 : 365;
        year++;
    }
    
    // Определяем месяц
    month = 1;
    while (days >= daysInMonth(month, year)) {
        days -= daysInMonth(month, year);
        month++;
    }
    
    // Определяем день
    day = days + 1;  // +1 потому что days отсчитывается с 0
}

// ==================== ПУБЛИЧНЫЕ МЕТОДЫ ====================

// Конструктор по умолчанию (текущая дата)
Date::Date() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    year = 1900 + ltm->tm_year;
    month = 1 + ltm->tm_mon;
    day = ltm->tm_mday;
}

// Конструктор с параметрами
Date::Date(int d, int m, int y) : day(d), month(m), year(y) {
    if (!isValidDate(d, m, y)) {
        throw invalid_argument("Некорректная дата!");
    }
}

// Конструктор копирования
Date::Date(const Date& other) : day(other.day), month(other.month), year(other.year) {}

// Геттеры
int Date::getDay() const { return day; }
int Date::getMonth() const { return month; }
int Date::getYear() const { return year; }

// Сеттер
void Date::setDate(int d, int m, int y) {
    if (!isValidDate(d, m, y)) {
        throw invalid_argument("Некорректная дата!");
    }
    day = d;
    month = m;
    year = y;
}

// Проверка корректности текущей даты
bool Date::isValid() const {
    return isValidDate(day, month, year);
}

// Вывод даты
void Date::print() const {
    cout << toString();
}

// Преобразование в строку
string Date::toString() const {
    ostringstream oss;
    oss << setw(2) << setfill('0') << day << "."
        << setw(2) << setfill('0') << month << "."
        << setw(4) << setfill('0') << year;
    return oss.str();
}

// Текущая дата
Date Date::today() {
    return Date();  // Используем конструктор по умолчанию
}

// Статическая проверка високосного года
bool Date::checkLeapYear(int y) {
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

// ==================== ПЕРЕГРУЖЕННЫЕ ОПЕРАТОРЫ ====================

// Оператор присваивания
Date& Date::operator=(const Date& other) {
    if (this != &other) {
        day = other.day;
        month = other.month;
        year = other.year;
    }
    return *this;
}

// Сложение с днями
Date Date::operator+(int days) const {
    Date result = *this;
    result.fromDays(result.toDays() + days);
    return result;
}

// Вычитание дней
Date Date::operator-(int days) const {
    Date result = *this;
    result.fromDays(result.toDays() - days);
    return result;
}

// Сложение с накоплением
Date& Date::operator+=(int days) {
    fromDays(toDays() + days);
    return *this;
}

// Вычитание с накоплением
Date& Date::operator-=(int days) {
    fromDays(toDays() - days);
    return *this;
}

// Префиксный инкремент (++date)
Date& Date::operator++() {
    *this += 1;
    return *this;
}

// Постфиксный инкремент (date++)
Date Date::operator++(int) {
    Date temp = *this;
    *this += 1;
    return temp;
}

// Префиксный декремент (--date)
Date& Date::operator--() {
    *this -= 1;
    return *this;
}

// Постфиксный декремент (date--)
Date Date::operator--(int) {
    Date temp = *this;
    *this -= 1;
    return temp;
}

// Операторы сравнения
bool Date::operator<(const Date& other) const {
    return toDays() < other.toDays();
}

bool Date::operator>(const Date& other) const {
    return toDays() > other.toDays();
}

bool Date::operator<=(const Date& other) const {
    return toDays() <= other.toDays();
}

bool Date::operator>=(const Date& other) const {
    return toDays() >= other.toDays();
}

bool Date::operator==(const Date& other) const {
    return toDays() == other.toDays();
}

bool Date::operator!=(const Date& other) const {
    return toDays() != other.toDays();
}

// Разность между датами
int Date::operator-(const Date& other) const {
    return toDays() - other.toDays();
}

// Доступ по индексу [0]-день, [1]-месяц, [2]-год
int Date::operator[](int index) const {
    switch(index) {
        case 0: return day;
        case 1: return month;
        case 2: return year;
        default:
            throw out_of_range("Индекс должен быть 0, 1 или 2");
    }
}

// Преобразование в строку
Date::operator std::string() const {
    return toString();
}
