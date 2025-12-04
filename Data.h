// объявления классов, структур, прототипы функций, extern переменные

#ifndef DATA_H
#define DATA_H

#include <iostream>
#include <stdexcept>  // для исключений
#include <string>

using namespace std;

class Date {
private:
    int day;
    int month;
    int year;
    
    // Вспомогательные методы
    bool isLeapYear(int y) const;
    int daysInMonth(int m, int y) const;
    void validate() const;
    void normalize();
    
public:
    // Конструкторы (требование задания)
    Date();                           // по умолчанию
    Date(int d, int m, int y);        // с параметрами
    Date(const Date& other);          // копирования
    
    // Деструктор (требование задания)
    ~Date();
    
    // Функция вывода на экран (требование задания)
    void print() const;
    string toString() const;
    
    // Оператор присваивания (требование задания)
    Date& operator=(const Date& other);
    
    // Бинарные арифметические операторы (требование задания)
    Date operator+(int days) const;        // Date + int
    Date operator-(int days) const;        // Date - int
    friend Date operator+(int days, const Date& date); // int + Date
    
    // Арифметика с накоплением (требование задания)
    Date& operator+=(int days);
    Date& operator-=(int days);
    
    // Унарные операторы (требование задания)
    Date& operator++();     // префиксный ++
    Date operator++(int);   // постфиксный ++
    Date& operator--();     // префиксный --
    Date operator--(int);   // постфиксный --
    
    // Логические операторы (требование задания)
    bool operator==(const Date& other) const;
    bool operator!=(const Date& other) const;
    bool operator<(const Date& other) const;
    bool operator>(const Date& other) const;
    bool operator<=(const Date& other) const;
    bool operator>=(const Date& other) const;
    
    // Операторы взятия элемента (требование задания)
    int& operator[](int index);               // для изменения
    const int& operator[](int index) const;   // для чтения
    
    // Операторы преобразования типа (требование задания)
    operator string() const;      // к строке
    operator int() const;              // к int (дней с 01.01.1970)
    
    // Дополнительные методы
    int daysBetween(const Date& other) const;
    int dayOfWeek() const;  // 0-воскресенье, 1-понедельник...
    
    // Геттеры
    int getDay() const { return day; }
    int getMonth() const { return month; }
    int getYear() const { return year; }
    
    // Статические методы
    static Date today();
    static bool isValidDate(int d, int m, int y);
    
private:
    // Вспомогательный метод для преобразования в дни
    int toDays() const;
    static Date fromDays(int days);
};

#endif // DATA_H
