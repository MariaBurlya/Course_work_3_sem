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
    bool checkLeapYear(int y) const;  // Внутренний метод
    int daysInMonth(int m, int y) const;
    void normalize();
    int toDays() const;
    void fromDays(int days);

public:
    // Конструкторы
    Date();
    Date(int d, int m, int y);
    Date(const Date& other);
    
    // Деструктор
    ~Date() = default;
    
    // Геттеры
    int getDay() const;
    int getMonth() const;
    int getYear() const;
    
    // Сеттеры с проверкой
    void setDay(int d);
    void setMonth(int m);
    void setYear(int y);
    
    // Проверка корректности даты
    bool isValid() const;
    
    // Функция вывода на экран
    void print() const;
    
    // Статический метод для получения текущей даты
    static Date today();
    
    // Статический метод проверки високосного года
    static bool isLeapYear(int y);
    
    // Перегруженные операторы
    
    // 1. Оператор присваивания
    Date& operator=(const Date& other);
    
    // 2. Бинарные арифметические операторы
    Date operator+(int days) const;
    Date operator-(int days) const;
    friend Date operator+(int days, const Date& date);
    
    // 3. Арифметика с накоплением
    Date& operator+=(int days);
    Date& operator-=(int days);
    
    // 4. Унарные операторы
    Date& operator++();
    Date operator++(int);
    Date& operator--();
    Date operator--(int);
    
    // 5. Логические операторы
    bool operator<(const Date& other) const;
    bool operator>(const Date& other) const;
    bool operator<=(const Date& other) const;
    bool operator>=(const Date& other) const;
    bool operator==(const Date& other) const;
    bool operator!=(const Date& other) const;
    
    // 6. Оператор взятия элемента []
    int operator[](int index) const;
    
    // 7. Операторы преобразования типа
    operator int() const;
    operator std::string() const;
    
    // Дополнительные методы
    int daysBetween(const Date& other) const;
};

#endif // DATE_H
