#ifndef DATE_H
#define DATE_H

#include <string>
#include <stdexcept>

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
    
    // Метод для вывода
    std::string toString() const;
    
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
    
    // Инкремент/декремент 
    Date& operator++();      
    Date operator++(int);   
    Date& operator--();     
    Date operator--(int);    

    bool operator<(const Date& other) const;   
    bool operator==(const Date& other) const;  
};

#endif 
