#ifndef DATE_H
#define DATE_H

#include <string>
#include <stdexcept>
#include <iostream>

class Date {
private:
    int day;
    int month;
    int year;
    
    // Вспомогательные методы
    bool isLeapYear(int y) const;
    int daysInMonth(int m, int y) const;
    bool isValidDate(int d, int m, int y) const;
    int toDays() const;
    void fromDays(int days);
    
public:
    // Конструкторы
    Date();
    Date(int d, int m, int y);
    
    // Методы доступа
    std::string toString() const;
    bool isValid() const;
    
    // Статические методы
    static Date today();
    static bool checkLeapYear(int y);
    
    // Арифметические операторы
    Date operator+(int days) const;
    Date operator-(int days) const;
    int operator-(const Date& other) const;
    
    // Операторы присваивания
    Date& operator+=(int days);
    Date& operator-=(int days);
    Date& operator=(const Date& other);
    
    // Инкремент/декремент
    Date& operator++();      // префиксный
    Date operator++(int);    // постфиксный
    Date& operator--();      // префиксный
    Date operator--(int);    // постфиксный
    
    // Операторы сравнения
    bool operator<(const Date& other) const;
    bool operator>(const Date& other) const;
    bool operator==(const Date& other) const;
    bool operator!=(const Date& other) const;
    bool operator<=(const Date& other) const;
    bool operator>=(const Date& other) const;
    
    // Оператор взятия элемента []
    int operator[](int index) const;
    
    // Операторы преобразования типа
    operator int() const;
    operator std::string() const;
    
    // Дружественные операторы ввода/вывода
    friend std::ostream& operator<<(std::ostream& os, const Date& date);
    friend std::istream& operator>>(std::istream& is, Date& date);
};

#endif // DATE_H
