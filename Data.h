#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <stdexcept>
#include <string>

class Date {
private:
    int day;
    int month;
    int year;

    // Вспомогательные приватные методы
    bool isLeapYear(int y) const;
    int daysInMonth(int m, int y) const;
    bool isValidDate(int d, int m, int y) const;
    void normalize();
    int toDays() const;
    void fromDays(int days);

public:
    // Конструкторы
    Date();                       // Текущая дата
    Date(int d, int m, int y);    // Конкретная дата
    Date(const Date& other);      // Копирование
    
    // Геттеры
    int getDay() const;
    int getMonth() const;
    int getYear() const;
    
    // Сеттеры
    void setDate(int d, int m, int y);
    
    // Проверка корректности
    bool isValid() const;
    
    // Вывод
    void print() const;
    std::string toString() const;
    
    // Статические методы
    static Date today();
    static bool checkLeapYear(int y);
    
    // === ПЕРЕГРУЖЕННЫЕ ОПЕРАТОРЫ ===
    
    // 1. Оператор присваивания
    Date& operator=(const Date& other);
    
    // 2. Арифметические
    Date operator+(int days) const;
    Date operator-(int days) const;
    Date& operator+=(int days);
    Date& operator-=(int days);
    
    // 3. Унарные
    Date& operator++();       // Префиксный ++
    Date operator++(int);     // Постфиксный ++
    Date& operator--();       // Префиксный --
    Date operator--(int);     // Постфиксный --
    
    // 4. Сравнение
    bool operator<(const Date& other) const;
    bool operator>(const Date& other) const;
    bool operator<=(const Date& other) const;
    bool operator>=(const Date& other) const;
    bool operator==(const Date& other) const;
    bool operator!=(const Date& other) const;
    
    // 5. Разность дат
    int operator-(const Date& other) const;
    
    // 6. Доступ по индексу
    int operator[](int index) const;
    
    // 7. Преобразование
    operator std::string() const;
};

#endif // DATE_H
