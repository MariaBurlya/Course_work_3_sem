#ifndef DATE_H
#define DATE_H

#include <string>

class Date {
private:
    int day;
    int month;
    int year;

    bool isLeapYear(int y) const;
    int daysInMonth(int m, int y) const;
    bool isValidDate(int d, int m, int y) const;
    int toDays() const;
    void fromDays(int days);

public:
    Date();
    Date(int d, int m, int y);
    
    bool isValid() const;
    std::string toString() const;
    
    static Date today();
    static bool checkLeapYear(int y);
    
    Date operator+(int days) const;
    Date operator-(int days) const;
    Date& operator+=(int days);
    Date& operator-=(int days);
    
    Date& operator++();
    Date operator++(int);
    Date& operator--();
    Date operator--(int);
    
    bool operator<(const Date& other) const;
    bool operator==(const Date& other) const;
    
    int operator-(const Date& other) const;
};

#endif // DATE_H
