#include "data.cpp"
#include <iostream>
#include <vector>
#include <locale>

using namespace std;

void printHeader(const string& title) {
    cout << "\n=== " << title << " ===" << endl;
}

void testConstructors() {
    printHeader("ТЕСТ КОНСТРУКТОРОВ");
    
    cout << "1. Конструктор по умолчанию: ";
    Date d1;
    d1.print();
    cout << endl;
    
    cout << "2. Конструктор с параметрами (15.07.2023): ";
    Date d2(15, 7, 2023);
    d2.print();
    cout << endl;
    
    cout << "3. Конструктор копирования: ";
    Date d3 = d2;
    d3.print();
    cout << endl;
    
    cout << "4. Попытка создания некорректной даты (31.02.2023): ";
    try {
        Date d4(31, 2, 2023);
        cout << "ОШИБКА: исключение не сгенерировано!" << endl;
    } catch (const exception& e) {
        cout << "Исключение перехвачено: " << e.what() << endl;
    }
}

void testOperators() {
    printHeader("ТЕСТ ОПЕРАТОРОВ");
    
    Date d1(15, 7, 2023);
    Date d2(20, 7, 2023);
    
    cout << "1. Оператор присваивания: ";
    Date d3 = d1;
    d3.print();
    cout << endl;
    
    cout << "2. Оператор + (дата + дни): ";
    Date d4 = d1 + 10;
    d4.print();
    cout << endl;
    
    cout << "3. Оператор - (дата - дни): ";
    Date d5 = d1 - 10;
    d5.print();
    cout << endl;
    
    cout << "4. Оператор + (дни + дата): ";
    Date d6 = 5 + d1;
    d6.print();
    cout << endl;
    
    cout << "5. Оператор +=: ";
    d1 += 5;
    d1.print();
    cout << endl;
    
    cout << "6. Оператор -=: ";
    d1 -= 10;
    d1.print();
    cout << endl;
    
    cout << "7. Префиксный ++: ";
    ++d1;
    d1.print();
    cout << endl;
    
    cout << "8. Постфиксный ++: ";
    d1++.print();
    cout << " (возвращена старая дата: ";
    d1.print();
    cout << " - новая дата)" << endl;
    
    cout << "9. Оператор ==: " << (d1 == d2 ? "true" : "false") << endl;
    cout << "10. Оператор !=: " << (d1 != d2 ? "true" : "false") << endl;
    cout << "11. Оператор <: " << (d1 < d2 ? "true" : "false") << endl;
    cout << "12. Оператор >: " << (d1 > d2 ? "true" : "false") << endl;
}

void testElementAccess() {
    printHeader("ТЕСТ ДОСТУПА К ЭЛЕМЕНТАМ");
    
    Date d(15, 7, 2023);
    
    cout << "Дата: ";
    d.print();
    cout << endl;
    
    cout << "d[0] (день): " << d[0] << endl;
    cout << "d[1] (месяц): " << d[1] << endl;
    cout << "d[2] (год): " << d[2] << endl;
    
    cout << "\nИзменение через оператор []:" << endl;
    d[0] = 20;  // меняем день
    cout << "Новая дата: ";
    d.print();
    cout << endl;
    
    cout << "\nПопытка доступа к несуществующему элементу: ";
    try {
        cout << d[5] << endl;
    } catch (const exception& e) {
        cout << "Исключение: " << e.what() << endl;
    }
}

void testTypeConversion() {
    printHeader("ТЕСТ ПРЕОБРАЗОВАНИЯ ТИПОВ");
    
    Date d(15, 7, 2023);
    
    cout << "1. Преобразование в string: " << endl;
    string s = d;  // неявное преобразование
    cout << "   string s = d; // s = \"" << s << "\"" << endl;
    
    cout << "2. Явное преобразование в string: ";
    cout << string(d) << endl;
    
    cout << "3. Преобразование в int (дней с 01.01.1970): ";
    int days = d;
    cout << days << " дней" << endl;
    
    cout << "4. Использование в cout (через string): ";
    cout << d << endl;  // работает через operator string()
}

void testAdditionalMethods() {
    printHeader("ТЕСТ ДОПОЛНИТЕЛЬНЫХ МЕТОДОВ");
    
    Date d1(15, 7, 2023);
    Date d2(25, 7, 2023);
    
    cout << "1. Разница между ";
    d1.print();
    cout << " и ";
    d2.print();
    cout << ": " << d1.daysBetween(d2) << " дней" << endl;
    
    cout << "2. День недели для ";
    d1.print();
    cout << ": ";
    string days[] = {"воскресенье", "понедельник", "вторник", "среда", 
                     "четверг", "пятница", "суббота"};
    cout << days[d1.dayOfWeek()] << endl;
    
    cout << "3. Сегодняшняя дата: ";
    Date::today().print();
    cout << endl;
    
    cout << "4. Проверка дат:" << endl;
    cout << "   29.02.2023 - " << (Date::isValidDate(29, 2, 2023) ? "валидна" : "невалидна") << endl;
    cout << "   29.02.2024 - " << (Date::isValidDate(29, 2, 2024) ? "валидна" : "невалидна") << endl;
    cout << "   31.04.2023 - " << (Date::isValidDate(31, 4, 2023) ? "валидна" : "невалидна") << endl;
}

void testEdgeCases() {
    printHeader("ТЕСТ КРАЙНИХ СЛУЧАЕВ");
    
    cout << "1. Переход через год:" << endl;
    Date d(31, 12, 2023);
    cout << "   Начальная дата: ";
    d.print();
    cout << endl;
    cout << "   +1 день: ";
    (d + 1).print();
    cout << endl;
    
    cout << "\n2. Переход через месяц:" << endl;
    d = Date(31, 1, 2023);
    cout << "   Начальная дата: ";
    d.print();
    cout << endl;
    cout << "   +1 день: ";
    (d + 1).print();
    cout << endl;
    
    cout << "\n3. Отрицательные дни (нормализация):" << endl;
    d = Date(1, 1, 2023);
    cout << "   Начальная дата: ";
    d.print();
    cout << endl;
    cout << "   -1 день: ";
    (d - 1).print();
    cout << endl;
    
    cout << "\n4. Большое количество дней:" << endl;
    d = Date(1, 1, 2023);
    cout << "   +1000 дней: ";
    (d + 1000).print();
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "rus");
    
    try {
        testConstructors();
        testOperators();
        testElementAccess();
        testTypeConversion();
        testAdditionalMethods();
        testEdgeCases();
        
        cout << "\n=========================================" << endl;
        cout << "ВСЕ ТЕСТЫ УСПЕШНО ЗАВЕРШЕНЫ!" << endl;
        cout << "=========================================" << endl;
        
    } catch (const exception& e) {
        cerr << "\n!!! КРИТИЧЕСКАЯ ОШИБКА: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}
